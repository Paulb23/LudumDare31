#include "config.h"
#include "../SSL/SSL.h"

static const char *CONFIG_PATH = "../conf/config.ini";


static SSL_Window *ld31_create_window(Ld31_config *config) {
	return SSL_Window_Create(config->title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config->window_width, config->window_height, 0,0, 0);
}


Ld31_config *ld31_loadConfig() {
	dictionary *dict = dictionary_new(0);
	dict = iniparser_load(CONFIG_PATH);

	Ld31_config *config = malloc(sizeof(Ld31_config));

	config->title = iniparser_getstring(dict, "display:title", "LD 31!");
	config->window_height = iniparser_getint(dict, "display:window_height", 600);
	config->window_width  = iniparser_getint(dict, "display:window_width",  800);
	config->window_res_height = iniparser_getint(dict, "display:window_res_height", 800);
	config->window_res_width  = iniparser_getint(dict, "display:window_res_width",  600);
	config->frames_per_second = iniparser_getint(dict, "display:frames_per_second",  60);

	return config;
}


Ld31_game *ld31_loadgame(Ld31_config *config) {
	Ld31_game * game = malloc(sizeof(Ld31_game));
	game->config = config;
	game->window = ld31_create_window(config);

	return game;
}
