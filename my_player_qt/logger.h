///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     logger.h                                                       
///  @brief    ��־�࣬���ڹ���������е���־��Ϣ��ffmpeg�������־                                                                              
///  @author   ���(imcy1994@163.com)                                                                                                        
///  @version  1.0.0.0                                                
///  @date     2019.05.15                                                                                
///                                                                          
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef  __logger__
#define  __logger__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdint.h>

extern "C" {
#include <libavformat\avformat.h>
}
/**
	@brief ����������ͬ����־����
*/
typedef enum logRank {
	LOG_INFO=1,
	LOG_WARNING,
	LOG_ERROR,
}logRankType;

void initLogger(const std::string& logFilename);
/**
	@brief ��־��
	
	���ڹ���������е���־��Ϣ��ffmpeg��av_log�����־��
	��������־��Ϣд����־�ļ���
*/
class logger
{
public:
	logger() : logRank() {};
	static logger * getInstance() {
		static logger log;
		return &log;
	}
	/**
		@brief ��־��ʼ������
		
		���ڴ���־�ļ�����ʼ�������

		@param logFilename ��־�ļ�����
	*/
	friend void initLogger(const std::string& logFilename);
	/**
		@brief ffmpeg��av_log�Ļص�������
		
		���ڽ�ffmepeg����ʱ����־��Ϣ��level�������־�ļ���

		@param level ffmpeg��־����
		@param fmt ��ʽ������־��Ϣ
		@param vl ��ʽ�������б�
	*/
	friend void avLogOuput(void * ptr, int level, const char * fmt, va_list vl);
	/**
		@brief ������־������־��ӡʱ��͵��õ㺯��д�������

		@param rank ��־����
		@param line ����д����־�����ĺ����к�
		@param function ����д����־�����ĺ�����
	*/
	static std::ostream& start(int rank,
		const std::int32_t line,
		const std::string& function);
	/**
		@brief ��ȡ��־�ļ���
	*/
	void setLogFileName(const std::string& logFilename);
	std::string getLogFileName();

	~logger();
private:
	/**
		@brief ����ͬ��־����д�������

		@param rank ��־����
	*/
	static std::ostream& getStream(int rank);
	static std::ofstream logFile; ///< ��־�ļ������
	std::string fileName; ///< ��־�ļ���
	logRankType logRank;                             
};

// ����귽����־��ӡ��������
#define LOG(rank)   \
logger::getInstance()->start(rank, __LINE__,__FUNCTION__)
#endif