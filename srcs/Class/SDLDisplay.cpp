#include "SDLDisplay.hpp"
#include "SystemManager.hpp"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024
#define NK_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_gl3.h"

Display::Display()
{
	return;
}

Display::~Display()
{
	return;
}

Display::Display(Display const &disp)
{
	*this = disp;
	return;
}

/*
	Display de la query dans la fenetre en haut a droite
*/

void Display::setManager(SystemManager *systemManager)
{
	this->_manager = systemManager;
}

void Display::displayQuery(struct nk_context *ctx)
{
	// bool isSolved = false;
	// std::string query = "Query = ";

	if (nk_begin(ctx, "Queries", nk_rect(800, 50, 350, 300), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(ctx, 20, 3);
		nk_label_colored(ctx, "Query = ", NK_TEXT_LEFT, nk_rgb(255, 255, 255));
		nk_label_colored(ctx, this->query.c_str(), NK_TEXT_LEFT, nk_rgb(126, 255, 255));
		if (nk_button_label(ctx, "Solve query"))
		{
			_isSolved = true;
			query.clear();
			results.clear();
			_manager->findQueries();
		}
		for (size_t i = 0; _isSolved && i < this->results.size(); i++)
		{
			nk_layout_row_dynamic(ctx, 20, 1);
			nk_label_colored(ctx, this->results[i].c_str(), NK_TEXT_LEFT, nk_rgb(255, 255, 255));
		}
	}
}

/*
	Display des relations dans la fenetre du bas
*/

void Display::displayLog(struct nk_context *ctx)
{
	Logger logger;
	std::vector<std::string> logs = logger.getLog();
	if (nk_begin(ctx, "Logs", nk_rect(50, 400, 730, 300), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
			nk_layout_row_dynamic(ctx, 20, 1);
			for (unsigned int i = 0; i < logs.size(); i++)
				nk_label_colored(ctx, logs[i].c_str(), NK_TEXT_LEFT, nk_rgb(255, 255, 255));
			
	}
}

/*
	Display des faits initiaux dans la fenetre en haut a gauche
*/

void Display::displayInitialFacts(struct nk_context *ctx, const struct nk_input *in, struct nk_rect *bounds)
{
	std::string convert;
	if (nk_begin(ctx, "Initial Facts", nk_rect(50, 50, 230, 300), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(ctx, 35, 5);
		for (size_t i = 0; i < 6; i++)
		{
			for (size_t j = 0; ((i * 5 + j) < 26) && j < 5; j++)
			{
				convert = char(i * 5 + j + 'A');
				if (initialFactsState[i * 5 + j])
				{
					*bounds = nk_widget_bounds(ctx);
					nk_button_label(ctx, convert.c_str());
					convert = "This fact was initialized in the description file.";
					if (nk_input_is_mouse_hovering_rect(in, *bounds))
						nk_tooltip(ctx, convert.c_str());
				}
			}
		}
	}
}

/*
	Display des faits actuels dans la deuxieme fenetre du haut
*/

void Display::displayFacts(struct nk_context *ctx)
{
	if (nk_begin(ctx, "Facts", nk_rect(300, 50, 230, 300), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		std::string convert;
		for (size_t i = 0; i < 6; i++)
		{
			// printf("[ ");
			nk_layout_row_dynamic(ctx, 35, 5);
			for (size_t j = 0; ((i * 5 + j) < 26) && j < 5; j++)
			{
				ctx->style.button.normal = nk_style_item_color(nk_rgba(120 * !tableVerite[i * 5 + j], 120 * tableVerite[i * 5 + j], 0, 255));
				convert = char(i * 5 + j + 'A');
				// printf("%d ", (int)tableVerite[i * 5 + j]);
				if (nk_button_label(ctx, convert.c_str()))
				{
					tableVerite[i * 5 + j] = !tableVerite[i * 5 + j];


					if (_manager->_mapFact.find(i * 5 + j + 'A') == _manager->_mapFact.end())
						_manager->_mapFact[i * 5 + j + 'A'] = new Fact(i * 5 + j + 'A');

					_manager->_mapFact[i * 5 + j + 'A']->setStatus(
						tableVerite[i * 5 + j] == true ? 
						True :
						False,
						true
					);





				}
			}
		// printf("]\n");
		}
		// printf(" \n\n\n");
		ctx->style.button.normal = nk_style_item_color(nk_rgba(40, 40, 40, 255));
	}
}

/*
	Display des regles dans la troisieme fenetre du haut
*/

void Display::displayActiveRules(struct nk_context *ctx)
{
	if (nk_begin(ctx, "Rules", nk_rect(550, 50, 230, 300), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label_colored(ctx, "Enabled Rules", NK_TEXT_LEFT, nk_rgb(0, 255, 0));
		for (size_t i = 0; i < activeRules.size(); i++)
		{
			nk_layout_row_dynamic(ctx, 20, 2);
			nk_label_colored(ctx, activeRules[i].c_str(), NK_TEXT_LEFT, nk_rgb(255, 255, 255));
			if (nk_button_label(ctx, "Disable"))
			{
				inactiveRules.push_back(activeRules[i]);
				activeRules.erase(activeRules.begin() + i);
			}
		}
		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label_colored(ctx, "Disabled Rules", NK_TEXT_LEFT, nk_rgb(255, 0, 0));
		for (size_t i = 0; i < inactiveRules.size(); i++)
		{
			nk_layout_row_dynamic(ctx, 20, 2);
			nk_label_colored(ctx, inactiveRules[i].c_str(), NK_TEXT_LEFT, nk_rgb(255, 255, 255));
			if (nk_button_label(ctx, "Enable"))
			{
				activeRules.push_back(inactiveRules[i]);
				inactiveRules.erase(inactiveRules.begin() + i);
			}
		}
	}
}

/*
	Boucle de "Gameplay"
	Chaque fonction d'affichage est rappelee 
	a chaque frame (peut etre a changer en "new frame on change")
*/

void Display::update(struct nk_context *ctx, struct nk_colorf *bg)
{
	/* Input */
	const struct nk_input *in = &ctx->input;
	struct nk_rect bounds;
	SDL_Event evt;
	nk_input_begin(ctx);
	while (SDL_PollEvent(&evt))
	{
		if (evt.type == SDL_QUIT || (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE))
			_running = false;
		nk_sdl_handle_event(&evt);
	}
	
	this->displayInitialFacts(ctx, in, &bounds);	
	nk_end(ctx);

	this->displayFacts(ctx);	
	nk_end(ctx);
	
	this->displayActiveRules(ctx);	
	nk_end(ctx);

	this->displayQuery(ctx);	
	nk_end(ctx);

	this->displayLog(ctx);
	nk_end(ctx);

	nk_input_end(ctx);

	


	// Draw
	SDL_GetWindowSize(_win, &_win_width, &_win_height);
	glViewport(0, 0, _win_width, _win_height);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(bg->r, bg->g, bg->b, bg->a);
	nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
	SDL_GL_SwapWindow(_win);
}

/*
	Fonction de nettoyage de la SDL et de Nuklear
*/

void Display::cleanup()
{
	nk_sdl_shutdown();
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_win);
	SDL_Quit();
}

/*
	Initialisation de la SDL et de Nuklear, la fonction update est appellee dans init
*/

void Display::init()
{
	struct nk_context *ctx;
	struct nk_colorf bg;
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	_win = SDL_CreateWindow("Expert-System",
						   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						   WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
	_glContext = SDL_GL_CreateContext(_win);
	SDL_GetWindowSize(_win, &_win_width, &_win_height);

	/* OpenGL setup */
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glewExperimental = 1;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to setup GLEW\n");
		exit(1);
	}
	ctx = nk_sdl_init(_win);
	{
		struct nk_font_atlas *atlas;
		nk_sdl_font_stash_begin(&atlas);
		nk_sdl_font_stash_end();
	}
	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
	for (size_t i = 0; i < 26; i++)
		initialFactsState[i] = tableVerite[i];
	// _manager->setUndefinedConclusions("A", "!A");
	// _manager->setUndefinedConclusions("B", "!B");
	// _manager->setUndefinedConclusions("C", "!C");
	// _manager->setUndefinedConclusions("D", "!D");
	// _manager->setUndefinedConclusions("E", "!E");
	std::cout << "undefinedsolved = " << this->undefinedSolved << '\n';
	while (_running)
	{
		this->update(ctx, &bg);
	}
	this->cleanup();
}