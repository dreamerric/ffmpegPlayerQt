///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     frameQueue.h                                                       
///  @brief    ֡�����࣬����ʵ��֡���в���                                                                              
///  @author   ���(imcy1994@163.com)                                                                                                        
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
	@brief ֡������
	
	����ʵ�ֳ��ӡ���ӡ������֡���в��� 
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
	std::queue<AVFrame*> queue; ///< ֡����
	QMutex mutex;
	QWaitCondition condition;
};

