#ifndef PARSE_ERROR_EXCEPTION_HPP
# define PARSE_ERROR_EXCEPTION_HPP

# include <string>
# include "EStep.hpp"

class ParseErrorException : public std::exception {
	public:
		ParseErrorException(EStep step);
		virtual ~ParseErrorException(void) throw();
		virtual const char *what() const throw();
		ParseErrorException(ParseErrorException const &parseErrorException);
	private:
		ParseErrorException(void);
		ParseErrorException & operator=(ParseErrorException const &parseErrorException);
		EStep _step;
};

#endif