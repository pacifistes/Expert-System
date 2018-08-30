#ifndef SYSTEM_MANAGER_HPP
# define SYSTEM_MANAGER_HPP

# include <regex>
# include <iostream>
# include <map>
# include "EStep.hpp"
# include "Color.hpp"
# include "Rule.hpp"
# include "Fact.hpp"
# include "Logger.hpp"
# include "ParseErrorException.hpp"
# include "SDLDisplay.hpp"

class Display;

class SystemManager {
	public:
		SystemManager(Display *display);
		virtual ~SystemManager();
		void init(std::vector<std::string> lines);
		void findQueries();
		void addInitialFactsToGraph(std::string const &initialFacts);
		void setUndefinedConclusions(std::string s1, std::string s2);
		std::map<char, Fact*> _mapFact;
		void resetAllRules();

	private: 
		SystemManager();
		SystemManager(SystemManager const &systemManager);
		SystemManager & operator=(SystemManager const &systemManager);
		void addRuleToGraph(Rule *rule);
		bool isValidInfixNotation(std::string infix);
		void parseLine(std::string const &line);
		void registerLine();
		EStep _step;
		Display *_display;
		std::string _queries;
		std::cmatch _match;
		std::vector<Rule*> _rulesToDelete;
		typedef std::map<EStep const, std::string const> mapRegex;
		static mapRegex initMapRegex();
		static mapRegex _mapRegex;

};

#endif