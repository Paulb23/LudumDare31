#include "../../config.h"
#include "entity.h"
#include "ld31_game.h"

int tile_size;

static void snowman_movement(Ld31_game *game, entity *e, float delta) {
		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.left)) {
			e->x -= 2 * delta;
		}
		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.right)) {
				e->x += 2 * delta;
		}
		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.down)) {
				e->y += 2 * delta;
		}
		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.up)) {
				e->y -= 2 * delta;
		}
}

static void fireman_movment(Ld31_game *game, entity *e, float delta)  {
	if (SSL_Keybord_Keyname_Down(game->config->fireman_keys.left)) {
		e->x -= 2 * delta;
	}
	if (SSL_Keybord_Keyname_Down(game->config->fireman_keys.right)) {
			e->x += 2 * delta;
	}
	if (SSL_Keybord_Keyname_Down(game->config->fireman_keys.down)) {
			e->y += 2 * delta;
	}
	if (SSL_Keybord_Keyname_Down(game->config->fireman_keys.up)) {
			e->y -= 2 * delta;
	}

}

static void handle_collision(Ld31_level *lvl, entity *e) {
	int layer = SSL_Tiled_Get_LayerIndex(lvl->map, "collsion");

	if (SSL_Tiled_Get_TileId(lvl->map, (e->x / tile_size) + 1, (e->y / tile_size), layer) == 1) {			// right
		while (SSL_Tiled_Get_TileId(lvl->map, (e->x / tile_size) + 1, (e->y / tile_size), layer) == 1) {
			e->x -= 1;
		}
	}

	if (SSL_Tiled_Get_TileId(lvl->map, ((e->x + tile_size) / tile_size) - 1, (e->y / tile_size), layer) == 1) {			// left
		while (SSL_Tiled_Get_TileId(lvl->map, ((e->x + tile_size) / tile_size) - 1, (e->y / tile_size), layer) == 1) {
			e->x += 1;
		}
	}

	if (SSL_Tiled_Get_TileId(lvl->map, (e->x / tile_size), ((e->y )/ tile_size) + 1, layer) == 1) {			// down
		while (SSL_Tiled_Get_TileId(lvl->map, (e->x / tile_size), ((e->y ) / tile_size) + 1, layer) == 1) {
			e->y -= 1;
		}
	}

	if (SSL_Tiled_Get_TileId(lvl->map, (e->x / tile_size), ((e->y - tile_size) / tile_size), layer) == 1) {			// up
		while (SSL_Tiled_Get_TileId(lvl->map, (e->x / tile_size), ((e->y - tile_size) / tile_size), layer) == 1) {
			e->y += 1;
		}
	}
}

Ld31_level *load_level(int level, Ld31_game *game) {
	Ld31_level *lvl = malloc(sizeof(Ld31_level));

	lvl->map = SSL_Tiled_Map_Load("../extras/resources/maps/test_map.tmx", game->window);
	lvl->dict = dictionary_new(0);

	tile_size = SSL_Tiled_Get_Tile_Width(lvl->map);

	return lvl;
}


void play_game(Ld31_game *game) {

	int running = 1;
	SDL_Event event;

	long lastTime = SDL_GetTicks();
	const double ns = 1000.0 / MAX_TICKS_PER_SECOND;
	Uint32 timer = SDL_GetTicks();
	float delta = 0;
	double fps = 0;
	double tick = 0;
	double s_fps = 0;

	Ld31_level *level = load_level(0, game);
	entity *e = create_entity("player", SSL_Image_Load("../extras/resources/sprites/snow_man.png", 32, 32, game->window), up, 100, 100);
	entity *e2 = create_entity("player", SSL_Image_Load("../extras/resources/sprites/fire_man.png", 32, 32, game->window), up, 400, 400);

	SSL_Font *debug_font = SSL_Font_Load("../extras/resources/font/unispace.ttf", 18);

	while (running) {
		Uint32 now = SDL_GetTicks();					// get the current time
		delta += (now - lastTime) / ns;				// calculate the time passed since our last update
		lastTime = now;

		SDL_RenderPresent(game->window->renderer);
		SDL_RenderClear(game->window->renderer);

		while (delta >= 1) {
			snowman_movement(game, e, delta);
			fireman_movment(game, e2, delta);

			handle_collision(level, e);
			handle_collision(level, e2);

			while(SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					running = 0;
					break;
				}
			}

			tick++;
			delta--;
		}
		fps++;

		SSL_Tiled_Draw_Map(level->map, 0, -32, game->window);
		SSL_Image_Draw(e->image, e->x, e->y, 0, 0, SDL_FLIP_NONE, game->window);
		SSL_Image_Draw(e2->image, e2->x, e2->y, 0, 0, SDL_FLIP_NONE, game->window);

		char buf[3];
		itoa(s_fps, buf, 10);
		SSL_Font_Draw(0, 0, 0 ,SDL_FLIP_NONE, "FPS:", debug_font, SSL_Color_Create(0,0,0,0), game->window);
		SSL_Font_Draw(55, 0, 0 ,SDL_FLIP_NONE, buf, debug_font, SSL_Color_Create(0,0,0,0), game->window);

		if (SDL_GetTicks() - timer > 1000) {
			timer += 1000;
			s_fps = fps;
			fps = 0;
			tick = 0;
		}
	}
}

