///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     playerMediaTimer.h                                                       
///  @brief    ����Ƶͬ���࣬����ͬ����Ƶ����Ƶ��������Ƶ֡������openglWidget��ʾ                                                                             
///  @author   ���(imcy1994@163.com)                                                                                                        
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
	@brief ����Ƶͬ����

	����ͬ����Ƶ����Ƶ��
	������Ƶʱ��ȡ����Ƶ֡�����е�frame
	����frameΪRGBͼ������openglWidget��ʾ��ʵ������Ƶͬ����
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
		@brief ���ڳߴ�仯���ý����RGBͼƬ�ߴ�

		@param width	���ú�ͼƬ��
		@param height	���ú�ͼƬ��
	*/
	void resetImage(int width, int height);
	~playerMediaTimer();

public slots:
	/**
		@brief ��������Ƶͬ��

		����Ƶͬ������Ƶ�ϣ�������һ֡���ӳ�ʱ��
		ʹ��Ҫ���ŵĵ�ǰ֡��PTS����һ֡��PTS�������Ʋ�����һ֡���ӳ�ʱ��
		������video�Ĳ����ٶ�����������ӳ�ʱ��,
		������ʱʱ�������Ƶ֡�Ľ��벥�š�
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
		@brief ���͸�videoWidget����ˢ����ʾ�������Ƶͼ��
	*/
	void updateFrame(QImage *image);
};

