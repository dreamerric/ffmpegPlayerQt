#include "playerMediaTimer.h"
#include "playerMedia.h"
static const double SYNC_THRESHOLD = 0.01;   //ͬ��
static const double NOSYNC_THRESHOLD = 10.0;  //��ͬ��

playerMediaTimer::playerMediaTimer()
{
	buf = new uchar[imageWidth*imageHeight * 4];
	img = new QImage(buf, imageWidth, imageHeight, QImage::Format_ARGB32);
	timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(synchronizeAudioAndVideo()));
	timer->start(20);
}

playerMediaTimer::~playerMediaTimer()
{
	if (img)
		delete img;
	if (buf)
		delete buf;
	if (timer)
		delete timer;
}

void playerMediaTimer::synchronizeAudioAndVideo()
{
	if (!isPlay) {
		timer->setInterval(20);
		return;
	}
	if (playerMedia::getInstance()->video->getVideoFrameSize() == 0) {
		timer->setInterval(20);
		return;
	}
	static int width = 0;
	static int height = 0;
	// ���ڳߴ緢���仯������RGBͼƬ�ߴ�
	if (width != imageHeight || height != imageWidth) {
		if (img) {
			delete img;
			img = nullptr;
		}
		width = imageHeight;
		height = imageWidth;
	}

	if (img == nullptr)
	{
		if (buf != nullptr) {
			delete buf;
			buf = nullptr;
		}	
		buf = new uchar[imageWidth*imageHeight * 4];
		img = new QImage(buf, imageWidth, imageHeight, QImage::Format_ARGB32);
		
	}

	AVFrame * frame;
	frame = playerMedia::getInstance()->video->dequeueFrame();
	// ����Ƶͬ������Ƶ�ϣ�������һ֡���ӳ�ʱ��
    // ʹ��Ҫ���ŵĵ�ǰ֡��PTS����һ֡��PTS�������Ʋ�����һ֡���ӳ�ʱ��
	// ������video�Ĳ����ٶ�����������ӳ�ʱ��
	double current_pts = *(double*)frame->opaque;
	double delay = current_pts - playerMedia::getInstance()->video->getFrameLastPts();
	if (delay <= 0 || delay >= 1.0)
		delay = playerMedia::getInstance()->video->getFrameLastDelay();

	playerMedia::getInstance()->video->setFrameLastDelay(delay);
	playerMedia::getInstance()->video->setFrameLastPts(current_pts);
	
	// double ref_clock = playerMedia::getInstance()->audio->getAudioClock();
	double ref_clock = playerMedia::getInstance()->audio->getCurrentAudioClock();
	double diff = current_pts - ref_clock;  
	double threshold = (delay > SYNC_THRESHOLD) ? delay : SYNC_THRESHOLD;
	
	// ����������һ֡���ӳ�ʱ�䣬��ʵ��ͬ��
	if (fabs(diff) < NOSYNC_THRESHOLD) 
	{
		if (diff <= -threshold) // ���ˣ�delay��Ϊ0
			delay = 0;
		else if (diff >= threshold) // ���ˣ��ӱ�delay
			delay *= 2;
	}

	playerMedia::getInstance()->video->setFrameTimer(playerMedia::getInstance()->video->getFrameTimer() + delay);
	double actual_delay = playerMedia::getInstance()->video->getFrameTimer() - static_cast<double>(av_gettime()) / 1000000.0;
	if (actual_delay <= 0.010)
		actual_delay = 0.010;
	// ����һ��֡���ŵ��ӳ�
	timer->setInterval(static_cast<int>(actual_delay * 1000 + 0.5));
	AVCodecContext *videoCtx = playerMedia::getInstance()->video->getVideoStream()->codec;

	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };
	data[0] = (uint8_t *)img->bits();
	playerMedia::getInstance()->video->swsContext = sws_getCachedContext(playerMedia::getInstance()->video->swsContext, 
		videoCtx->width,
		videoCtx->height,
		videoCtx->pix_fmt,
		imageWidth, imageHeight,
		AV_PIX_FMT_BGRA,
		SWS_BICUBIC,
		NULL, NULL, NULL
	);

	linesize[0] = imageWidth * 4;
	int h = sws_scale(playerMedia::getInstance()->video->swsContext, frame->data, frame->linesize, 0, videoCtx->height,
		data,
		linesize);
	emit updateFrame(img);
	av_frame_unref(frame);
	av_frame_free(&frame);
}

bool playerMediaTimer::isPlaying()
{
	return isPlay;
}

void playerMediaTimer::setPlay(bool isPlaying)
{
	this->isPlay = isPlaying;
}

void playerMediaTimer::resetImage(int width, int height)
{
	imageWidth = width;
	imageHeight = height;
}

