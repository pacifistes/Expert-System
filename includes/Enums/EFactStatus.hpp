#ifndef EFACT_STATUS_HPP
# define EFACT_STATUS_HPP

# include <iostream>
# include "Color.hpp"

enum EFactStatus {
	True,
	False,
	FalseDefault
};

EFactStatus operator|(EFactStatus const &a, EFactStatus const &b);
EFactStatus operator+(EFactStatus const &a, EFactStatus const &b);
EFactStatus operator^(EFactStatus const &a, EFactStatus const &b);
EFactStatus operator!(EFactStatus const & status);
std::ostream & operator<<(std::ostream & os, EFactStatus status);
std::string operator+(std::string string, EFactStatus status);
#endif
