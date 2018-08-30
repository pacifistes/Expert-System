#ifndef CONFLICT_EXCEPTION_HPP
# define CONFLICT_EXCEPTION_HPP

# include <string>
# include "EFactStatus.hpp"

class ConflictException : public std::runtime_error {
	public:
		ConflictException(EFactStatus status);
		virtual ~ConflictException(void) throw();
		std::string error(EFactStatus status) const throw();
		ConflictException(ConflictException const &conflictException);
	private:
		ConflictException(void);
		ConflictException & operator=(ConflictException const &conflictException);
};

#endif