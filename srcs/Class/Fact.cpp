#include "Fact.hpp"

Fact::Fact() {
	return;
}

Fact::Fact(char name) : _status(FalseDefault), _name(name) {
	return;
}

Fact::~Fact() {
	return;
}

Fact::Fact(Fact const &fact) {
	*this = fact;
	return;
}

Fact & Fact::operator=(Fact const &fact) {
	(void)fact;
	return *this;
}

void Fact::insertRule(Rule *&rule) {
	this->_rules.push_back(rule);
}

void Fact::insertFact(char c, Fact *fact) {
	this->_mapFact[c] = fact;
}

void Fact::resetAllRules()
{
	for (auto rule : _rules)
	{
		rule->setConditionValidation(false);
	}
}

void Fact::setStatus(EFactStatus status, bool isPossibleToOverride) {
	Logger::log(std::ostringstream() << "The fact " << this->_name << " is set to " << status);

	if (isPossibleToOverride == false && ((status == True && this->_status == False)
		|| (status == False && this->_status == True))) {
		throw ConflictException(this->_status);
	}
	this->_status = status;
}

EFactStatus Fact::applyOperand(EFactStatus &a, EFactStatus &b, char cOperator) {
	switch (cOperator) {
		case '+':
			return a + b;
		case '|':
			return a | b;
		default:
			return a ^ b;
	}
}

bool	Fact::isConditionValid(Rule *&rule, std::string factAlreadyPass) {
	EFactStatus statusTmp;
	std::vector<EFactStatus> statusOfCondition;
	int size;

	for (char& charCondition : rule->getCondition()) {
		size = statusOfCondition.size();
		if (std::isupper(charCondition)) {
			Logger::log(std::ostringstream() << "I search the value of the fact " << charCondition << ":");
			statusOfCondition.push_back(this->_mapFact[charCondition]->getStatusByBackwardChaining(factAlreadyPass));
		}
		else if (charCondition == '!') {
			statusTmp = !statusOfCondition[size - 1];
			statusOfCondition.pop_back();
			statusOfCondition.push_back(statusTmp);
		}
		else {
			statusTmp = this->applyOperand(statusOfCondition[size - 2], statusOfCondition[size - 1], charCondition);
			statusOfCondition.pop_back();
			statusOfCondition.pop_back();
			statusOfCondition.push_back(statusTmp);
		}
	}
	if (statusOfCondition[0] == True) {
		statusOfCondition.pop_back();
		return true;
	}
	statusOfCondition.pop_back();
	return false;
}

void	Fact::applyConclusion(std::string operation) {
	bool isFactPositive = true;
	for (char& charOperation : operation) {
		if (charOperation == '!') {
			isFactPositive = !isFactPositive;
		}
		else if (std::isupper(charOperation)) {
			if (isFactPositive == false) {
				this->_mapFact[charOperation]->setStatus(False);
				isFactPositive = true;
			}
			else {
				this->_mapFact[charOperation]->setStatus(True);
			}
		}
	}
}

char Fact::getName() {
	return this->_name;
}

EFactStatus Fact::getStatusByBackwardChaining(std::string factAlreadyPass) {
	std::string factsToCheck;
	if (factAlreadyPass.find(this->_name) != std::string::npos) {
		Logger::log(std::ostringstream() << "I already visited the fact " << this->_name << " so I return his actual value");
		return this->_status;
	}
	factAlreadyPass += this->_name;
	if (this->_rules.size() == 0 && this->_status == True) {
		Logger::log(std::ostringstream() << "There are no rules but the fact " << this->_name
		<< " is initialize to " << Color::mapColor[EColor::Green] << True << Color::mapColor[EColor::EndOfColor] );
	}
	Logger::log(std::ostringstream() << "I am looking for all the rules whose conditions are not yet valid for the fact " << this->_name);
	for (auto& rule : this->_rules) {
		if (rule->isConditionValid() == true) {
			continue;
		}
		std::string stringRule = rule->getRule();
		Logger::log(std::ostringstream() << "I check the rule " << stringRule);
		if (this->isConditionValid(rule, factAlreadyPass)) {
			rule->setConditionValidation(true);
			Logger::log(std::ostringstream() << "The condition of the rule " << stringRule << " is valid, so I apply the conclusion");
			this->applyConclusion(rule->getConclusion());
			for (char & charConclusion : rule->getConclusion()) {
				if (std::isupper(charConclusion) && factsToCheck.find(charConclusion) == std::string::npos) {
					factsToCheck += charConclusion;
				}
			}
			for (char & charCondition : rule->getCondition()) {
				if (std::isupper(charCondition) && factsToCheck.find(charCondition) == std::string::npos) {
					factsToCheck += charCondition;
				}
			}
		}
		else {
			Logger::log(std::ostringstream() << "The condition of the rule " << stringRule << " isn't valid");
		}
	}
	for (char& factToCheck : factsToCheck) {
		Logger::log(std::ostringstream() << "I look if the realized change activates new rules for the fact " << factToCheck);
		this->_mapFact[factToCheck]->getStatusByBackwardChaining();
	}
	return this->_status;
}