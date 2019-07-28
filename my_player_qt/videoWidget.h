///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     videoWidget.h                                                       
///  @brief    用于将解码后的视频RGB图片显示在窗口上                                                                        
///  @author   巢娅(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <QtWidgets/qwidget.h>
#include <QOpenGLWidget>

/**
	@brief qt的openGLWidget控件类
	
	用于将解码后的视频RGB图片显示在窗口上
*/
class videoWidget :
	public QOpenGLWidget
{
	Q_OBJECT
public:
	videoWidget(QWidget *p = nullptr);
	void paintEvent(QPaintEvent *pEvent);
	void timerEvent(QTimerEvent *pEvent);
	void mouseMoveEvent(QMouseEvent *pEvent);

	videoWidget();
	~videoWidget();
public slots:
	/**
		@brief 显示视频解码后的视频帧图像
		
		playerMediaTimer对象updateFrame(QImage *image)信号处理函数，
		将解码后的img显示在窗口上。

		@param img 待显示的图像
	*/
	void setVideoImage(QImage* img);
	/**
		@brief 隐藏鼠标
	*/
	void hideMouse();
signals:
	/**
		@brief 隐藏进度条信号
		
		信号发送给管理主窗口的myPlayerQt对象
	*/
	void showSlider(bool isShow);
private:
	QTimer *mouseTimer;  ///< 鼠标显示定时器
};

