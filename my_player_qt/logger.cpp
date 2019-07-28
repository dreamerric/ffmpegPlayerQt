#include "logger.h"
#include <cstdlib>
#include <time.h>

std::ofstream logger::logFile;

void avLogOuput(void * ptr, int level, const char * fmt, va_list vl)
{
	if (level == AV_LOG_ERROR
		|| level == AV_LOG_WARNING
		|| level == AV_LOG_INFO
		|| level == AV_LOG_VERBOSE
		|| level == AV_LOG_FATAL
		|| level == AV_LOG_PANIC)
	{
		char buf[1024] = { 0 };
		vsprintf(buf, fmt, vl);
	    logger::getStream(level) << buf << std::flush;
	}
}
void initLogger(const std::string& logFilename)
{
	logger::getInstance()->setLogFileName(logFilename);
	logger::logFile.open(logFilename.c_str());
	av_log_set_callback(avLogOuput);
}
std::ostream& logger::getStream(int rank) {
	std::string info;
	switch (rank)
	{
	case LOG_INFO:
		info = "[INFO] ";
		break;
	case LOG_WARNING:
		info = "[WARNING] ";
		break;
	case LOG_ERROR:
		info = "[ERROR] ";
		break;
	case AV_LOG_ERROR:
		info = "[ERROR] ";
		break;
	case AV_LOG_WARNING:
		info = "[AV_LOG_WARNING] ";
		break;
	case AV_LOG_INFO:
		info = "";
		break;
	case AV_LOG_VERBOSE:
		info = "[AV_LOG_VERBOSE] ";
		break;
	case AV_LOG_DEBUG:
		info = "[AV_LOG_DEBUG] ";
		break;
	case AV_LOG_FATAL:
		info = "[AV_LOG_FATAL] ";
		break;
	case AV_LOG_PANIC:
		info = "[AV_LOG_PANIC] ";
		break;
	default:
		info = "";
		break;
	}
	if (logFile.is_open())
	{
		return logFile << info;
	}
	else
	{
		return std::cout << info;
	}
	
}

std::ostream& logger::start(int rank,
	const std::int32_t line,
	const std::string& function) {
	time_t tm;
	time(&tm);
	char time_string[128];
	ctime_s(time_string, sizeof time_string, &tm);
	return getStream(rank) << time_string
		<< "Function (" << function << ")"
		<< "Line " << line <<": "
		<< std::flush;
}

void logger::setLogFileName(const std::string & logFilename)
{
	fileName = logFilename;
}
std::string logger::getLogFileName()
{
	return fileName;
}

logger::~logger() {
	getStream(0) << std::endl << std::flush;
	logFile.close();
}
