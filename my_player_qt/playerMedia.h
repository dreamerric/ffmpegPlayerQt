///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     playerMedia.h                                                       
///  @brief    媒体类，用于管理音频类和视频类，获取视频上下文，控制播放                                                                              
///  @author   巢娅(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "playerAudio.h"
#include "playerVideo.h"
#include <QMutex>
extern "C" {
#include <libavformat\avformat.h>
}
/**
	@brief 媒体类
	
	用于管理音频类和视频类，获取视频上下文，控制播放
*/
class playerMedia
{
public:
	static playerMedia *getInstance() {
		static playerMedia media;
		return &media;
	}
	~playerMedia();
	/**
		@brief 打开网络流视频
	*/
	playerMedia * open();
	playerMedia * setMediaFile(const char*filename);
	/**
		@brief 确认video和audio对象的packet队列大小
	*/
	bool checkMediaSizeValid();

	int getVideoStreamIndex();
	int getAudioStreamIndex();
	void enqueueVideoPacket(const AVPacket &packet);
	void enqueueAudioPacket(const AVPacket &packet);
	
	void startAudioPlay();
	/**
		@brief 打开新视频前清理数据
		
		清理视频音频队列，关闭SDL，清理解码器，清理视频上下文
	*/
	void close();
	/**
		@brief ffmpeg的回调函数，跳出阻塞

		根据成员变量interruptFlag
		跳出打开视频流超时导致avformat_open_input()阻塞，
		以及网络速度慢，长时间无法加载导致av_read_frame()阻塞，
		函数阻塞如果不强制跳出会导致程序卡死。

		@return 返回0继续执行，返回1退出阻塞
	*/
	static int AVInterruptCallBackFun(void *param);

	AVFormatContext *getAVFormatContext();
	playerVideo *video;	///< video对象指针
	playerAudio *audio;	///< audio对象指针
	int totalTime = 0; ///< 视频总时长
	int pts = 0; ///< 当前packet的pts，以音频流为基准
	int type; ///< 指示视频类型的变量
	static bool interruptFlag; ///< 跳出ffmpeg阻塞标志

private:
	playerMedia();

	AVFormatContext *pFormatCtx; ///< 视频上下文
	const char *filename;
	QMutex mutex;
};

