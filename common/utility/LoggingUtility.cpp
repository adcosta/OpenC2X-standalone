#define ELPP_THREAD_SAFE
#define ELPP_NO_DEFAULT_LOG_FILE

#include <time.h>
#include <utility/LoggingUtility.h>

LoggingUtility::LoggingUtility(string moduleName) {
	mModuleName = moduleName;

	Configurations confDefault("../config/logging.conf");			//default logger for debugging
	Configurations confStatistics("../config/statistics.conf");	//statistics logger for stats

	confDefault.setRemainingToDefault();
	confDefault.setGlobally(ConfigurationType::Format, mModuleName + ", %datetime{%h:%m:%s,%g} \t %msg");
	confDefault.setGlobally(ConfigurationType::Filename, "../../logs/log_" + mModuleName + "_" + timeString() + ".log");

	confStatistics.setRemainingToDefault();
	confStatistics.setGlobally(ConfigurationType::Format, mModuleName + " \t %msg");
	confStatistics.setGlobally(ConfigurationType::Filename, "../../logs/stats_" + mModuleName + "_" + timeString() + ".csv");

	Loggers::reconfigureLogger("default_" + mModuleName, confDefault);
	Loggers::reconfigureLogger("statistics_" + mModuleName, confStatistics);
}

LoggingUtility::~LoggingUtility() {
}

string LoggingUtility::timeString() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[20];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 20, "%F_%R", timeinfo);	//format time and save in buffer

	return buffer;
}

void LoggingUtility::logStats(string messageType, long id, int64_t delay) {
	CLOG(INFO, ("statistics_" + mModuleName).c_str()) << messageType << "\t" << id << "\t" << delay;
}

void LoggingUtility::logInfo(string message) {
	CLOG(INFO, ("default_" + mModuleName).c_str()) << message;
}

void LoggingUtility::logError(string message){
	CLOG(ERROR,("default_" + mModuleName).c_str()) << "ERROR: " << message;
}

void LoggingUtility::logPError(string message){
	CPLOG(ERROR,("default_" + mModuleName).c_str()) << "ERROR: " << message;
}


