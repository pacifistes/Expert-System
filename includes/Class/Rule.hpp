#ifndef RULE_HPP
# define RULE_HPP

# include <string>
# include <stack>
# include <utility>

class Rule {
	public:
		Rule(std::string condition, std::string conclusion);
		virtual ~Rule();
		std::string getConclusion() const;
		std::string getCondition() const;
		std::string getRule() const;
		void setConclusion(std::string conclusion);
		bool isConditionValid();
		void setConditionValidation(bool isConditionValid);
	private:
		Rule();
		Rule(Rule const &rule);
		Rule & operator=(Rule const &rule);
		int getPrecision(char c) const;
		std::string infixToPostfix(std::string &infix);
		std::string infixToPrefix(std::string &infix);
		std::string _condition;
		std::string _conclusion;
		bool _isConditionValid;
		std::string _rule;
};

#endif