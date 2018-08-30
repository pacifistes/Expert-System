#ifndef ESTEP_HPP
# define ESTEP_HPP

enum EStep {
	Rules,
	InitialFacts,
	Queries,
};

EStep & operator++(EStep & step);
EStep operator++(EStep & step, int i);
#endif
