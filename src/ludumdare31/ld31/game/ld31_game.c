#include "../../config.h"
#include "entity.h"
#include "ld31_game.h"
#include "math.h"

#define PI 3.14159265359

int tile_size;
SSL_List *snowballs;
SSL_List *fireballs;
SSL_List *collectibles;
SSL_List *entities;
long last_shot = 0;


int speed_upgrades = 0;
int proj_upgrades = 0;
int total_gold_collected;

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
					if (rand() % 100 + 0 <= 75) {
						Collectible *c = create_collectible("coin", SSL_Image_Load("../extras/resources/sprites/coin.png", 16,16,game->window), e1->x,e1->y);
						SSL_List_Add(collectibles, c);
					}
					SSL_List_Remove(entities, e1);
					SSL_Image_Destroy(e1->image);
					free(e1);
				}
			}
		}

		double radians = (e->entity->angle * PI) / 180;
		e->entity->x += speed * sin(radians);
		e->entity->y -= speed * cos(radians);

		double dx = (e->entity->x - e->deletionX);
		double dy = (e->entity->y - e->deletionY);
		double dist = sqrt(dx*dx+dy*dy);

		if (dist > (e->entity->range * 10) || e->entity->x > 768 || e->entity->y > 768 || e->entity->x < 0 || e->entity->y < 0 || collided) {
			SSL_List_Remove(snowballs, e);
			SSL_Image_Destroy(e->entity->image);
			free(e->entity);
			free(e);
		}

	}
}

static void snowman_shoot(Ld31_game *game, int x, int y, int angle, int prospeed, int dmg) {
	Snowball *e = malloc(sizeof(Snowball));
	double radians = (angle * PI) / 180;
	e->entity = create_entity("snowball", SSL_Image_Load("../extras/resources/sprites/snowball.png", 16, 16, game->window), up, x, y);
	e->entity->angle = angle;
	e->entity->damage = dmg;
	e->deletionX = x + (prospeed*cos(radians));
	e->deletionY = y + (prospeed*sin(radians));
	e->entity->range = prospeed;
	e->startX = x;
	e->startY = y;

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

	if (strcmp(e->name, "player") == 0) {
		int i;
		for (i = 1; i <= SSL_List_Size(collectibles); i++) {
			Collectible *e1 = SSL_List_Get(collectibles, i);
			if (collides(e->x, e->y, 32, 32, e1->x, e1->y, 16,16)) {
				if (strcmp(e1->name, "coin") == 0) {
					e->coins += e1->value;
					total_gold_collected += e1->value;
				}

				SSL_Image_Destroy(e1->image);
				free(e1);
				SSL_List_Remove(collectibles, e1);
			}
		}
	}
}

static void update_fireballs(float delta, int speed, entity *player, Ld31_game *game) {
	speed *= delta;
	int i;
	for (i = 1; i <= SSL_List_Size(fireballs); i++) {
		Snowball *e = SSL_List_Get(fireballs, i);

		int collided = 0;
		if (collides(e->entity->x, e->entity->y, 16,16, player->x, player->y, tile_size, tile_size)) {
				player->health -= e->entity->damage;
				collided = 1;
				if (player->health <= 0) {
					printf("Game Over!");
				}
		}

		double radians = (e->entity->angle * PI) / 180;
		e->entity->x += speed * sin(radians);
		e->entity->y -= speed * cos(radians);

		double dx = (e->entity->x - e->deletionX);
		double dy = (e->entity->y - e->deletionY);
		double dist = sqrt(dx*dx+dy*dy);

		if (dist > (e->entity->range * 10) || e->entity->x > 768 || e->entity->y > 768 || e->entity->x < 0 || e->entity->y < 0 || collided) {
			SSL_List_Remove(fireballs, e);
			SSL_Image_Destroy(e->entity->image);
			free(e->entity);
			free(e);
		}

	}
}

static void entity_shoot(Ld31_game *game, entity *e1, int x, int y, int angle, int prospeed, int dmg) {
	Snowball *e = malloc(sizeof(Snowball));
	double radians = (angle * PI) / 180;
	e->entity = create_entity("fireball", SSL_Image_Load("../extras/resources/sprites/filreball.png", 16, 16, game->window), up, x, y);
	e->entity->angle = angle;
	e->entity->damage = dmg;
	e->deletionX = x + (prospeed*cos(radians));
	e->deletionY = y + (prospeed*sin(radians));
	e->entity->range = prospeed;
	e->startX = x;
	e->startY = y;

	SSL_List_Add(fireballs, e);
	e1->last_shot = SDL_GetTicks();
}

static void move_entity(entity *e, entity *player, Ld31_game *game, float delta) {

	if (strcmp(e->name, "fire") == 0 ) {

		double dx = (player->x - e->x);
		double dy = (player->y - e->y);
		double dist = sqrt(dx*dx+dy*dy);

		if (dist < 400) {
			int deltaX = player->x - e->x ;
			int deltaY = player->y - e->y;
			int angleInDegrees = atan2(deltaX, -deltaY) * 180 / PI;
			e->angle = angleInDegrees;

			if (SDL_GetTicks() >= e->last_shot + e->attack_speed) {
				entity_shoot(game ,e, e->x, e->y, e->angle, 170, 10);
			}
		}
	}

}

static void update_entities(Ld31_level *lvl,entity *player, Ld31_game *game, float delta) {
		int i;
		for (i = 1; i <= SSL_List_Size(entities); i++) {
			entity *e = SSL_List_Get(entities, i);
			move_entity(e, player, game, delta);
		}
		update_fireballs(delta, 3, player, game);
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
	player->range = 15;
	player->projectle_speed = 4;
	player->coins = 0;
	player->health = 100;
	player->damage = 50;

	SSL_Font *debug_font = SSL_Font_Load("../extras/resources/font/unispace.ttf", 18);
	SSL_Font *calibri = SSL_Font_Load("../extras/resources/font/Calibri.ttf", 44);
	SSL_Font *calibri_small = SSL_Font_Load("../extras/resources/font/Calibri.ttf", 22);

	collectibles = SSL_List_Create();
	Collectible *c = create_collectible("coin", SSL_Image_Load("../extras/resources/sprites/coin.png", 16,16,game->window), 200,200);
	SSL_List_Add(collectibles, c);

	entities = SSL_List_Create();
	fireballs = SSL_List_Create();

	SSL_Image *stats_back = SSL_Image_Load("../extras/resources/sprites/stats_back.png", 384, 768, game->window);
	SSL_Image *gold_icon = SSL_Image_Load("../extras/resources/sprites/gold_icon.png", 32, 32, game->window);
	SSL_Image *skull_icon = SSL_Image_Load("../extras/resources/sprites/skull_icon.png", 32, 32, game->window);

	SSL_Image *shop_back = SSL_Image_Load("../extras/resources/sprites/shop_back.png", 384, 768, game->window);
	SSL_Interface *shop_inter = SSL_Interface_Create();

	SSL_Image_Button *speed_buy = SSL_Image_Button_Create(SSL_Rectangle_Create(0,100,384,100), SSL_Image_Load("../extras/resources/sprites/speed_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(shop_inter, speed_buy);

	SSL_Image_Button *attack_speed_buy = SSL_Image_Button_Create(SSL_Rectangle_Create(0,210,384,100), SSL_Image_Load("../extras/resources/sprites/attack_speed_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(shop_inter, attack_speed_buy);

	SSL_Image_Button *range_buy = SSL_Image_Button_Create(SSL_Rectangle_Create(0,320,384,100), SSL_Image_Load("../extras/resources/sprites/range_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(shop_inter, range_buy);

	SSL_Image_Button *projectile_speed_buy = SSL_Image_Button_Create(SSL_Rectangle_Create(0,430,384,100), SSL_Image_Load("../extras/resources/sprites/projectile_speed_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(shop_inter, projectile_speed_buy);

	SSL_Image_Button *health_buy = SSL_Image_Button_Create(SSL_Rectangle_Create(0,540,384,100), SSL_Image_Load("../extras/resources/sprites/health_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(shop_inter, health_buy);

	SSL_Image_Button *damage_buy = SSL_Image_Button_Create(SSL_Rectangle_Create(0,650,384,100), SSL_Image_Load("../extras/resources/sprites/damage_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(shop_inter, damage_buy);


	int speed_by_price = 10;
	int attack_speed_by_price = 5;
	int range_by_price = 15;
	int projectile_speed_by_price = 5;
	int health_by_price = 10;
	int damage_by_price = 20;
	total_gold_collected = 0;
	speed_upgrades = 0;
	proj_upgrades = 0;

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

				update_entities(level, player, game, delta);
			}

			while(SDL_PollEvent(&event)) {
				if (shop_open) {
					interface_update(shop_inter ,event);

					if (speed_buy->button_status->clicked && player->coins >= speed_by_price) {
						player->coins -= speed_by_price;
						player->speed += 0.2;
						speed_by_price *= 2;
						speed_upgrades++;
					} else if (speed_buy->button_status->clicked && player->coins < speed_by_price) {

					}

					if (attack_speed_buy->button_status->clicked && player->coins >= attack_speed_by_price) {
						player->coins -= attack_speed_by_price;
						player->attack_speed += 10;
						attack_speed_by_price *= 2;
					} else if (attack_speed_buy->button_status->clicked && player->coins < attack_speed_by_price) {

					}

					if (range_buy->button_status->clicked && player->coins >= range_by_price) {
						player->coins -= range_by_price;
						player->range += 2;
						range_by_price *= 2;
					} else if (range_buy->button_status->clicked && player->coins < range_by_price) {

					}

					if (projectile_speed_buy->button_status->clicked && player->coins >= projectile_speed_by_price) {
							player->coins -= projectile_speed_by_price;
							player->projectle_speed += 0.2;
							projectile_speed_by_price *= 2;
							proj_upgrades++;
					} else if (range_buy->button_status->clicked && player->coins < projectile_speed_by_price) {

					}

					if (health_buy->button_status->clicked && player->coins >= health_by_price) {
							player->coins -= health_by_price;
							player->health += 10;
							health_by_price *= 2;
					} else if (health_buy->button_status->clicked && player->coins < health_by_price) {

					}

					if (damage_buy->button_status->clicked && player->coins >= damage_by_price) {
							player->coins -= damage_by_price;
							player->damage += 5;
							damage_by_price *= 2;
					} else if (damage_buy->button_status->clicked && player->coins < damage_by_price) {

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
		SSL_Font_Draw(0, 0, 0 ,SDL_FLIP_NONE, "FPS:", debug_font, SSL_Color_Create(255,255,255,0), game->window);
		SSL_Font_Draw(75, 0, 0 ,SDL_FLIP_NONE, buf, debug_font, SSL_Color_Create(255,255,255,0), game->window);

		itoa(player->coins, buf, 10);
		SSL_Font_Draw(0, 25, 0 ,SDL_FLIP_NONE, "Coins:", debug_font, SSL_Color_Create(255,255,255,0), game->window);
		SSL_Font_Draw(95, 25, 0 ,SDL_FLIP_NONE, buf, debug_font, SSL_Color_Create(255,255,255,0), game->window);

		itoa(uptime, buf, 10);
		SSL_Font_Draw(0, 50, 0 ,SDL_FLIP_NONE, "Uptime:", debug_font, SSL_Color_Create(255,255,255,0), game->window);
		SSL_Font_Draw(105, 50, 0 ,SDL_FLIP_NONE, buf, debug_font, SSL_Color_Create(255,255,255,0), game->window);

		for (i = 1; i <= SSL_List_Size(snowballs); i++) {
			Snowball *e = SSL_List_Get(snowballs, i);
			SSL_Image_Draw(e->entity->image, e->entity->x, e->entity->y, e->entity->angle, 0, SDL_FLIP_NONE, game->window);
		}

		for (i = 1; i <= SSL_List_Size(fireballs); i++) {
			Snowball *e = SSL_List_Get(fireballs, i);
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
			SSL_Image_Draw(stats_back, 370, 0, 0, 0, SDL_FLIP_NONE, game->window);
			interface_draw(shop_inter, game->window);

			itoa(speed_by_price, buf, 10);
			SSL_Font_Draw(250, 145, 0 ,SDL_FLIP_NONE, buf, calibri, SSL_Color_Create(255,255,255,0), game->window);

			itoa(attack_speed_by_price, buf, 10);
			SSL_Font_Draw(250, 255, 0 ,SDL_FLIP_NONE, buf, calibri, SSL_Color_Create(255,255,255,0), game->window);

			itoa(range_by_price, buf, 10);
			SSL_Font_Draw(250, 370, 0 ,SDL_FLIP_NONE, buf, calibri, SSL_Color_Create(255,255,255,0), game->window);

			itoa(projectile_speed_by_price, buf, 10);
			SSL_Font_Draw(250, 480, 0 ,SDL_FLIP_NONE, buf, calibri, SSL_Color_Create(255,255,255,0), game->window);

			itoa(health_by_price, buf, 10);
			SSL_Font_Draw(250, 590, 0 ,SDL_FLIP_NONE, buf, calibri, SSL_Color_Create(255,255,255,0), game->window);

			itoa(damage_by_price, buf, 10);
			SSL_Font_Draw(250, 695, 0 ,SDL_FLIP_NONE, buf, calibri, SSL_Color_Create(255,255,255,0), game->window);

			SSL_Image_Draw(gold_icon, 410, 255, 0, 0, SDL_FLIP_NONE, game->window);

			itoa(player->coins, buf, 10);
			SSL_Font_Draw(450, 275, 0 ,SDL_FLIP_NONE, "Current: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(540, 277, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(total_gold_collected, buf, 10);
			SSL_Font_Draw(450, 300, 0 ,SDL_FLIP_NONE, "Total Collected: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(600, 302, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(total_gold_collected, buf, 10);
			SSL_Font_Draw(450, 325, 0 ,SDL_FLIP_NONE, "Collected That Round: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(655, 327, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			SSL_Image_Draw(skull_icon, 410, 360, 0, 0, SDL_FLIP_NONE, game->window);

			itoa((player->speed + speed_upgrades), buf, 10);
			SSL_Font_Draw(450, 385, 0 ,SDL_FLIP_NONE, "Speed: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(520, 387, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(player->attack_speed, buf, 10);
			SSL_Font_Draw(450, 410, 0 ,SDL_FLIP_NONE, "Attack Speed: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(582, 410, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(player->range, buf, 10);
			SSL_Font_Draw(450, 435, 0 ,SDL_FLIP_NONE, "Range: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(520, 435, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa((player->projectle_speed + proj_upgrades), buf, 10);
			SSL_Font_Draw(450, 460, 0 ,SDL_FLIP_NONE, "Proj. Speed: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(565, 460, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(player->health, buf, 10);
			SSL_Font_Draw(450, 485, 0 ,SDL_FLIP_NONE, "Health: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(525, 487, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(player->damage, buf, 10);
			SSL_Font_Draw(450, 510, 0 ,SDL_FLIP_NONE, "Damage: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(540, 510, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);
		}

		if (SDL_GetTicks() - timer > 1000) {
			timer += 1000;
			s_fps = fps;
			fps = 0;
			tick = 0;
			uptime++;
			if (SSL_List_Size(entities) < uptime / 10) {
				int x = (rand() % 21 + 2) * tile_size;
				int y = (rand() % 21 + 2) * tile_size;
				entity *e = create_entity("fire", SSL_Image_Load("../extras/resources/sprites/fire_man.png", 32, 32, game->window), up, x,y);
				e->attack_speed = 2000;
				e->last_shot = 0;
				SSL_List_Add(entities, e);
			}
		}
	}
}

