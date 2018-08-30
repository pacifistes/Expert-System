#include "ParseErrorException.hpp"

ParseErrorException::ParseErrorException() {
	return;
}

ParseErrorException::ParseErrorException(EStep step) : _step(step) {

}

ParseErrorException::~ParseErrorException() throw() {
	return;
}

const char *ParseErrorException::what() const throw() {
	if (this->_step == InitialFacts || this->_step == Rules)
		return "ParseErrorException: the line should be a rule or an Initial facts";
	return "ParseErrorException: the line should be a query";
}

ParseErrorException & ParseErrorException::operator=(ParseErrorException const &parseErrorException) {
	(void)parseErrorException;
	return *this;
}

ParseErrorException::ParseErrorException(ParseErrorException const &parseErrorException) {
	*this = parseErrorException;
	return;
}