///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     readPacketsThread.h                                                       
///  @brief    读取视频音频和视频packet的线程类                                                                        
///  @author   巢娅(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <QThread>
#include <QMutex>

/**
	@brief 读取视频音频和视频packet的线程类
*/
class readPacketsThread :public QThread
{
	Q_OBJECT
public:
	static readPacketsThread * getInstance() {
		static readPacketsThread rpt;
		return &rpt;
	}
	/**
		@brief 音视频packet入队线程

		根据packet中的stream_index将视频和音频packet分别放入各自对象队列，
		配合主窗口进度条根据isSeek标志调用av_seek_frame()跳转至视频指定位置，
	*/
	void run();
	bool getIsPlaying();
	/**
		@brief 设置跳转标志
	*/
	bool getIsSeeking();
	void setPlaying(bool isPlaying);
	virtual ~readPacketsThread();

public slots:
	/**
		@brief	接收主窗口视频跳转位置
		@param pos	视频跳转点在进度条中的位置
	*/
	void receivePos(float pos);
private:
	readPacketsThread();
	bool isSeek = false;
	float currentPos = 0;
	
	bool isPlay = false;
	QMutex mutex;
};

