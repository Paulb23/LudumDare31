#include "../../config.h"
#include "entity.h"
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
	entity *e = create_entity("player", SSL_Image_Load("../extras/resources/sprites/player.png", 32, 32, game->window), up, 100, 100);
	entity *e2 = create_entity("player", SSL_Image_Load("../extras/resources/sprites/player.png", 32, 32, game->window), up, 100, 100);

	while (running) {
		SDL_RenderPresent(game->window->renderer);
		SDL_RenderClear(game->window->renderer);

		SSL_Tiled_Draw_Map(level->map, 0, 0, game->window);
		SSL_Image_Draw(e->image, e->x, e->y, 0, 0, SDL_FLIP_NONE, game->window);
		SSL_Image_Draw(e2->image, e2->x, e2->y, 0, 0, SDL_FLIP_NONE, game->window);

		if (SSL_Keybord_Keyname_Down("_a")) {
			e->x -= 1;
		}
		if (SSL_Keybord_Keyname_Down("_d")) {
				e->x += 1;
			}
		if (SSL_Keybord_Keyname_Down("_s")) {
				e->y += 1;
			}
		if (SSL_Keybord_Keyname_Down("_w")) {
				e->y -= 1;
			}

		if (SSL_Keybord_Keyname_Down("_left")) {
			e2->x -= 1;
		}
		if (SSL_Keybord_Keyname_Down("_right")) {
				e2->x += 1;
			}
		if (SSL_Keybord_Keyname_Down("_down")) {
				e2->y += 1;
			}
		if (SSL_Keybord_Keyname_Down("_up")) {
				e2->y -= 1;
			}

		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
				break;
			}
		}

	}

}

