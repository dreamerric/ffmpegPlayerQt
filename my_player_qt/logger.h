///////////////////////////////////////////////////////////////////////////////             
///                                                                            
///  @file     logger.h                                                       
///  @brief    日志类，用于管理程序运行的日志信息和ffmpeg的输出日志                                                                              
///  @author   巢娅(imcy1994@163.com)                                                                                                        
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
	@brief 定义三个不同的日志级别
*/
typedef enum logRank {
	LOG_INFO=1,
	LOG_WARNING,
	LOG_ERROR,
}logRankType;

void initLogger(const std::string& logFilename);
/**
	@brief 日志类
	
	用于管理程序运行的日志信息和ffmpeg的av_log输出日志，
	将所有日志信息写入日志文件。
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
		@brief 日志初始化函数
		
		用于打开日志文件，初始化输出流

		@param logFilename 日志文件名称
	*/
	friend void initLogger(const std::string& logFilename);
	/**
		@brief ffmpeg的av_log的回调函数，
		
		用于将ffmepeg运行时的日志信息按level输出到日志文件中

		@param level ffmpeg日志级别
		@param fmt 格式化的日志信息
		@param vl 格式化参数列表
	*/
	friend void avLogOuput(void * ptr, int level, const char * fmt, va_list vl);
	/**
		@brief 将按日志级别、日志打印时间和调用点函数写入输出流

		@param rank 日志级别
		@param line 调用写入日志操作的函数行号
		@param function 调用写入日志操作的函数名
	*/
	static std::ostream& start(int rank,
		const std::int32_t line,
		const std::string& function);
	/**
		@brief 获取日志文件名
	*/
	void setLogFileName(const std::string& logFilename);
	std::string getLogFileName();

	~logger();
private:
	/**
		@brief 按不同日志级别写入输出流

		@param rank 日志级别
	*/
	static std::ostream& getStream(int rank);
	static std::ofstream logFile; ///< 日志文件输出流
	std::string fileName; ///< 日志文件名
	logRankType logRank;                             
};

// 定义宏方便日志打印函数调用
#define LOG(rank)   \
logger::getInstance()->start(rank, __LINE__,__FUNCTION__)
#endif