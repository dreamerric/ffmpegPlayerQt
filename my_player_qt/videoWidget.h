///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     videoWidget.h                                                       
///  @brief    ���ڽ���������ƵRGBͼƬ��ʾ�ڴ�����                                                                        
///  @author   ���(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <QtWidgets/qwidget.h>
#include <QOpenGLWidget>

/**
	@brief qt��openGLWidget�ؼ���
	
	���ڽ���������ƵRGBͼƬ��ʾ�ڴ�����
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
		@brief ��ʾ��Ƶ��������Ƶ֡ͼ��
		
		playerMediaTimer����updateFrame(QImage *image)�źŴ�������
		��������img��ʾ�ڴ����ϡ�

		@param img ����ʾ��ͼ��
	*/
	void setVideoImage(QImage* img);
	/**
		@brief �������
	*/
	void hideMouse();
signals:
	/**
		@brief ���ؽ������ź�
		
		�źŷ��͸����������ڵ�myPlayerQt����
	*/
	void showSlider(bool isShow);
private:
	QTimer *mouseTimer;  ///< �����ʾ��ʱ��
};

