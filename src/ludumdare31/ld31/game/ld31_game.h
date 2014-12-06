#ifndef LD31_GAME_H_
#define LD31_GAME_H_

#include "../../config.h"

typedef struct _ld31_level_ {
	SSL_Tiled_Map *map;
	dictionary *dict;
} Ld31_level;

Ld31_level *load_level(int level, Ld31_game *game);
void play_game(Ld31_game *game, int gamemode);

#endif
