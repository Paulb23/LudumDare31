#include "../../config.h"
#include "ld31_game.h"


Ld31_level *load_level(int level, Ld31_game *game) {
	Ld31_level *lvl = malloc(sizeof(Ld31_level));

	lvl->map = SSL_Tiled_Map_Load("../extras/resources/maps/test_map.tmx", game->window);
	lvl->dict = dictionary_new(0);

	return lvl;
}


void play_game(Ld31_game *game) {

	int running = 1;
	SDL_Event event;

	Ld31_level *level = load_level(0, game);

	while (running) {


		SSL_Tiled_Draw_Map(level->map, 0,0, game->window);

		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}
		}
	}

}

