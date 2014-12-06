#include "../../config.h"
#include "entity.h"
#include "ld31_game.h"
#include "math.h"

int tile_size;
SSL_List *objects;

static void snowman_movement(Ld31_game *game, entity *e, float delta) {
		int speedx = 0;
		int speedy = 0;

		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.left)) {
			speedx -= 2.3 * delta;
		}
		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.right)) {
			speedx += 2.3 * delta;
		}
		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.down)) {
			speedy += 2.3 * delta;
		}
		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.up)) {
			speedy -= 2.3 * delta;
		}

		int x = e->x;
		int y = e->y;

		e->x += speedx;
		e->y += speedy;

		int deltaX = e->x - x;
		int deltaY = e->y - y;
		int angleInDegrees = atan2(deltaX, -deltaY) * 180 / 3.142;
		e->angle = angleInDegrees;
}

static void fireman_movment(Ld31_game *game, entity *e, float delta)  {
	int speedx = 0;
	int speedy = 0;

	if (SSL_Keybord_Keyname_Down(game->config->fireman_keys.left)) {
		speedx -= 2.5 * delta;
	}
	if (SSL_Keybord_Keyname_Down(game->config->fireman_keys.right)) {
		speedx += 2 * delta;
	}
	if (SSL_Keybord_Keyname_Down(game->config->fireman_keys.down)) {
		speedy += 2 * delta;
	}
	if (SSL_Keybord_Keyname_Down(game->config->fireman_keys.up)) {
		speedy -= 2 * delta;
	}

	int x = e->x;
	int y = e->y;

	e->x += speedx;
	e->y += speedy;

	int deltaX = e->x - x;
	int deltaY = e->y - y;
	int angleInDegrees = atan2(deltaX, -deltaY) * 180 / 3.142;
	e->angle = angleInDegrees;
}

static void handle_collision(Ld31_level *lvl, entity *e) {
	int layer = SSL_Tiled_Get_LayerIndex(lvl->map, "collsion");

	// walls
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

	// objects


}

Ld31_level *load_level(int level, Ld31_game *game) {
	Ld31_level *lvl = malloc(sizeof(Ld31_level));

	lvl->map = SSL_Tiled_Map_Load("../extras/resources/maps/test_map.tmx", game->window);
	lvl->dict = dictionary_new(0);

	tile_size = SSL_Tiled_Get_Tile_Width(lvl->map);

	return lvl;
}


static entity *spawn_snowman(Ld31_game *game, Ld31_level *lvl) {
	int  x = 0;
	int y = 0;
	int i, j;
	int layer = SSL_Tiled_Get_LayerIndex(lvl->map, "spawn");

	for (i = 0; i < SSL_Tiled_Get_Width(lvl->map); i++) {
		for (j = 0; j < SSL_Tiled_Get_Height(lvl->map); j++) {
			if (SSL_Tiled_Get_TileId(lvl->map, i , j, layer) == 2) {
				x = i * tile_size;
				y = j * tile_size;
				break;
			}
		}
	}

	entity *e = create_entity("player", SSL_Image_Load("../extras/resources/sprites/snow_man.png", 32, 32, game->window), up, x, y);;
	return e;
}

static entity *spawn_fireman(Ld31_game *game, Ld31_level *lvl) {
	int  x = 0;
	int y = 0;
	int i, j;
	int layer = SSL_Tiled_Get_LayerIndex(lvl->map, "spawn");

	for (i = 0; i < SSL_Tiled_Get_Width(lvl->map); i++) {
		for (j = 0; j < SSL_Tiled_Get_Height(lvl->map); j++) {
			if (SSL_Tiled_Get_TileId(lvl->map, i , j, layer) == 1) {
				x = i * tile_size;
				y = j * tile_size;
				break;
			}
		}
	}

	entity *e = create_entity("player", SSL_Image_Load("../extras/resources/sprites/fire_man.png", 32, 32, game->window), up, x, y);
	return e;
}

static void spawn_objects(Ld31_game *game, Ld31_level *lvl) {
	objects = SSL_List_Create();
	int  x = 0;
	int y = 0;
	int i, j;
	int layer = SSL_Tiled_Get_LayerIndex(lvl->map, "spawn");

	for (i = 0; i < SSL_Tiled_Get_Width(lvl->map); i++) {
		for (j = 0; j < SSL_Tiled_Get_Height(lvl->map); j++) {
			if (SSL_Tiled_Get_TileId(lvl->map, i , j, layer) > 2) {
				x = i * tile_size;
				y = j * tile_size;
				entity *e;

				switch (SSL_Tiled_Get_TileId(lvl->map, i , j, layer)) {
					case 3: {
						e = create_entity("box", SSL_Image_Load("../extras/resources/sprites/box.png", 32, 32, game->window), up, x, y);
						break;
					}
				}

				SSL_List_Add(objects, e);
			}
		}
	}
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

	entity *e = spawn_snowman(game, level);
	entity *e2 = spawn_fireman(game, level);
	spawn_objects(game, level);

	SSL_Font *debug_font = SSL_Font_Load("../extras/resources/font/unispace.ttf", 18);

	while (running) {
		Uint32 now = SDL_GetTicks();
		delta += (now - lastTime) / ns;
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

		SSL_Image_Draw(e->image, e->x, e->y, e->angle, 0, SDL_FLIP_NONE, game->window);
		SSL_Image_Draw(e2->image, e2->x, e2->y, e2->angle, 0, SDL_FLIP_NONE, game->window);

		int i;
		for (i = 1; i <= SSL_List_Size(objects); i++) {
			entity *q = SSL_List_Get(objects, i);
			SSL_Image_Draw(q->image, q->x, q->y, q->angle, 0, SDL_FLIP_NONE, game->window);
		}

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

