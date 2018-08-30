#include "SystemManager.hpp"

SystemManager::SystemManager() {
	return;
}

SystemManager::SystemManager(Display *display) : _step(Rules), _display(display) {
	return;
}

SystemManager::~SystemManager() {
	std::string factsToDelete;
	while (this->_rulesToDelete.size() > 1) {
		delete this->_rulesToDelete[0];
		this->_rulesToDelete.erase(this->_rulesToDelete.begin());
	}
	for (auto mapFact: this->_mapFact) {
		factsToDelete += mapFact.first;
	}
	for (char& factToDelete : factsToDelete) {
		delete this->_mapFact[factToDelete];
		this->_mapFact.erase(factToDelete);
	}
	return;
}

SystemManager::SystemManager(SystemManager const &systemManager) {
	*this = systemManager;
	return;
}

SystemManager & SystemManager::operator=(SystemManager const &systemManager) {
	(void)systemManager;
	return *this;
}

void SystemManager::setUndefinedConclusions(std::string s1, std::string s2) {
	_display->undefinedConclusions.push_back(s1 + "," + s2);
	_display->undefinedSolved = false;
}

void SystemManager::parseLine(std::string const &line) {
	if (!std::regex_search(line.c_str(), this->_match, std::regex(SystemManager::_mapRegex[this->_step]))) {
		this->_step++;
	}
	if (!std::regex_search(line.c_str(), this->_match, std::regex(SystemManager::_mapRegex[this->_step]))
		|| (this->_step == Rules && (!this->isValidInfixNotation(this->_match[1]) || !this->isValidInfixNotation(this->_match[2])))) {
			throw ParseErrorException(this->_step++);
	}
	if (_step == Rules)
		_display->activeRules.push_back(line);
}

bool	SystemManager::isValidInfixNotation(std::string infix) {
	bool isLastWasOperand = false;
	infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());
	for (size_t i = 0; i < infix.length(); i++) {
		if (std::isupper(infix[i])) {
			if (isLastWasOperand == true) {
				return false;
			}
			isLastWasOperand = true;
		}
		if (infix[i] == '+' || infix[i] == '|' || infix[i] == '^') {
			if (isLastWasOperand == false) {
				return false;
			}
			isLastWasOperand = false;
		}
	}
	if (isLastWasOperand == false || std::count(infix.begin(), infix.end(), '(') != std::count(infix.begin(), infix.end(), ')')) {
		return false;
	}
	return true;
}

void	SystemManager::addRuleToGraph(Rule *rule) {
	std::string condition = rule->getCondition();
	std::string conclusion = rule->getConclusion();
	std::string factsOfConclusion;
	this->_rulesToDelete.push_back(rule);
	for (char& charConclusion : conclusion) {
		if (std::isupper(charConclusion)) {
			if (factsOfConclusion.find(charConclusion) == std::string::npos) {
				factsOfConclusion += charConclusion;
			}
			if (this->_mapFact.find(charConclusion) == this->_mapFact.end()) {
				this->_mapFact[charConclusion] = new Fact(charConclusion);
			}
			this->_mapFact[charConclusion]->insertRule(rule);
			for (char& charCondition : condition) {
				if (std::isupper(charCondition)) {
					if (this->_mapFact.find(charCondition) == this->_mapFact.end()) {
						this->_mapFact[charCondition] = new Fact(charCondition);
					}
					this->_mapFact[charConclusion]->insertFact(charCondition, this->_mapFact[charCondition]);
				}
			}
		}
	}
	for (char & charFact : factsOfConclusion) {
		for (char & charFactToInsert : factsOfConclusion) {
			this->_mapFact[charFact]->insertFact(charFactToInsert, this->_mapFact[charFactToInsert]);
		}
	}
}

void	SystemManager::resetAllRules(void)
{
	for (auto fact : this->_mapFact)
	{
		fact.second->resetAllRules();
	}
}

void	SystemManager::addInitialFactsToGraph(std::string const &initialFacts) {
	for (const char & charFact : initialFacts) {
		if (this->_mapFact.find(charFact) == this->_mapFact.end()) {
			this->_mapFact[charFact] = new Fact(charFact);
		}
		this->_mapFact[charFact]->setStatus(True);
		this->_display->tableVerite[charFact - 'A'] = true;
	}
}

void SystemManager::registerLine() {
	switch (this->_step) {
		case Rules:
			this->addRuleToGraph(new Rule(this->_match[1], this->_match[2]));
			break;
		case InitialFacts:
			this->addInitialFactsToGraph(this->_match[1]);
			this->_step++;
			break;
		default:
			this->_queries = this->_match[1];
			break;
	}
}

void SystemManager::init(std::vector<std::string> lines) {
	int iterator;

	iterator = 0;
	for (auto line : lines) {
		if (!line.empty() && !std::regex_match(line, std::regex("^(?:\\s*#.*)?$"))) {
			try {
				this->parseLine(line);
			}
			catch (std::exception const & e) {
				std::cerr << Color::mapColor[EColor::White] << "line:" << iterator + 1 << ": ";
				std::cerr << Color::mapColor[EColor::Red]  << "error: " << Color::mapColor[EColor::EndOfColor];
				std::cerr << Color::mapColor[EColor::White] << e.what() << " : " << std::endl;
				std::cerr << Color::mapColor[EColor::EndOfColor] << Color::mapColor[EColor::Green]  << "> ";
				std::cerr << Color::mapColor[EColor::EndOfColor] << line << std::endl;
				std::exit(EXIT_FAILURE);
			}
			this->registerLine();
			if (!this->_queries.empty()) {
				return;
			}
		}
		iterator++;
	}
}

void SystemManager::findQueries() {
	EFactStatus status;
	Logger::clearLog();
	Logger::log(std::ostringstream() << "Start of resolution:\n");
	resetAllRules();
	for (const char& charFact : this->_queries) {
		std::stringstream resultPerChar;
		_display->query += charFact;
		Logger::log(std::ostringstream() << "I search the value of the fact " << charFact << ":");
		if (this->_mapFact.find(charFact) == this->_mapFact.end()) {
			Logger::log(std::ostringstream() << "No rule or initial fact found");
			Logger::log(std::ostringstream() << Color::mapColor[EColor::White] << "The fact " << charFact << " is " << Color::mapColor[EColor::EndOfColor] << FalseDefault);
			resultPerChar << "The fact " << charFact << " is False";
			this->_display->tableVerite[charFact - 'A'] = false; //TOCHECK
			_display->results.push_back(resultPerChar.str());
		}
		else {
			try {
				status = this->_mapFact[charFact]->getStatusByBackwardChaining();
			}
			catch (std::exception const & e) {//A Definir ce que l'on fait
				Logger::log(std::ostringstream() << e.what());
				std::exit(EXIT_FAILURE);
			}
			Logger::log(std::ostringstream() << this->_mapFact[charFact]->getName());

		Logger::log(std::ostringstream() << Color::mapColor[EColor::White] << "The fact " << charFact << " is " << Color::mapColor[EColor::EndOfColor] << status);
		if (status == True) {
			this->_display->tableVerite[charFact - 'A'] = true; //TOCHECK
			resultPerChar << "The fact " << charFact << " is True";
		}
		else {
			this->_display->tableVerite[charFact - 'A'] = false; //TOCHECK
			resultPerChar << "The fact " << charFact << " is False";
		}
		_display->results.push_back(resultPerChar.str());
		(void)status;
		}
	}
}

SystemManager::mapRegex SystemManager::initMapRegex() {
	SystemManager::mapRegex mapRegex = {
		{Rules, "^((?:[\\s\\!]*\\(?[\\s\\!]*[A-Z]\\s*\\)?|\\+|\\||\\^|\\s)+)=>((?:\\s*\\(?[\\s\\!]*[A-Z]\\s*\\)?|\\+|\\s)+)(?:#.*)?$"},
		{InitialFacts, "^=([A-Z]*)?(?:\\s*#.*)?$"},
		{Queries, "^\\?([A-Z]+)(?:\\s*#.*)?"}
	};
	return mapRegex;
}

SystemManager::mapRegex SystemManager::_mapRegex = initMapRegex();