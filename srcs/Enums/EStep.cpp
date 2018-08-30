#include "EStep.hpp"
#include <iostream>


EStep & operator++(EStep & step) {
	switch (step) {
		case Rules:
			step = InitialFacts;
			break;
		default:
			step = Queries;
			break;
	}
	return step;
}

EStep operator++(EStep & step, int i) {
	(void)i;
	EStep tmp = step;
 	++step;
 	return tmp;
}