#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
// #include "nuklear.h"

# include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>


// #include "nuklear.h"
// #include "nuklear_sdl_gl3.h"

class SystemManager;

class Display {
	public:
		Display();
		Display(Display const &disp);
		virtual ~Display();

		void init();
		void update(struct nk_context *ctx, struct nk_colorf *bg);
		void cleanup();
		void displayActiveRules(struct nk_context *ctx);
		void setManager(SystemManager *systemManager);
		// void displayInitialFacts(struct nk_context *ctx);
		void displayInitialFacts(struct nk_context *ctx, const struct nk_input *in, struct nk_rect *bounds);
		void displayFacts(struct nk_context *ctx);
		void displayLog(struct nk_context *ctx);
		void displayQuery(struct nk_context *ctx);

		
		std::vector<std::string> definedConclusions;
		std::vector<std::string> undefinedConclusions;
		std::vector<std::string> activeRules;
		std::vector<std::string> inactiveRules;
		std::vector<std::string> initialFacts;
		std::vector<std::string> results;
		std::string query;
		bool tableVerite[26];
		bool initialFactsState[26];
		bool undefinedSolved = false;

	  private:
		int _resolvedConclusions = 0;
	  	SystemManager *_manager;
		bool _isSolved = false;
		bool _running = true;	
		SDL_Window *_win;
		SDL_GLContext _glContext;
		int _win_width, _win_height;
};

#endif