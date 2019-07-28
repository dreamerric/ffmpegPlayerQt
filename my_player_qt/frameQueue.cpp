#include "frameQueue.h"

bool frameQueue::enQueue(const AVFrame * frame)
{
	AVFrame* p = av_frame_alloc();
	int ret = av_frame_ref(p, frame);
	if (ret < 0)
		return false;

	p->opaque = (void *)new double(*(double*)p->opaque); 
	QMutexLocker locker(&mutex);
	queue.push(p);
	condition.wakeOne();
	return true;
}

AVFrame * frameQueue::deQueue()
{
	bool ret = true;
	AVFrame *frame;
	QMutexLocker locker(&mutex);
	while (true)
	{
		if (!queue.empty())
		{
			frame = queue.front();
			queue.pop();
			ret = true;
			break;
		}
		else
		{
			condition.wait(&mutex);
		}
	}

	return frame;
}

int frameQueue::getQueueSize()
{
	return queue.size();
}

void frameQueue::queueFlush()
{
	while (!queue.empty())
	{
		AVFrame *frame = deQueue();
		av_frame_unref(frame);
	}
}

frameQueue::frameQueue()
{
}


frameQueue::~frameQueue()
{
}
