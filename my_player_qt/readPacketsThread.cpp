#include "readPacketsThread.h"
#include "playerMedia.h"
#include "logger.h"

#include <QMutexLocker>
#include <QElapsedTimer>

extern "C" {

#include <libavformat\avformat.h>

}
static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

static bool isExit = false;
static int count = 0;

readPacketsThread::readPacketsThread()
{
}

void readPacketsThread::run()
{
	AVPacket *packet = (AVPacket *)av_malloc(sizeof(AVPacket));
	av_init_packet(packet);

	while (!isExit) {
		QMutexLocker locker(&mutex);
		if (!isPlay) {
			locker.unlock();
			msleep(100);
			continue;
		}

		playerMedia *media = playerMedia::getInstance();
		if (media == nullptr || media->audio == nullptr || media->video == nullptr) {
			msleep(100);
			break;
		}
		if (isSeek) {
			double total = media->totalTime / 1000;
			double start = media->audio->getStream()->start_time / (double)AV_TIME_BASE;
			start += (currentPos * total);
			int64_t timestamp = (int64_t)(start * AV_TIME_BASE);
			int ret = av_seek_frame(media->getAVFormatContext(), -1, timestamp, AVSEEK_FLAG_BACKWARD);
			
			if (ret < 0)
			{
				LOG(LOG_ERROR) << "Seeking fail!" << std::endl;
				printf( "Seeking fail!\n");
				isSeek = false;
				locker.unlock();
				msleep(100);
				continue;
			}
			media->audio->clearPacket();
			media->video->clearPackets();
			media->video->clearFrames();
			isSeek = false;
		}

		bool isInvalid = media->checkMediaSizeValid();
		if (isInvalid) {
			locker.unlock();
			msleep(10);
			continue;
		}

		if (!media->getAVFormatContext()) {
			locker.unlock();
			msleep(10);
			continue;
		}

		int ret = av_read_frame(media->getAVFormatContext(), packet);
		
		if (ret < 0)
		{
			av_packet_unref(packet);
			if (ret == AVERROR_EOF) {
				locker.unlock();
				msleep(100);
				continue;
			}

			if (media->getAVFormatContext()->pb->error == 0)
			{
				locker.unlock();
				msleep(100);
				continue;
			}
			else {
				locker.unlock();
				msleep(100);
				continue;
			}

		}
		if (media->audio != nullptr && packet->stream_index == media->getAudioStreamIndex())
		{
			locker.unlock();
			media->enqueueAudioPacket(*packet);
		}
		else if (media->video != nullptr && packet->stream_index == media->getVideoStreamIndex())
		{
			locker.unlock();
			media->enqueueVideoPacket(*packet);
		}
		else {
			locker.unlock();
			//av_free_packet(packet);
			av_packet_unref(packet);
		}

		
	}

	if (packet)
	{
		av_free_packet(packet);

	}
}

bool readPacketsThread::getIsPlaying()
{
	return isPlay;
}

bool readPacketsThread::getIsSeeking()
{
	return isSeek;
}
void readPacketsThread::setPlaying(bool isPlaying)
{
	this->isPlay = isPlaying;
}

void readPacketsThread::receivePos(float pos)
{
	currentPos = pos;
	isSeek = true;
}

readPacketsThread::~readPacketsThread()
{
	QMutexLocker locker(&mutex);
	isExit = true;
	locker.unlock();
	wait();
}
