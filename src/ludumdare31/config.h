#ifndef CONFIG_H_
#define CONFIG_H_

#include "../SSL/SSL.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_Image.h"
#include "SDL2/SDL_Mixer.h"

SSL_Image *cursor;

int mute;

typedef struct _ld31_keys_ {
	char *up;
	char *down;
	char *left;
	char *right;
} ld31_keys;


typedef struct _LD31_Config_ {
	char *title;
	int window_width;
	int window_height;
	int window_res_width;
	int window_res_height;
	int frames_per_second;
	ld31_keys snowman_keys;
	char *open_shop;
	char *start_round;
	char *mute;
} Ld31_config;

typedef struct _LD31_Game_ {
	Ld31_config *config;
	SSL_Window *window;
} Ld31_game;

Ld31_config *ld31_loadConfig();

Ld31_game *ld31_loadgame(Ld31_config *config);

#endif
