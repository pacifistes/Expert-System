#include "Reader.hpp"

Reader::Reader() {
	return;
}

Reader::~Reader() {
	return;
}

Reader::Reader(Reader const &reader) {
	*this = reader;
	return;
}

Reader & Reader::operator=(Reader const &reader) {
	(void)reader;
	return *this;
}

std::vector<std::string> Reader::readFile(const std::string &fileName) {
	std::vector<std::string> lines;
	std::string line;
	std::ifstream file(fileName);

	if (file) {
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		file.close();
	}
	return lines;
}