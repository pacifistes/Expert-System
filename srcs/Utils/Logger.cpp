#include "Logger.hpp"

Logger::Logger() {
	return;
}

Logger::~Logger() {
	return;
}

Logger::Logger(Logger const &logger) {
	*this = logger;
	return;
}

Logger & Logger::operator=(Logger const &logger) {
	(void)logger;
	return *this;
}

void Logger::log(std::ostringstream message) {
	std::ofstream log(Logger::fileName, std::ofstream::app|std::ofstream::out);
	if (log.is_open()) {
		log << message.str() << std::endl;
		log.close();
	}
}

void Logger::clearLog() {
	std::ofstream ofs;
	ofs.open(Logger::fileName, std::ofstream::trunc);
	if (ofs.is_open()) {
		ofs.close();
	}
}

std::vector<std::string> Logger::getLog() {
	return Reader::readFile(Logger::fileName);
}

const std::string Logger::fileName = "Log.txt";