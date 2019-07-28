///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     playerMedia.h                                                       
///  @brief    ý���࣬���ڹ�����Ƶ�����Ƶ�࣬��ȡ��Ƶ�����ģ����Ʋ���                                                                              
///  @author   ���(imcy1994@163.com)                                                                                                        
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
	@brief ý����
	
	���ڹ�����Ƶ�����Ƶ�࣬��ȡ��Ƶ�����ģ����Ʋ���
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
		@brief ����������Ƶ
	*/
	playerMedia * open();
	playerMedia * setMediaFile(const char*filename);
	/**
		@brief ȷ��video��audio�����packet���д�С
	*/
	bool checkMediaSizeValid();

	int getVideoStreamIndex();
	int getAudioStreamIndex();
	void enqueueVideoPacket(const AVPacket &packet);
	void enqueueAudioPacket(const AVPacket &packet);
	
	void startAudioPlay();
	/**
		@brief ������Ƶǰ��������
		
		������Ƶ��Ƶ���У��ر�SDL�������������������Ƶ������
	*/
	void close();
	/**
		@brief ffmpeg�Ļص���������������

		���ݳ�Ա����interruptFlag
		��������Ƶ����ʱ����avformat_open_input()������
		�Լ������ٶ�������ʱ���޷����ص���av_read_frame()������
		�������������ǿ�������ᵼ�³�������

		@return ����0����ִ�У�����1�˳�����
	*/
	static int AVInterruptCallBackFun(void *param);

	AVFormatContext *getAVFormatContext();
	playerVideo *video;	///< video����ָ��
	playerAudio *audio;	///< audio����ָ��
	int totalTime = 0; ///< ��Ƶ��ʱ��
	int pts = 0; ///< ��ǰpacket��pts������Ƶ��Ϊ��׼
	int type; ///< ָʾ��Ƶ���͵ı���
	static bool interruptFlag; ///< ����ffmpeg������־

private:
	playerMedia();

	AVFormatContext *pFormatCtx; ///< ��Ƶ������
	const char *filename;
	QMutex mutex;
};

