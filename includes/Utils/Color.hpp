#ifndef COLOR_HPP
# define COLOR_HPP

# include <string>
# include <map>
# include "EColor.hpp"

class Color {
	public:
		Color();
		virtual ~Color();
		static std::map<EColor const, std::string const> mapColor;

	private:
		Color(Color const &operand);
		Color & operator=(Color const &operand);
		static std::map<EColor const, std::string const> initMapColor();
};

#endif
