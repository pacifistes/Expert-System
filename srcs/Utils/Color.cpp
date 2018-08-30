#include "Color.hpp"

Color::Color() {
	return;
}

Color::~Color() {
	return;
}

Color::Color(Color const &color) {
	*this = color;
	return;
}

Color & Color::operator=(Color const &color) {
	(void)color;
	return *this;
}

std::map<EColor const, std::string const> Color::initMapColor() {
	std::map<EColor const, std::string const> mapColor = {
		{EColor::Red, ""},
		{EColor::White, ""},
		{EColor::Green, ""},
		{EColor::EndOfColor, ""}
	};
	return mapColor;
}

std::map<EColor const, std::string const> Color::mapColor = initMapColor();
