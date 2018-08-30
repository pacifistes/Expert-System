#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>
# include <fstream>
# include <sstream>
# include <vector>
# include "Reader.hpp"
class Logger {
	public:
		Logger();
		virtual ~Logger();
		static void log(std::ostringstream message);
		static void clearLog();
		static std::vector<std::string> getLog();
	private:
		static const std::string fileName;
		Logger(Logger const &operand);
		Logger & operator=(Logger const &operand);
};

#endif
