#include "../config.h"
#include "game.h"
#include "game/ld31_game.h"

void start_game(Ld31_game *game) {
	int gamemode = main_menu(game);

	if (gamemode == -1) {
		return;
	}

	play_game(game, gamemode);
}
