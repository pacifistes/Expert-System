#include "LoopException.hpp"

LoopException::LoopException() {
	return;
}

LoopException::~LoopException() throw() {
	return;
}

const char *LoopException::what() const throw() {
	return "LoopException: infinity loop";
}

LoopException & LoopException::operator=(LoopException const &loopException) {
	(void)loopException;
	return *this;
}

LoopException::LoopException(LoopException const &loopException) {
	*this = loopException;
	return;
}