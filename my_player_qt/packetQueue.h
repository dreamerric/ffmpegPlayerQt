///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     packetQueue.h                                                       
///  @brief    视频packet队列的定义，定义出入队等队列操作                                                                              
///  @author   巢娅(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <QWaitCondition>
#include <QMutex>
#include <queue>

extern "C" {
#include <libavcodec\avcodec.h>
}
/**
	@brief packet队列类
	
	用于实现packet队列的出队、入队、队列清理等队列操作方法
*/
class packetQueue
{
public:
	packetQueue();
	bool enQueue(const AVPacket packet);
	AVPacket deQueue();
	uint32_t getPacketSize();
	void queueFlush();
	virtual ~packetQueue();
private:
	std::queue<AVPacket> queue;
	uint32_t    size;
	QMutex mutex;
	QWaitCondition condtion;

};

