#ifndef FACT_HPP
# define FACT_HPP

# include <vector>
# include <regex>
# include <map>
# include <iostream>
# include "Rule.hpp"
# include "Logger.hpp"
# include "EFactStatus.hpp"
# include "LoopException.hpp"
# include "ConflictException.hpp"

class Fact {
	public:
		Fact(char name);
		virtual ~Fact();
		void insertRule(Rule *&rule);
		void insertFact(char c, Fact *fact);
		void setStatus(EFactStatus status, bool isPossibleToOverride = false);
		char getName();
		EFactStatus getStatusByBackwardChaining(std::string factAlreadyPass = "");
	private:
		Fact();
		Fact(Fact const &fact);
		Fact & operator=(Fact const &fact);
		EFactStatus applyOperand(EFactStatus &a, EFactStatus &b, char cOperator);
		bool isConditionValid(Rule *&rule, std::string factAlreadyPass);
		void applyConclusion(std::string operation);
		EFactStatus _status;
		char _name;
		std::vector<Rule*> _rules;
		std::map<char, Fact*> _mapFact;
};

#endif