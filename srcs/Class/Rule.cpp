#include "Rule.hpp"

Rule::Rule(std::string condition, std::string conclusion) :	_condition(infixToPostfix(condition)),
															_conclusion(infixToPrefix(conclusion)),
															_isConditionValid(false),
															_rule(condition + " => " + conclusion) {
	return;
}

Rule::Rule() {
	return;
}

Rule::~Rule() {
	return;
}

Rule::Rule(Rule const &rule) {
	*this = rule;
	return;
}

Rule & Rule::operator=(Rule const &rule) {
	(void)rule;
	return *this;
}

int Rule::getPrecision(char c) const {
	if (c == '!')
		return 4;
	else if(c == '+')
		return 3;
	else if(c == '|')
		return 2;
	else if(c == '^')
		return 1;
	else
		return -1;
}

std::string Rule::getRule() const {
	return this->_rule;
}

std::string Rule::getConclusion() const {
	return this->_conclusion;
}

std::string Rule::getCondition() const {
	return this->_condition;
}

void Rule::setConclusion(std::string conclusion) {
	this->_conclusion = conclusion;
}

bool Rule::isConditionValid() {
	return this->_isConditionValid;
}

void Rule::setConditionValidation(bool isConditionValid) {
	this->_isConditionValid = isConditionValid;
}

std::string Rule::infixToPostfix(std::string &infix) {
	std::stack<char> stack;
	std::string postfix;

	infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());
	for(size_t i = 0; i < infix.length(); i++) {
		if(std::isupper(infix[i])) {
			postfix+=infix[i];
		}
 		else if(infix[i] == '(') {
			stack.push('(');
		}
		else if(infix[i] == ')') {
			while(stack.size() > 0) {
				if(stack.top() == '(') {
					stack.pop();
					break;
				}
				postfix += stack.top();
				stack.pop();
			}
		}
		else {
			while(stack.size() > 0 && this->getPrecision(infix[i]) <= this->getPrecision(stack.top())) {
				postfix += stack.top();
				stack.pop();
			}
			stack.push(infix[i]);
		}
	}
	while(stack.size() > 0) {
		postfix += stack.top();
		stack.pop();
	}
	return postfix;
}

std::string Rule::infixToPrefix(std::string &infix) {
	std::string postfix;
	postfix = this->infixToPostfix(infix);
	return std::string(postfix.rbegin(), postfix.rend());
}