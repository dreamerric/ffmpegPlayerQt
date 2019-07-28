#include "playerMedia.h"
#include "playerMediaTimer.h"
#include "readPacketsThread.h"
#include "logger.h"

extern "C" {
#include <libavutil/time.h>
}
const static long long  MAX_AUDIOQ_SIZE = (5 * 16 * 1024);
const static long long   MAX_VIDEOQ_SIZE = (5 * 256 * 1024);
bool playerMedia::interruptFlag;

static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

playerMedia::playerMedia()
{
	av_register_all();
	avformat_network_init();
	pFormatCtx = nullptr;

	audio = new playerAudio;
	video = new playerVideo;
	interruptFlag = false;
}
int playerMedia::AVInterruptCallBackFun(void *param)
{
	if (!interruptFlag)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
playerMedia::~playerMedia()
{
	QMutexLocker locker(&mutex);
	if (audio != nullptr) {
		delete audio;
		audio = nullptr;
	}

	if (video != nullptr) {
		delete video;
		video = nullptr;
	}
}

playerMedia * playerMedia::open()
{
	close();
	QMutexLocker locker(&mutex);
	pFormatCtx = avformat_alloc_context();
	pFormatCtx->interrupt_callback.callback = AVInterruptCallBackFun;
	pFormatCtx->interrupt_callback.opaque = pFormatCtx;

	interruptFlag = false;

	char errorbuf[1024] = { 0 };
	int errCode = 0;
	if ((errCode = avformat_open_input(&pFormatCtx, filename, NULL, NULL)) < 0) {
		av_strerror(errCode, errorbuf, sizeof(errorbuf));
		LOG(LOG_ERROR) << "Open input file fail, error code: " 
			<< errCode <<": "
			<< errorbuf
			<< std::endl;
		return nullptr;
	};
	if ((errCode = avformat_find_stream_info(pFormatCtx, NULL)) < 0) {
		av_strerror(errCode, errorbuf, sizeof(errorbuf));
		LOG(LOG_ERROR) << "Find stream fail, error code: " 
			<< errCode << ": "
			<< errorbuf
			<< std::endl;
		return nullptr;
	};
	av_dump_format(pFormatCtx, 0, filename, 0);

	video->setStreamIndex(-1);
	audio->setStreamIndex(-1);
	for (uint32_t i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && audio->getStreamIndex() < 0)
			audio->setStreamIndex(i);

		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && video->getStreamIndex() < 0)
			video->setStreamIndex(i);
	}

	if (audio->getStreamIndex() < 0 || video->getStreamIndex() < 0) {
		return nullptr;
	}

	// set audio
	AVCodec *pCodecAudio = avcodec_find_decoder(pFormatCtx->streams[audio->getStreamIndex()]->codec->codec_id);
	if (!pCodecAudio)
	{
		LOG(LOG_ERROR) << "Audio code not find!" << std::endl;
		return nullptr;
	}
	audio->setAVCodecContext(avcodec_alloc_context3(pCodecAudio));
	audio->setStream(pFormatCtx->streams[audio->getStreamIndex()]);

	if (avcodec_copy_context(audio->getAVCodecContext(), 
		pFormatCtx->streams[audio->getStreamIndex()]->codec) != 0) {
		LOG(LOG_ERROR) << "Audio stream can not copy to context!" << std::endl;
		return nullptr;
	}

	errCode = avcodec_open2(audio->getAVCodecContext(), pCodecAudio, nullptr);
	if (errCode != 0)
	{
		av_strerror(errCode, errorbuf, sizeof(errorbuf));
		return nullptr;
	}
	//set video
	AVCodec *pCodecVideo = avcodec_find_decoder(pFormatCtx->streams[video->getStreamIndex()]->codec->codec_id);
	if (!pCodecVideo) {
		LOG(LOG_ERROR) << "Video code not find!" << std::endl;
		return nullptr;
	}

	video->setVideoStream(pFormatCtx->streams[video->getStreamIndex()]);
	video->setAVCodecContext(avcodec_alloc_context3(pCodecVideo));
	if (avcodec_copy_context(video->getAVCodecContext(), 
		pFormatCtx->streams[video->getStreamIndex()]->codec) != 0) {
		LOG(LOG_ERROR) << "Video stream can not copy to context!" << std::endl;
		return nullptr;
	}

	errCode = avcodec_open2(video->getAVCodecContext(), pCodecVideo, nullptr);
	if (errCode != 0)
	{
		av_strerror(errCode, errorbuf, sizeof(errorbuf));
		return nullptr;
	}
	totalTime = ((pFormatCtx->duration / AV_TIME_BASE) * 1000);
	
	video->setFrameTimer(static_cast<double>(av_gettime()) / 1000000.0);
	video->setFrameLastDelay(40e-3);
	audio->audioOpen();
	video->setPlaying(true);

	readPacketsThread::getInstance()->setPlaying(true);
	playerMediaTimer::getInstance()->setPlay(true);
	return this;
}

playerMedia * playerMedia::setMediaFile(const char * filename)
{
	this->filename = filename;
	return this;
}

bool playerMedia::checkMediaSizeValid()
{
	if (this->audio == nullptr || this->video == nullptr) {
		return true;
	}
	uint32_t audioSize = this->audio->getAudioQueueSize();
	uint32_t videoSize = this->video->getVideoQueueSize();
	return (audioSize > MAX_AUDIOQ_SIZE || videoSize > MAX_VIDEOQ_SIZE);
}

int playerMedia::getVideoStreamIndex()
{
	return video->getStreamIndex();
}

int playerMedia::getAudioStreamIndex()
{
	return audio->getStreamIndex();
}

void playerMedia::enqueueVideoPacket(const AVPacket & packet)
{
	video->enqueuePacket(packet);
}

void playerMedia::enqueueAudioPacket(const AVPacket & packet)
{
	audio->enqueuePacket(packet);
}

void playerMedia::startAudioPlay()
{
	audio->audioOpen();
}

AVFormatContext * playerMedia::getAVFormatContext()
{
	QMutexLocker locker(&mutex);
	AVFormatContext * p = pFormatCtx;
	return p;
}

void playerMedia::close()
{
	QMutexLocker locker(&mutex);
	totalTime = 0;
	pts = 0;

	audio->audioClose();
	audio->clearPacket();
	video->clearFrames();
	video->clearPackets();
	
	if (pFormatCtx) {
		avformat_close_input(&pFormatCtx);
		pFormatCtx = nullptr;
	}

	if (video->swsContext)
	{
		sws_freeContext(video->swsContext);
		video->swsContext = nullptr;
	}
	
	readPacketsThread::getInstance()->setPlaying(false);
	playerMediaTimer::getInstance()->setPlay(false);
	video->setPlaying(false);
}
