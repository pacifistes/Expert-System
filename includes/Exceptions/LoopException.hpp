#ifndef LOOP_EXCEPTION_HPP
# define LOOP_EXCEPTION_HPP

# include <string>

class LoopException : public std::exception {
	public:
		LoopException(void);				
		virtual ~LoopException(void) throw();
		virtual const char *what() const throw();
		LoopException(LoopException const &loopException);
	private:
		LoopException & operator=(LoopException const &loopException);
};

#endif