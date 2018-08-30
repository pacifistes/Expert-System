#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "Color.hpp"
#include "Reader.hpp"
#include "SDLDisplay.hpp"
#include "SystemManager.hpp"

int main(int ac, char **av) {
	Display *display = new Display();
	SystemManager manager(display);
	display->setManager(&manager);
	std::vector<std::string> lines;
	if ((ac < 2 || ac > 3) || (ac == 3 && strcmp(av[1], "-g"))) {
		std::cerr << "Usage:         ./expert-system [options] [file]." << std::endl;
		std::cerr << "Options:       [-g]: Starts the graphical version" << std::endl;
		return EXIT_FAILURE;
	}
	lines = Reader::readFile(av[ac - 1]);
	if (lines.empty()) {
		std::cerr << Color::mapColor[EColor::Red] << "error: " << Color::mapColor[EColor::EndOfColor];
		std::cerr << Color::mapColor[EColor::White] << " problem while reading the file." << Color::mapColor[EColor::EndOfColor] << std::endl;
		return EXIT_FAILURE;
	}
	manager.init(lines);
	if (!strcmp(av[1], "-g")) {
		display->init();
	}
	else
		manager.findQueries();  // On test avec le manager inclu dans le display
	return EXIT_SUCCESS;
}
