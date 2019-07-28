///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     frameQueue.h                                                       
///  @brief    帧队列类，用于实现帧队列操作                                                                              
///  @author   巢娅(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <queue>
#include <QMutex>
#include <QWaitCondition>
extern "C" {

#include <libavcodec\avcodec.h>
#include <libavformat/avformat.h>
}
/**
	@brief 帧队列类
	
	用于实现出队、入队、清理等帧队列操作 
*/
class frameQueue
{
public:
	static const int capacity = 30;
	
	bool enQueue(const AVFrame* frame);
	AVFrame * deQueue();
	
	int getQueueSize();
	void queueFlush();

	frameQueue();
	~frameQueue();
private:
	std::queue<AVFrame*> queue; ///< 帧队列
	QMutex mutex;
	QWaitCondition condition;
};

