#include "../config.h"
#include "game.h"
#include "game/ld31_game.h"

void start_game(Ld31_config *config) {

	Ld31_game *game = ld31_loadgame(config);
	play_game(game);
}
