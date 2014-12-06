#include "../../config.h"
#include "entity.h"
#include "ld31_game.h"
#include "math.h"

#define PI 3.14159265359

int tile_size;
SSL_List *snowballs;
SSL_List *collectibles;
SSL_List *entities;
long last_shot = 0;

static int collides(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + w2 && y1 + w1 > y2) ? 1: 0 ;
}

static void snowman_movement(Ld31_game *game, entity *e, float delta) {
		int x;
		int y;

		SDL_GetMouseState(&x,&y);

		int deltaX = x - e->x ;
		int deltaY = y - e->y;
		int angleInDegrees = atan2(deltaX, -deltaY) * 180 / PI;
		e->angle = angleInDegrees;

		double radians = (e->angle * PI) / 180;
		int speed = e->speed * delta;

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

static void update_snowballs(float delta, int speed, Ld31_game *game) {
	speed *= delta;
	int i;
	for (i = 1; i <= SSL_List_Size(snowballs); i++) {
		Snowball *e = SSL_List_Get(snowballs, i);

		int collided = 0;
		int j = 0;
		for (j = 1; j <= SSL_List_Size(entities); j++) {
			entity *e1 = SSL_List_Get(entities, j);

			if (collides(e->entity->x, e->entity->y, 16,16, e1->x, e1->y, tile_size, tile_size)) {
				collided = 1;
				e1->health -= e->entity->damage;

				if (e1->health <= 0) {
					Collectible *c = create_collectible("coin", SSL_Image_Load("../extras/resources/sprites/coin.png", 16,16,game->window), e1->x,e1->y);
					SSL_List_Add(collectibles, c);

					SSL_List_Remove(entities, e1);
					SSL_Image_Destroy(e1->image);
					free(e1);
				}
			}
		}

		double radians = (e->entity->angle * PI) / 180;
		e->entity->x += speed * sin(radians);
		e->entity->y -= speed * cos(radians);

		if (SDL_GetTicks() > e->deletion_time || e->entity->x > 768 || e->entity->y > 768 || e->entity->x < 0 || e->entity->y < 0 || collided) {
			SSL_List_Remove(snowballs, e);
			SSL_Image_Destroy(e->entity->image);
			free(e->entity);
			free(e);
		}

	}
}

static void snowman_shoot(Ld31_game *game, int x, int y, int angle, int prospeed, int dmg) {
	Snowball *e = malloc(sizeof(Snowball));
	e->entity = create_entity("snowball", SSL_Image_Load("../extras/resources/sprites/snowball.png", 16, 16, game->window), up, x, y);
	e->entity->angle = angle;
	e->entity->damage = dmg;
	e->deletion_time = SDL_GetTicks() + prospeed;
	SSL_List_Add(snowballs, e);
	last_shot = SDL_GetTicks();
}

static void update_snowman(Ld31_game *game, entity *e, float delta) {
	snowman_movement(game, e, delta);
	if (SSL_Mouse_Left_Down() && SDL_GetTicks() >= last_shot + e->attack_speed) {
		snowman_shoot(game, e->x, e->y, e->angle, e->range, e->damage);
	}
	update_snowballs(delta, e->projectle_speed, game);
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

	int i;
	for (i = 1; i <= SSL_List_Size(collectibles); i++) {
		Collectible *e1 = SSL_List_Get(collectibles, i);
		if (collides(e->x, e->y, 32, 32, e1->x, e1->y, 16,16)) {
			if (strcmp(e1->name, "coin") == 0) {
				e->coins += e1->value;
			}

			SSL_Image_Destroy(e1->image);
			free(e1);
			SSL_List_Remove(collectibles, e1);
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

	entity *e = create_entity("player", SSL_Image_Load("../extras/resources/sprites/snow_man.png", 32, 32, game->window), up, x, y);
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
	int uptime = 0;

	Ld31_level *level = load_level(0, game);

	entity *player = spawn_snowman(game, level);
	player->speed = 2;
	player->attack_speed = 500;
	player->range = 2000;
	player->projectle_speed = 4;
	player->attack_damage = 0;
	player->coins = 0;
	player->health = 100;
	player->damage = 50;

	SSL_Font *debug_font = SSL_Font_Load("../extras/resources/font/unispace.ttf", 18);
	SSL_Font *calibri = SSL_Font_Load("../extras/resources/font/Calibri.ttf", 44);

	collectibles = SSL_List_Create();
	Collectible *c = create_collectible("coin", SSL_Image_Load("../extras/resources/sprites/coin.png", 16,16,game->window), 200,200);
	SSL_List_Add(collectibles, c);

	entities = SSL_List_Create();

	SSL_Image *shop_back = SSL_Image_Load("../extras/resources/sprites/shop_back.png", 384, 768, game->window);
	SSL_Interface *shop_inter = SSL_Interface_Create();

	SSL_Image_Button *speed_buy = SSL_Image_Button_Create(SSL_Rectangle_Create(0,100,384,100), SSL_Image_Load("../extras/resources/sprites/speed_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(shop_inter, speed_buy);

	SSL_Image_Button *attack_speed_buy = SSL_Image_Button_Create(SSL_Rectangle_Create(0,210,384,100), SSL_Image_Load("../extras/resources/sprites/attack_speed_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(shop_inter, attack_speed_buy);


	int speed_by_price = 10;
	int attack_speed_by_price = 5;

	int i = 0;
	int shop_open = 0;
	while (running) {
		Uint32 now = SDL_GetTicks();
		delta += (now - lastTime) / ns;
		lastTime = now;

		SDL_RenderPresent(game->window->renderer);
		SDL_RenderClear(game->window->renderer);

		while (delta >= 1) {

			if (!shop_open) {
				update_snowman(game, player, delta);
				handle_collision(level, player);
			}

			while(SDL_PollEvent(&event)) {
				if (shop_open) {
					interface_update(shop_inter ,event);

					if (speed_buy->button_status->clicked && player->coins >= speed_by_price) {
						player->coins -= speed_by_price;
						player->speed += 0.2;
						speed_by_price *= 2;
					} else if (speed_buy->button_status->clicked && player->coins < speed_by_price) {

					}

					if (attack_speed_buy->button_status->clicked && player->coins >= attack_speed_by_price) {
						player->coins -= attack_speed_by_price;
						player->attack_speed += 10;
						attack_speed_by_price *= 2;
					} else if (attack_speed_buy->button_status->clicked && player->coins < attack_speed_by_price) {

					}
				}

				if (SSL_Keybord_Keyname_Pressed(game->config->open_shop, event)) {
					shop_open = !shop_open;
				}

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
		SSL_Font_Draw(75, 0, 0 ,SDL_FLIP_NONE, buf, debug_font, SSL_Color_Create(0,0,0,0), game->window);

		itoa(player->coins, buf, 10);
		SSL_Font_Draw(0, 25, 0 ,SDL_FLIP_NONE, "Coins:", debug_font, SSL_Color_Create(0,0,0,0), game->window);
		SSL_Font_Draw(95, 25, 0 ,SDL_FLIP_NONE, buf, debug_font, SSL_Color_Create(0,0,0,0), game->window);

		itoa(uptime, buf, 10);
		SSL_Font_Draw(0, 50, 0 ,SDL_FLIP_NONE, "Uptime:", debug_font, SSL_Color_Create(0,0,0,0), game->window);
		SSL_Font_Draw(105, 50, 0 ,SDL_FLIP_NONE, buf, debug_font, SSL_Color_Create(0,0,0,0), game->window);

		for (i = 1; i <= SSL_List_Size(snowballs); i++) {
			Snowball *e = SSL_List_Get(snowballs, i);
			SSL_Image_Draw(e->entity->image, e->entity->x, e->entity->y, e->entity->angle, 0, SDL_FLIP_NONE, game->window);
		}

		for (i = 1; i <= SSL_List_Size(collectibles); i++) {
			Collectible *e = SSL_List_Get(collectibles, i);
			SSL_Image_Draw(e->image, e->x, e->y, e->angle, 0, SDL_FLIP_NONE, game->window);
		}

		for (i = 1; i <= SSL_List_Size(entities); i++) {
			entity *e = SSL_List_Get(entities, i);
			SSL_Image_Draw(e->image, e->x, e->y, e->angle, 0, SDL_FLIP_NONE, game->window);
		}

		if (shop_open) {
			SSL_Image_Draw(shop_back, 0, 0, 0, 0, SDL_FLIP_NONE, game->window);
			interface_draw(shop_inter, game->window);

			itoa(speed_by_price, buf, 10);
			SSL_Font_Draw(250, 145, 0 ,SDL_FLIP_NONE, buf, calibri, SSL_Color_Create(255,255,255,0), game->window);

			itoa(attack_speed_by_price, buf, 10);
			SSL_Font_Draw(250, 255, 0 ,SDL_FLIP_NONE, buf, calibri, SSL_Color_Create(255,255,255,0), game->window);
		}

		if (SDL_GetTicks() - timer > 1000) {
			timer += 1000;
			s_fps = fps;
			fps = 0;
			tick = 0;
			uptime++;
			if (SSL_List_Size(entities) < uptime / 10) {
				int x = (rand() % 22 + 1) * tile_size;
				int y = (rand() % 22 + 1) * tile_size;
				entity *e = create_entity("fire", SSL_Image_Load("../extras/resources/sprites/fire_man.png", 32, 32, game->window), up, x,y);
				SSL_List_Add(entities, e);
			}
		}
	}
}

