///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     packetQueue.h                                                       
///  @brief    ��Ƶpacket���еĶ��壬�������ӵȶ��в���                                                                              
///  @author   ���(imcy1994@163.com)                                                                                                        
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
	@brief packet������
	
	����ʵ��packet���еĳ��ӡ���ӡ���������ȶ��в�������
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

