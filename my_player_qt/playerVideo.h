///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     playerVideo.h                                                       
///  @brief    ��Ƶ�࣬����������Ƶpts��������Ƶpacket���к�frame����                                                                            
///  @author   ���(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "packetQueue.h"
#include "frameQueue.h"
#include <QThread>
extern "C" {
#include <libavformat/avformat.h>
#include<libswscale/swscale.h>
#include <libswresample/swresample.h>
}
/**
	@brief ��Ƶ��
	
	�̳�QThread�����ڽ��װ��Ƶpacket��
	������Ƶʱ�ӣ�������Ƶpacket���к�frame����
*/
class playerVideo : public QThread
{
public:
	playerVideo();
	/**
		@brief ��Ƶ���װ�߳�
		
		����Ƶ������ȡ��packet���װΪframe��
		��frame����֡���У����õ�ǰ֡��ʱ
	*/
	void run();
	/**
		@brief ���õ�ǰ��Ƶ��videoClock
		
		videoClock����Ƶ���ŵ���ǰ֡ʱ���Ѳ��ŵ�ʱ�䳤�ȡ�
		��synchronize�����У����û�еõ���֡��PTS���õ�ǰ��videoClock�����ƣ�
		Ȼ�����video_clock��ֵ��
		
		@param srcFrame ��ǰ�����frame
		@param pts	��ǰframe��pts
	*/
	double synchronizeVideo(AVFrame *&srcFrame, double &pts);

	void setStreamIndex(const int &streamIndex);
	int getStreamIndex();

	AVStream *getVideoStream();
	void setVideoStream(AVStream *&stream);

	AVCodecContext *getAVCodecContext();
	void setAVCodecContext(AVCodecContext *videoContext);

	int getVideoQueueSize();
	void enqueuePacket(const AVPacket packet);
	
	AVFrame * dequeueFrame();
	int getVideoFrameSize();

	void setFrameTimer(const double &frameTimer);
	double getFrameTimer();
	/**
		@brief ������һ֡�Ĳ���ʱ��
	*/
	void setFrameLastPts(const double &frameLastPts);
	double getFrameLastPts();
	/**
		@brief ������һ֡����ʱ
	*/
	void setFrameLastDelay(const double &frameLastDelay);
	double getFrameLastDelay();
	
	void setVideoClock(const double &videoClock);
	double getVideoClock();
	
	bool getIsPlaying();
	void setPlaying(bool isPlaying);

	void clearFrames();
	void clearPackets();

	SwsContext *swsContext = nullptr; ///< ��Ƶ������������
	~playerVideo();
private:
	int streamIndex = -1;
	AVStream *stream; ///< ��Ƶ��ָ��

	double frameTimer;        
	double frameLastPts;  ///< ������һ֡��pts
	double frameLastDelay;  ///< ��һ֡��ʱ
	double videoClock;  ///< ��Ƶʱ��
	bool isPlay = false;
	
	packetQueue *videoPackets; ///< ��Ƶpacket����
	frameQueue frameQueue;	///< ��Ƶ֡����

	AVCodecContext *videoContext; ///< ��Ƶ��������

	QMutex mutex;
};

