///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     playerAudio.h                                                       
///  @brief    音频类，用于管理音频packet队列，音频流的解码，调用SDL播放音频                                                                              
///  @author   巢娅(imcy1994@163.com)                                                                                                        
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
	@brief 音频类
	
	用于管理音频packet队列，音频流的解封装、解码，
	调用SDL播放音频
*/
class playerAudio
{
public:
	playerAudio();
	const uint32_t BUFFERSIZE = 192000; ///< 音频缓冲区大小
	
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
		@brief 设置音频缓冲区
	*/
	uint8_t* getAudioBuff();
	void setAudioBuff(uint8_t*& audioBuff);

	uint32_t getAudioBuffSize();
	void setAudioBuffSize(uint32_t audioBuffSize);
	
	uint32_t getAudioBuffIndex();
	void setAudioBuffIndex(uint32_t audioBuffIndex);
	/**
		@brief 设置音频时钟
	*/
	double getAudioClock();
	void setAudioClock(const double &audioClock);
	double getCurrentAudioClock();

	bool getIsPlaying();
	void setPlaying(bool isPlaying);
	/**
		@brief 设置音量
	*/
	void setVolume(int volume);
	~playerAudio();
private:
	int streamIndex = -1;
	AVStream *stream;   ///< 音频流
	AVCodecContext *audioContext; ///< 音频上下文

	packetQueue audioPackets; ///< 音频packet队列
	double audioClock;///< 音频时钟
	uint8_t *audioBuff;	///< 解码后数据的缓冲空间
	uint32_t audioBuffSize;  ///< 音频缓冲区中的字节数
	uint32_t audioBuffIndex; ///< 音频缓冲区中未发送数据的index
	bool isPlay = false;
};
/**
	@brief SDL播放的回调函数
	
	调用SDL提供的音频播放接口，
	发送长度为len的解码后的音频流到播放设备
*/
void audioCallback(void* userdata, uint8_t *stream, int len); 
/**
	@brief 音频解码函数

	从音频的packet队列中取出packet解封装成音频frame，
	再将音频帧解码成PCM数据放入音频缓冲区

	@param srcFrame 当前解码的frame
	@param pts	当前frame的pts
*/
int audioDecodeFrame(playerAudio *audio, uint8_t *audioBuffer, int bufferSize);