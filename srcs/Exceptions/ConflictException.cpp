#include "ConflictException.hpp"

ConflictException::ConflictException() : runtime_error("ConflictException: the fact have opposite rules") {
	return;
}

ConflictException::ConflictException(EFactStatus status) : runtime_error(error(status)) {
	return;
}

ConflictException::~ConflictException() throw() {
	return;
}

std::string ConflictException::error(EFactStatus status) const throw() {
	return (Color::mapColor[EColor::Red] + "ConflictException" + Color::mapColor[EColor::EndOfColor] + Color::mapColor[EColor::White] + ": the fact was already set to " + status);
}

ConflictException & ConflictException::operator=(ConflictException const &loopException) {
	(void)loopException;
	return *this;
}

ConflictException::ConflictException(ConflictException const &loopException) : runtime_error("ConflictException: the fact have opposite rules") {
	*this = loopException;
	return;
}