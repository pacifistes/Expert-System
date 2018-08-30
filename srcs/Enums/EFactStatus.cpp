# include "EFactStatus.hpp"

EFactStatus operator|(EFactStatus const &a, EFactStatus const &b) {
	if (a == True || b == True) {
		return True;
	}
	return False;
}

EFactStatus operator+(EFactStatus const &a, EFactStatus const &b) {
	if (a == True && b == True) {
		return True;
	}
	return False;
}

EFactStatus operator^(EFactStatus const &a, EFactStatus const &b) {
	if ((a == True && (b == False || b == FalseDefault))
		|| (b == True && (a == False || a == FalseDefault))) {
		return True;
	}
	return False;
}

EFactStatus operator!(EFactStatus const &status) {
	if (status == False || status == FalseDefault)
		return True;
	return False;
}

std::ostream & operator<<(std::ostream & os, EFactStatus status) {
	switch(status)
	{
		case True:
			os << Color::mapColor[EColor::Green] << "true" << Color::mapColor[EColor::EndOfColor];
			break;
		case False:
			os << Color::mapColor[EColor::Red] << "false" << Color::mapColor[EColor::EndOfColor];
			break;
		default:
			os << Color::mapColor[EColor::Red] << "false by default" << Color::mapColor[EColor::EndOfColor];
			break;
	}
	return os;
}

std::string operator+(std::string string, EFactStatus const status) {
	switch(status)
	{
		case True:
			string = string + Color::mapColor[EColor::Green] + "true" + Color::mapColor[EColor::EndOfColor];
			break;
		case False:
			string = string + Color::mapColor[EColor::Red] + "false" + Color::mapColor[EColor::EndOfColor];
			break;
		default:
			string = string + Color::mapColor[EColor::Red] + "false by default" + Color::mapColor[EColor::EndOfColor];
			break;
	}
	return string;
}