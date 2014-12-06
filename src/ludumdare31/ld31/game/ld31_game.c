#include "../../config.h"
#include "entity.h"
#include "ld31_game.h"
#include "math.h"

#define PI 3.14159265359

int tile_size;
SSL_List *snowballs;
long last_shot = 0;

static void snowman_movement(Ld31_game *game, entity *e, float delta) {
		int x;
		int y;

		SDL_GetMouseState(&x,&y);

		int deltaX = x - e->x ;
		int deltaY = y - e->y;
		int angleInDegrees = atan2(deltaX, -deltaY) * 180 / PI;
		e->angle = angleInDegrees;

		double radians = (e->angle * PI) / 180;
		int speed = 3 * delta;

		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.left)) {
			e->x -= speed * cos(radians);
			e->y -= speed * sin(radians);
		}

		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.right)) {
			e->x += speed * cos(radians);
			e->y += speed * sin(radians);
		}

		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.up)) {
			e->x += speed * sin(radians);
			e->y -= speed * cos(radians);
		}

		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.down)) {
			e->x -= speed * sin(radians);
			e->y += speed * cos(radians);
		}
}

static void update_snowballs(float delta) {
	int speed = 3 * delta;
	int i;
	for (i = 1; i < SSL_List_Size(snowballs); i++) {
		Snowball *e = SSL_List_Get(snowballs, i);

		double radians = (e->entity->angle * PI) / 180;
		e->entity->x += speed * sin(radians);
		e->entity->y -= speed * cos(radians);

		if (SDL_GetTicks() > e->deletion_time || e->entity->x > 768 || e->entity->y > 768 || e->entity->x < 0 || e->entity->y < 0) {
			SSL_List_Remove(snowballs, e);
			SSL_Image_Destroy(e->entity->image);
			free(e->entity);
			free(e);
		}

	}
}

static void snowman_shoot(Ld31_game *game, int x, int y, int angle) {
	Snowball *e = malloc(sizeof(Snowball));
	e->entity = create_entity("snowball", SSL_Image_Load("../extras/resources/sprites/snowball.png", 16, 16, game->window), up, x, y);
	e->entity->angle = angle;
	e->deletion_time = SDL_GetTicks() + 4000;
	SSL_List_Add(snowballs, e);
	last_shot = SDL_GetTicks();
}

static void update_snowman(Ld31_game *game, entity *e, float delta) {
	snowman_movement(game, e, delta);
	if (SSL_Mouse_Left_Down() && SDL_GetTicks() >= last_shot + 100) {
		snowman_shoot(game, e->x, e->y, e->angle);
	}
	update_snowballs(delta);
}

static int collides(entity *e1, entity *e2) {
  return (e1->x < e2->x + tile_size && e1->x + tile_size > e2->x && e1->y < e2->y + tile_size && e1->y + tile_size > e2->y) ? 1: 0 ;
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
}

Ld31_level *load_level(int level, Ld31_game *game) {
	Ld31_level *lvl = malloc(sizeof(Ld31_level));

	lvl->map = SSL_Tiled_Map_Load("../extras/resources/maps/test_map.tmx", game->window);
	lvl->dict = dictionary_new(0);

	tile_size = SSL_Tiled_Get_Tile_Width(lvl->map);

	return lvl;
}


static entity *spawn_snowman(Ld31_game *game, Ld31_level *lvl) {
	snowballs = SSL_List_Create();
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

	entity *e = create_entity("player", SSL_Image_Load("../extras/resources/sprites/snow_man.png", 32, 32, game->window), up, x, y);;
	return e;
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

	entity *player = spawn_snowman(game, level);

	SSL_Font *debug_font = SSL_Font_Load("../extras/resources/font/unispace.ttf", 18);

	int i = 0;
	while (running) {
		Uint32 now = SDL_GetTicks();
		delta += (now - lastTime) / ns;
		lastTime = now;

		SDL_RenderPresent(game->window->renderer);
		SDL_RenderClear(game->window->renderer);

		while (delta >= 1) {
			update_snowman(game, player, delta);

			handle_collision(level, player);

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

		SSL_Image_Draw(player->image, player->x, player->y, player->angle, 0, SDL_FLIP_NONE, game->window);

		char buf[3];
		itoa(s_fps, buf, 10);
		SSL_Font_Draw(0, 0, 0 ,SDL_FLIP_NONE, "FPS:", debug_font, SSL_Color_Create(0,0,0,0), game->window);
		SSL_Font_Draw(55, 0, 0 ,SDL_FLIP_NONE, buf, debug_font, SSL_Color_Create(0,0,0,0), game->window);

		for (i = 1; i < SSL_List_Size(snowballs); i++) {
			Snowball *e = SSL_List_Get(snowballs, i);
			SSL_Image_Draw(e->entity->image, e->entity->x, e->entity->y, e->entity->angle, 0, SDL_FLIP_NONE, game->window);
		}

		if (SDL_GetTicks() - timer > 1000) {
			timer += 1000;
			s_fps = fps;
			fps = 0;
			tick = 0;
		}
	}
}

