///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     playerMediaTimer.h                                                       
///  @brief    音视频同步类，用于同步音频和视频，解码视频帧发送至openglWidget显示                                                                             
///  @author   巢娅(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <QTimer>
#include <QMutex>
#include <QImage>
extern "C" {

#include <libswscale\swscale.h>
#include <libavutil\time.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}
/**
	@brief 音视频同步类

	用于同步音频和视频，
	根据音频时钟取出视频帧队列中的frame
	解码frame为RGB图像发送至openglWidget显示，实现视音频同步。
*/
class playerMediaTimer : public QObject
{
	Q_OBJECT
public:
	static playerMediaTimer *getInstance() {
		static playerMediaTimer displayMediaThread;
		return &displayMediaThread;
	}
	bool isPlaying();
	void setPlay(bool isPlaying);
	/**
		@brief 窗口尺寸变化重置解码的RGB图片尺寸

		@param width	重置后图片宽
		@param height	重置后图片高
	*/
	void resetImage(int width, int height);
	~playerMediaTimer();

public slots:
	/**
		@brief 设置音视频同步

		将视频同步到音频上，计算下一帧的延迟时间
		使用要播放的当前帧的PTS和上一帧的PTS差来估计播放下一帧的延迟时间
		并根据video的播放速度来调整这个延迟时间,
		根据延时时间控制视频帧的解码播放。
	*/
	void synchronizeAudioAndVideo();
private:
	playerMediaTimer();
	bool isPlay = false;
	QTimer *timer;
	uchar *buf;
	QImage *img;
	int imageWidth = 800;
	int imageHeight = 600;
	QMutex mutex;
signals:
	/**
		@brief 发送给videoWidget对象刷新显示解码后视频图像
	*/
	void updateFrame(QImage *image);
};

