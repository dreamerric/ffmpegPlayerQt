#include "playerVideo.h"
static bool isExit = false;

static int audioVolume = 64;
playerVideo::playerVideo()
{
	frameTimer = 0.0;
	frameLastDelay = 0.0;
	frameLastPts = 0.0;
	videoClock = 0.0;
	videoPackets = new packetQueue;
}

void playerVideo::run()
{
	AVFrame * frame = av_frame_alloc();
	double pts;
	AVPacket packet;
	while (!isExit)
	{
		QMutexLocker locker(&mutex);
		if (!isPlay) {
			locker.unlock();
			msleep(100);
			continue;
		}

		if (frameQueue.getQueueSize() >= frameQueue::capacity) 
		{
			locker.unlock();
			msleep(100);
			continue;
		}
		if (videoPackets->getPacketSize() == 0) 
		{
			locker.unlock();
			msleep(100);
			continue;
		}
		packet = videoPackets->deQueue();
		int ret = avcodec_send_packet(videoContext, &packet);
		if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) 
		{
			continue;
		}

		ret = avcodec_receive_frame(videoContext, frame);
		if (ret < 0 && ret != AVERROR_EOF) 
		{
			continue;
		}

		if ((pts = av_frame_get_best_effort_timestamp(frame)) == AV_NOPTS_VALUE)
			pts = 0;
		pts *= av_q2d(stream->time_base);  
		pts = synchronizeVideo(frame, pts);
		frame->opaque = &pts;
		frameQueue.enQueue(frame);  
		av_frame_unref(frame);
	}
	av_frame_free(&frame);
}

double playerVideo::synchronizeVideo(AVFrame *& srcFrame, double & pts)
{
	double frameDelay;
	if (pts != 0)
		videoClock = pts;    
	else
		pts = videoClock;   
	if (stream->codec)
	{
		frameDelay = av_q2d(stream->codec->time_base);
		frameDelay += srcFrame->repeat_pict * (frameDelay * 0.5);
		videoClock += frameDelay;
	}
	return pts;
}

AVStream * playerVideo::getVideoStream()
{
	return this->stream;
}

void playerVideo::setVideoStream(AVStream *& stream)
{
	this->stream = stream;
}

void playerVideo::setStreamIndex(const int & streamIndex)
{
	this->streamIndex = streamIndex;
}

int playerVideo::getStreamIndex()
{
	return streamIndex;
}
AVCodecContext * playerVideo::getAVCodecContext()
{
	return videoContext;
}

void playerVideo::setAVCodecContext(AVCodecContext * videoContext)
{
	this->videoContext = videoContext;
}

int playerVideo::getVideoQueueSize()
{
	return videoPackets->getPacketSize();
}

void playerVideo::enqueuePacket(const AVPacket packet)
{
	videoPackets->enQueue(packet);
}

AVFrame * playerVideo::dequeueFrame()
{
	return frameQueue.deQueue();
}

int playerVideo::getVideoFrameSize()
{
	return frameQueue.getQueueSize();
}

void playerVideo::setFrameTimer(const double & frameTimer)
{
	this->frameTimer = frameTimer;
}

double playerVideo::getFrameTimer()
{
	return frameTimer;
}

void playerVideo::setFrameLastPts(const double & frameLastPts)
{
	this->frameLastPts = frameLastPts;
}

double playerVideo::getFrameLastPts()
{
	return frameLastPts;
}

void playerVideo::setFrameLastDelay(const double & frameLastDelay)
{
	this->frameLastDelay = frameLastDelay;
}

double playerVideo::getFrameLastDelay()
{
	return frameLastDelay;
}

void playerVideo::setVideoClock(const double & videoClock)
{
	this->videoClock = videoClock;
}

double playerVideo::getVideoClock()
{
	return videoClock;
}

bool playerVideo::getIsPlaying()
{
	return isPlay;
}

void playerVideo::setPlaying(bool isPlaying)
{
	isPlay = isPlaying;
}

void playerVideo::clearFrames()
{
	frameQueue.queueFlush();
}

void playerVideo::clearPackets()
{
	videoPackets->queueFlush();
}


playerVideo::~playerVideo()
{
	QMutexLocker locker(&mutex);
	isExit = true;
	delete videoPackets;
	locker.unlock();
	wait();
}
