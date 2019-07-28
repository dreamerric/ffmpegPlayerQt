///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     playerVideo.h                                                       
///  @brief    视频类，用于设置视频pts，管理视频packet队列和frame队列                                                                            
///  @author   巢娅(imcy1994@163.com)                                                                                                        
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
	@brief 视频类
	
	继承QThread，用于解封装视频packet，
	设置视频时钟，管理视频packet队列和frame队列
*/
class playerVideo : public QThread
{
public:
	playerVideo();
	/**
		@brief 视频解封装线程
		
		从视频队列中取出packet解封装为frame，
		将frame放入帧队列，设置当前帧延时
	*/
	void run();
	/**
		@brief 设置当前视频流videoClock
		
		videoClock是视频播放到当前帧时的已播放的时间长度。
		在synchronize函数中，如果没有得到该帧的PTS就用当前的videoClock来近似，
		然后更新video_clock的值。
		
		@param srcFrame 当前解码的frame
		@param pts	当前frame的pts
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
		@brief 设置上一帧的播放时间
	*/
	void setFrameLastPts(const double &frameLastPts);
	double getFrameLastPts();
	/**
		@brief 设置上一帧的延时
	*/
	void setFrameLastDelay(const double &frameLastDelay);
	double getFrameLastDelay();
	
	void setVideoClock(const double &videoClock);
	double getVideoClock();
	
	bool getIsPlaying();
	void setPlaying(bool isPlaying);

	void clearFrames();
	void clearPackets();

	SwsContext *swsContext = nullptr; ///< 视频解码器上下文
	~playerVideo();
private:
	int streamIndex = -1;
	AVStream *stream; ///< 视频流指针

	double frameTimer;        
	double frameLastPts;  ///< 保存上一帧的pts
	double frameLastDelay;  ///< 上一帧延时
	double videoClock;  ///< 视频时钟
	bool isPlay = false;
	
	packetQueue *videoPackets; ///< 视频packet队列
	frameQueue frameQueue;	///< 视频帧队列

	AVCodecContext *videoContext; ///< 视频流上下文

	QMutex mutex;
};

