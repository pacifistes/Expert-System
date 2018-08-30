#ifndef READER_HPP
# define READER_HPP

# include <string>
# include <fstream>
# include <vector>

class Reader {
	public:
		Reader();
		virtual ~Reader();
		static std::vector<std::string> readFile(const std::string &fileName);
	private:
		Reader(Reader const &operand);
		Reader & operator=(Reader const &operand);
};

#endif
