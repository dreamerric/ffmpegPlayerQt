///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     playerAudio.h                                                       
///  @brief    ��Ƶ�࣬���ڹ�����Ƶpacket���У���Ƶ���Ľ��룬����SDL������Ƶ                                                                              
///  @author   ���(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "packetQueue.h"

extern "C" {

#include <libavformat/avformat.h>
#include "SDL2/SDL.h"
#include <libswresample\swresample.h>
}
/**
	@brief ��Ƶ��
	
	���ڹ�����Ƶpacket���У���Ƶ���Ľ��װ�����룬
	����SDL������Ƶ
*/
class playerAudio
{
public:
	playerAudio();
	const uint32_t BUFFERSIZE = 192000; ///< ��Ƶ��������С
	
	bool audioClose();
	bool audioOpen();

	void setStreamIndex(const int &streamIndex);
	int getStreamIndex();

	AVStream *getStream();
	void setStream(AVStream *&stream);

	AVCodecContext *getAVCodecContext();
	void setAVCodecContext(AVCodecContext *audioContext);

	int getAudioQueueSize();
	void clearPacket();
	
	void enqueuePacket(const AVPacket packet);
	AVPacket dequeuePacket();
	/**
		@brief ������Ƶ������
	*/
	uint8_t* getAudioBuff();
	void setAudioBuff(uint8_t*& audioBuff);

	uint32_t getAudioBuffSize();
	void setAudioBuffSize(uint32_t audioBuffSize);
	
	uint32_t getAudioBuffIndex();
	void setAudioBuffIndex(uint32_t audioBuffIndex);
	/**
		@brief ������Ƶʱ��
	*/
	double getAudioClock();
	void setAudioClock(const double &audioClock);
	double getCurrentAudioClock();

	bool getIsPlaying();
	void setPlaying(bool isPlaying);
	/**
		@brief ��������
	*/
	void setVolume(int volume);
	~playerAudio();
private:
	int streamIndex = -1;
	AVStream *stream;   ///< ��Ƶ��
	AVCodecContext *audioContext; ///< ��Ƶ������

	packetQueue audioPackets; ///< ��Ƶpacket����
	double audioClock;///< ��Ƶʱ��
	uint8_t *audioBuff;	///< ��������ݵĻ���ռ�
	uint32_t audioBuffSize;  ///< ��Ƶ�������е��ֽ���
	uint32_t audioBuffIndex; ///< ��Ƶ��������δ�������ݵ�index
	bool isPlay = false;
};
/**
	@brief SDL���ŵĻص�����
	
	����SDL�ṩ����Ƶ���Žӿڣ�
	���ͳ���Ϊlen�Ľ�������Ƶ���������豸
*/
void audioCallback(void* userdata, uint8_t *stream, int len); 
/**
	@brief ��Ƶ���뺯��

	����Ƶ��packet������ȡ��packet���װ����Ƶframe��
	�ٽ���Ƶ֡�����PCM���ݷ�����Ƶ������

	@param srcFrame ��ǰ�����frame
	@param pts	��ǰframe��pts
*/
int audioDecodeFrame(playerAudio *audio, uint8_t *audioBuffer, int bufferSize);