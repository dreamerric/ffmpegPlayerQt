#include "packetQueue.h"
#include <iostream>
#include <QMutexLocker>
static bool isExit = false;
packetQueue::packetQueue()
{
	size = 0;
}

bool packetQueue::enQueue(const AVPacket packet)
{
	QMutexLocker locker(&mutex);
	queue.push(packet);
	size += packet.size;
	condtion.wakeOne();
	return true;
}

AVPacket packetQueue::deQueue()
{
	bool ret = false;
	AVPacket pkt;
	QMutexLocker locker(&mutex);
	while (true)
	{
		if (!queue.empty())
		{
			pkt = queue.front();
			queue.pop();
			size -= pkt.size;
			ret = true;
			break;
		}
		else
		{
			condtion.wait(&mutex);
		}
	}
	return pkt;
}

uint32_t packetQueue::getPacketSize()
{
	QMutexLocker locker(&mutex);
	return size;
}


void packetQueue::queueFlush()
{
	while (!queue.empty())
	{
		AVPacket pkt = deQueue();
		av_free_packet(&pkt);
	}
}

packetQueue::~packetQueue()
{
	QMutexLocker locker(&mutex);
	isExit = true;
}
