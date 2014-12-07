#include "../../config.h"
#include "entity.h"
#include "ld31_game.h"
#include "math.h"
#include "../game.h"

#define PI 3.14159265359

int tile_size;
SSL_List *snowballs;
SSL_List *fireballs;
SSL_List *collectibles;
SSL_List *entities;
long last_shot = 0;


int speed_upgrades = 0;
int proj_upgrades = 0;
int health_upgrades = 0;
int total_gold_collected;
int total_gold_collected_round;
int max_health = 0;

Mix_Chunk *shoot;
Mix_Chunk *shoot_fire;
Mix_Chunk *hit;
Mix_Chunk *hit_fire;
Mix_Chunk *death;
Mix_Chunk *coin;
Mix_Chunk *upgrade;
Mix_Chunk *shop_sfx;
Mix_Chunk *round_start;
Mix_Chunk *round_end;

int screen_shake_ticks = 0;
int current_round = 0;

static int rraytrace(Ld31_level *lvl, int x0, int y0, int x1, int y1) {
	int layer = SSL_Tiled_Get_LayerIndex(lvl->map, "collsion");
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int x = x0;
    int y = y0;
    int n = 1 + dx + dy;
    int x_inc = (x1 > x0) ? 1 : -1;
    int y_inc = (y1 > y0) ? 1 : -1;
    int error = dx - dy;
    dx *= 2;
    dy *= 2;
    for (; n > 0; --n)
    {
	// here I can use x,y to do something with the tile, in my case I just need to check if my tile is 1
        if(SSL_Tiled_Get_TileId(lvl->map,x/tile_size,y/tile_size, layer) == 1) {
        	return(1);
        }
        if (error > 0)
        {
            x += x_inc;
            error -= dy;
        }
        else
        {
            y += y_inc;
            error += dx;
        }
    }
    // nothing blocking the line
    return(0);
}

static int collides(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + w2 && y1 + w1 > y2) ? 1: 0 ;
}

static void check_collision(Ld31_level *lvl, entity *e, float speedX, float speedY, float delta) {
	float tmpX = e->x + speedX;
	float tmpY = e->y + speedY;
	int layer = SSL_Tiled_Get_LayerIndex(lvl->map, "collsion");

	// walls
	if (SSL_Tiled_Get_TileId(lvl->map, (tmpX / tile_size), (tmpY / tile_size), layer) == 1) {			// right
		while (SSL_Tiled_Get_TileId(lvl->map, (tmpX / tile_size), (tmpY / tile_size), layer) == 1) {
			tmpX = e->x + 1;
			tmpY = e->y + 1;
		}
	}

	if (SSL_Tiled_Get_TileId(lvl->map, (tmpX / tile_size) + 1, (tmpY / tile_size), layer) == 1) {			// right
		while (SSL_Tiled_Get_TileId(lvl->map, (tmpX / tile_size) + 1, (tmpY / tile_size), layer) == 1) {
			tmpX = e->x - 1;
			tmpY = e->y;
		}
	}

	if (SSL_Tiled_Get_TileId(lvl->map, (tmpX / tile_size), (tmpY / tile_size) + 1, layer) == 1) {			// right
		while (SSL_Tiled_Get_TileId(lvl->map, (tmpX / tile_size), (tmpY / tile_size) + 1, layer) == 1) {
			tmpX = e->x;
			tmpY = e->y - 1;
		}
	}

	e->x = tmpX;
	e->y = tmpY;
}

static void snowman_movement(Ld31_game *game, Ld31_level *lvl, entity *e, float delta) {
		int x;
		int y;

		SDL_GetMouseState(&x,&y);

		int deltaX = x - e->x ;
		int deltaY = y - e->y;
		int angleInDegrees = atan2(deltaX, -deltaY) * 180 / PI;
		e->angle = angleInDegrees;

		double radians = (e->angle * PI) / 180;
		int speed = e->speed * delta;

		float speedX = 0;
		float speedY = 0;

		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.left)) {
			speedX -= speed * cos(radians);
			speedY -= speed * sin(radians);
		}

		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.right)) {
			speedX += speed * cos(radians);
			speedY += speed * sin(radians);
		}

		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.up)) {
			speedX += speed * sin(radians);
			speedY -= speed * cos(radians);
		}

		if (SSL_Keybord_Keyname_Down(game->config->snowman_keys.down)) {
			speedX -= speed * sin(radians);
			speedY += speed * cos(radians);
		}

		check_collision(lvl, e, speedX, speedY, delta);
}

static void update_snowballs(float delta, Ld31_level *lvl, int speed, Ld31_game *game) {
	speed *= delta;
	int i;
	for (i = 1; i <= SSL_List_Size(snowballs); i++) {
		Snowball *e = SSL_List_Get(snowballs, i);

		int collided = 0;
		int j = 0;
		for (j = 1; j <= SSL_List_Size(entities); j++) {
			entity *e1 = SSL_List_Get(entities, j);

			if (collides(e->entity->x, e->entity->y, 16,16, e1->x, e1->y, tile_size, tile_size)) {
				Mix_PlayChannel(-1, hit_fire, 0);
				screen_shake_ticks += 50;
				collided = 1;
				e1->health -= e->entity->damage;

				if (e1->health <= 0) {
					Mix_PlayChannel(-1, death, 0);
					if (rand() % 100 + 0 <= 75) {
						Collectible *c = create_collectible("coin", SSL_Image_Load("../extras/resources/sprites/coin.png", 16,16,game->window), e1->x,e1->y);
						SSL_List_Add(collectibles, c);
					} else if (rand() % 100 + 0 <= 75) {
						Collectible *c = create_collectible("health", SSL_Image_Load("../extras/resources/sprites/health_pack.png", 16,16,game->window), e1->x,e1->y);
						SSL_List_Add(collectibles, c);
					}
					SSL_List_Remove(entities, e1);
					SSL_Image_Destroy(e1->image);
					free(e1);
				}
			}

			int layer = SSL_Tiled_Get_LayerIndex(lvl->map, "collsion");

			double radians = (e->entity->angle * PI) / 180;
			float tmpx = e->entity->x + speed * sin(radians);
			float tmpy = e->entity->y - speed * cos(radians);
			if (SSL_Tiled_Get_TileId(lvl->map, (tmpx / tile_size), (tmpy / tile_size), layer) == 1) {
				Mix_PlayChannel(-1, hit_fire, 0);
				screen_shake_ticks += 2;
				collided = 1;
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
	Mix_PlayChannel(-1, shoot, 0);
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

static void update_snowman(Ld31_game *game, Ld31_level *lvl, entity *e, float delta) {
	snowman_movement(game, lvl, e, delta);
	if (SSL_Mouse_Left_Down() && SDL_GetTicks() >= last_shot + e->attack_speed) {
		snowman_shoot(game, e->x, e->y, e->angle, e->range, e->damage);
	}
	update_snowballs(delta, lvl, e->projectle_speed, game);
}

static void handle_collision(Ld31_level *lvl, entity *e) {
	if (strcmp(e->name, "player") == 0) {
		int i;
		for (i = 1; i <= SSL_List_Size(collectibles); i++) {
			Collectible *e1 = SSL_List_Get(collectibles, i);
			if (collides(e->x, e->y, 32, 32, e1->x, e1->y, 25,25)) {
				Mix_PlayChannel(-1, coin, 0);
				if (strcmp(e1->name, "coin") == 0) {
					e->coins += e1->value;
					total_gold_collected += e1->value;
					total_gold_collected_round += e1->value;
				}

				if (strcmp(e1->name, "health") == 0) {
					e->health += e1->value;
				}

				SSL_Image_Destroy(e1->image);
				free(e1);
				SSL_List_Remove(collectibles, e1);
			}
		}
	}
}

static void update_fireballs(float delta, Ld31_level *lvl, int speed, entity *player, Ld31_game *game) {
	speed *= delta;
	int i;
	for (i = 1; i <= SSL_List_Size(fireballs); i++) {
		Snowball *e = SSL_List_Get(fireballs, i);

		int collided = 0;
		if (collides(e->entity->x, e->entity->y, 16,16, player->x, player->y, tile_size, tile_size)) {
				Mix_PlayChannel(-1, hit, 0);
				screen_shake_ticks += 50;
				player->health -= e->entity->damage;
				collided = 1;
		}

		int layer = SSL_Tiled_Get_LayerIndex(lvl->map, "collsion");

		double radians = (e->entity->angle * PI) / 180;
		float tmpx = e->entity->x + speed * sin(radians);
		float tmpy = e->entity->y - speed * cos(radians);
		if (SSL_Tiled_Get_TileId(lvl->map, (tmpx / tile_size), (tmpy / tile_size), layer) == 1) {
			Mix_PlayChannel(-1, hit_fire, 0);
			screen_shake_ticks += 2;
			collided = 1;
		}

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
	Mix_PlayChannel(-1, shoot_fire, 0);
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

static void move_entity(entity *e, Ld31_level *lvl,  entity *player, Ld31_game *game, float delta) {

	if (strcmp(e->name, "fire") == 0 ) {
		int layer = SSL_Tiled_Get_LayerIndex(lvl->map, "collsion");
		int speed = e->speed * delta;

		switch(e->direction) {
			case up: {
				e->y -= speed;
				if (SSL_Tiled_Get_TileId(lvl->map, e->x / tile_size, (e->y / tile_size), layer) == 1) {
					e->direction = down;
				}
				break;
			}
			case down: {
				e->y += speed;
				if (SSL_Tiled_Get_TileId(lvl->map, e->x / tile_size, ((e->y + tile_size) / tile_size), layer) == 1) {
					e->direction = up;
				}
				break;
			}
			case left: {
				e->x -= speed;
				if (SSL_Tiled_Get_TileId(lvl->map, e->x / tile_size, (e->y / tile_size), layer) == 1) {
					e->direction = right;
				}
				break;
			}
			case right: {
				e->x += speed;
				if (SSL_Tiled_Get_TileId(lvl->map, (e->x  + tile_size) / tile_size, ((e->y) / tile_size), layer) == 1) {
					e->direction = left;
				}
				break;
			}
		}

		double dx = (player->x - e->x);
		double dy = (player->y - e->y);
		double dist = sqrt(dx*dx+dy*dy);

		if (dist < 400 && rraytrace(lvl, player->x, player->y, e->x, e->y) == 0) {
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
			move_entity(e, lvl, player, game, delta);
		}
		update_fireballs(delta, lvl, 3, player, game);
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


static void game_over(int gamemode, int uptime, SDL_Event event, Ld31_game *game, entity *player) {
	int running = 1;

	SSL_Font *calibri = SSL_Font_Load("../extras/resources/font/Calibri.ttf", 44);
	SSL_Font *calibri_small = SSL_Font_Load("../extras/resources/font/Calibri.ttf", 22);

	SSL_Image *time_alive_back = SSL_Image_Load("../extras/resources/sprites/time_alive_back.png", 312, 501, game->window);
	SSL_Image *gold_icon = SSL_Image_Load("../extras/resources/sprites/gold_icon.png", 32, 32, game->window);
	SSL_Image *skull_icon = SSL_Image_Load("../extras/resources/sprites/skull_icon.png", 32, 32, game->window);
	SSL_Image *background = SSL_Image_Load("../extras/resources/sprites/game_over_back.png", 768, 768, game->window);
	SSL_Interface *interface = SSL_Interface_Create();

	SSL_Image_Button *menu_button = SSL_Image_Button_Create(SSL_Rectangle_Create(400,650,384,100), SSL_Image_Load("../extras/resources/sprites/menu_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(interface, menu_button);


	while (running) {
		SDL_RenderPresent(game->window->renderer);
		SDL_RenderClear(game->window->renderer);

		SSL_Image_Draw(background, 0, 0, 0, 0, SDL_FLIP_NONE, game->window);
		interface_draw(interface, game->window);

		if (gamemode == 0) {
			SSL_Image_Draw(time_alive_back, 20, 155, 0, 0, SDL_FLIP_NONE, game->window);

			SSL_Image_Draw(gold_icon, 410, 255, 0, 0, SDL_FLIP_NONE, game->window);

			char buf[3];
			itoa(player->coins, buf, 10);
			SSL_Font_Draw(450, 275, 0 ,SDL_FLIP_NONE, "Current: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(540, 277, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(total_gold_collected, buf, 10);
			SSL_Font_Draw(450, 300, 0 ,SDL_FLIP_NONE, "Total Collected: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(600, 302, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(total_gold_collected_round, buf, 10);
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

			itoa(max_health, buf, 10);
			SSL_Font_Draw(450, 485, 0 ,SDL_FLIP_NONE, "Health: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(525, 487, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(player->damage, buf, 10);
			SSL_Font_Draw(450, 510, 0 ,SDL_FLIP_NONE, "Damage: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(540, 510, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(current_round-1, buf, 10);
			SSL_Font_Draw(160, 400, 0 ,SDL_FLIP_NONE, buf, calibri, SSL_Color_Create(255,255,255,0), game->window);
		}

		int mx;
		int my;
		SDL_GetMouseState(&mx,&my);
		SSL_Image_Draw(cursor, mx, my, 0, 0, SDL_FLIP_NONE, game->window);
		while(SDL_PollEvent(&event)) {

			interface_update(interface, event);

			if (SSL_Keybord_Keyname_Pressed(game->config->mute, event)) {
				if (!mute) {
					Mix_VolumeMusic(0);
					Mix_Volume(-1, 0);
					mute = 1;
				} else {
					Mix_VolumeMusic(50);
					Mix_Volume(-1, 30);
					mute = 0;
				}
			}

			if (menu_button->button_status->clicked) {
				running = 0;
			}

			if (event.type == SDL_QUIT) {
				exit(0);
				break;
			}
		}
	}

	SSL_Font_Destroy(calibri);
	free(calibri);
	SSL_Font_Destroy(calibri_small);
	free(calibri_small);
	SSL_Image_Destroy(time_alive_back);
	free(time_alive_back);
	SSL_Image_Destroy(gold_icon);
	free(gold_icon);
	SSL_Image_Destroy(skull_icon);
	free(skull_icon);
	SSL_Image_Destroy(background);
	free(background);
	SSL_Interface_Destroy(interface);
	free(interface);
	free(menu_button);
}

void play_game(Ld31_game *game, int gamemode) {

	Mix_Music *music = Mix_LoadMUS("../extras/resources/sound/Electro_Sketch.wav");
	Mix_PlayMusic(music, -1);

	shoot = Mix_LoadWAV("../extras/resources/sound/shoot.wav");
	shoot_fire = Mix_LoadWAV("../extras/resources/sound/shoot_fire.wav");

	hit = Mix_LoadWAV("../extras/resources/sound/hit.wav");
	hit_fire = Mix_LoadWAV("../extras/resources/sound/hit_fire.wav");

	death = Mix_LoadWAV("../extras/resources/sound/death.wav");

	coin = Mix_LoadWAV("../extras/resources/sound/coin.wav");

	upgrade = Mix_LoadWAV("../extras/resources/sound/upgrade.wav");

	shop_sfx = Mix_LoadWAV("../extras/resources/sound/shop_sfx.wav");

	round_start = Mix_LoadWAV("../extras/resources/sound/round_start.wav");
	round_end = Mix_LoadWAV("../extras/resources/sound/round_end.wav");


	int running = 1;
	SDL_Event event;

	long lastTime = SDL_GetTicks();
	const double ns = 1000.0 / MAX_TICKS_PER_SECOND;
	Uint32 timer = SDL_GetTicks();
	float delta = 0;
	double fps = 0;
	double tick = 0;
	//double s_fps = 0;
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
	Collectible *c = create_collectible("coin", SSL_Image_Load("../extras/resources/sprites/coin.png", 16,16,game->window), 232,200);
	SSL_List_Add(collectibles, c);

	entities = SSL_List_Create();
	fireballs = SSL_List_Create();

	SSL_Image *stats_back = SSL_Image_Load("../extras/resources/sprites/stats_back.png", 384, 768, game->window);
	SSL_Image *gold_icon = SSL_Image_Load("../extras/resources/sprites/gold_icon.png", 32, 32, game->window);
	SSL_Image *skull_icon = SSL_Image_Load("../extras/resources/sprites/skull_icon.png", 32, 32, game->window);
	SSL_Image *time_icon = SSL_Image_Load("../extras/resources/sprites/time_icon.png", 32, 32, game->window);

	SSL_Image *shop_back = SSL_Image_Load("../extras/resources/sprites/shop_back.png", 384, 768, game->window);
	SSL_Interface *shop_inter = SSL_Interface_Create();

	SSL_Image *ui_back = SSL_Image_Load("../extras/resources/sprites/ui_back.png", 200, 64, game->window);

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

	SSL_Image_Button *menu_button = SSL_Image_Button_Create(SSL_Rectangle_Create(370,50,384,100), SSL_Image_Load("../extras/resources/sprites/menu_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(shop_inter, menu_button);

	SSL_Image_Button *cont_button = SSL_Image_Button_Create(SSL_Rectangle_Create(370,600,384,100), SSL_Image_Load("../extras/resources/sprites/continue_button.png", 384, 100, game->window), 1, 2, 2);
	SSL_Interface_Add_Image_Button(shop_inter, cont_button);

	int speed_by_price = 10;
	int attack_speed_by_price = 5;
	int range_by_price = 15;
	int projectile_speed_by_price = 5;
	int health_by_price = 10;
	int damage_by_price = 20;
	total_gold_collected = 0;
	total_gold_collected_round = 0;
	speed_upgrades = 0;
	proj_upgrades = 0;
	health_upgrades = 0;
	max_health = player->health;
	screen_shake_ticks = 0;

	int i = 0;
	int shop_open = 0;
	int start_round = 0;
	current_round = 0;
	int played_round_end = 1;
	while (running) {
		Uint32 now = SDL_GetTicks();
		delta += (now - lastTime) / ns;
		lastTime = now;

		SDL_RenderPresent(game->window->renderer);
		SDL_RenderClear(game->window->renderer);

		while (delta >= 1) {

			if(screen_shake_ticks > 0) {
				screen_shake_ticks -= delta;
			}

			if (!shop_open) {
				update_snowman(game, level, player, delta);
				handle_collision(level, player);

				update_entities(level, player, game, delta);
			}

			if (player->health <= 0) {
				Mix_PlayChannel(-1, death, 0);
				game_over(gamemode, uptime, event, game, player);
				running = 0;
			}

			while(SDL_PollEvent(&event)) {
				if (shop_open) {
					interface_update(shop_inter ,event);

					if (speed_buy->button_status->clicked && player->coins >= speed_by_price) {
						Mix_PlayChannel(-1, upgrade, 0);
						player->coins -= speed_by_price;
						player->speed += 0.2;
						speed_by_price *= 2;
						speed_upgrades++;
					} else if (speed_buy->button_status->clicked && player->coins < speed_by_price) {

					}

					if (attack_speed_buy->button_status->clicked && player->coins >= attack_speed_by_price) {
						Mix_PlayChannel(-1, upgrade, 0);
						player->coins -= attack_speed_by_price;
						player->attack_speed += 10;
						attack_speed_by_price *= 2;
					} else if (attack_speed_buy->button_status->clicked && player->coins < attack_speed_by_price) {

					}

					if (range_buy->button_status->clicked && player->coins >= range_by_price) {
						Mix_PlayChannel(-1, upgrade, 0);
						player->coins -= range_by_price;
						player->range += 2;
						range_by_price *= 2;
					} else if (range_buy->button_status->clicked && player->coins < range_by_price) {

					}

					if (projectile_speed_buy->button_status->clicked && player->coins >= projectile_speed_by_price) {
							Mix_PlayChannel(-1, upgrade, 0);
							player->coins -= projectile_speed_by_price;
							player->projectle_speed += 0.2;
							projectile_speed_by_price *= 2;
							proj_upgrades++;
					} else if (range_buy->button_status->clicked && player->coins < projectile_speed_by_price) {

					}

					if (health_buy->button_status->clicked && player->coins >= health_by_price) {
							Mix_PlayChannel(-1, upgrade, 0);
							player->coins -= health_by_price;
							max_health += 10;
							health_upgrades++;
							if ((health_upgrades % 10) == 5) {
								health_by_price += 5;
							}
					} else if (health_buy->button_status->clicked && player->coins < health_by_price) {

					}

					if (damage_buy->button_status->clicked && player->coins >= damage_by_price) {
							Mix_PlayChannel(-1, upgrade, 0);
							player->coins -= damage_by_price;
							player->damage += 5;
							damage_by_price *= 2;
					} else if (damage_buy->button_status->clicked && player->coins < damage_by_price) {

					}

					if (menu_button->button_status->clicked) {
						player->health = 0;
					}

					if (cont_button->button_status->clicked) {
						shop_open = !shop_open;
					}
				}

				if (SSL_Keybord_Keyname_Pressed(game->config->start_round, event) && SSL_List_Size(entities) == 0 && !shop_open) {
					Mix_PlayChannel(-1, round_start, 0);
					start_round = 1;
				}

				if (SSL_Keybord_Keyname_Pressed(game->config->mute, event)) {
					if (!mute) {
						Mix_VolumeMusic(0);
						Mix_Volume(-1, 0);
						mute = 1;
					} else {
						Mix_VolumeMusic(50);
						Mix_Volume(-1, 30);
						mute = 0;
					}
				}

				if (gamemode == 0) {
					if (SSL_Keybord_Keyname_Pressed(game->config->open_shop, event)) {
						int layer = SSL_Tiled_Get_LayerIndex(level->map, "triggers");
						if (SSL_Tiled_Get_TileId(level->map, player->x / tile_size, player->y / tile_size, layer) == 1) {
							Mix_PlayChannel(-1, shop_sfx, 0);
							shop_open = !shop_open;
						}
					}
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

		int shakeX = 0;
		int shakeY = 0;
		if (screen_shake_ticks > 0) {
			shakeX = (rand() %  10 + 0);
			shakeY = (rand() %  10 + 0);
		}
		SSL_Tiled_Draw_Map(level->map, 0 + shakeX, shakeY, game->window);

		SSL_Image_Draw(player->image, player->x + shakeX, player->y + shakeY, player->angle, 0, SDL_FLIP_NONE, game->window);

		char buf[3];
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
			SSL_Image_Draw(e->image, e->x + shakeX, e->y + shakeY, e->angle, 0, SDL_FLIP_NONE, game->window);
		}

		for (i = 1; i <= SSL_List_Size(entities); i++) {
			entity *e = SSL_List_Get(entities, i);
			SSL_Image_Draw(e->image, e->x + shakeX, e->y + shakeY, e->angle, 0, SDL_FLIP_NONE, game->window);
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

			itoa(total_gold_collected_round, buf, 10);
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
			SSL_Font_Draw(565, 485, 0 ,SDL_FLIP_NONE, "/", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			itoa(max_health, buf, 10);
			SSL_Font_Draw(575, 487, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			itoa(player->damage, buf, 10);
			SSL_Font_Draw(450, 510, 0 ,SDL_FLIP_NONE, "Damage: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
			SSL_Font_Draw(540, 510, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);
		} else {
			SSL_Image_Draw(ui_back, 0, 0, 0, 0, SDL_FLIP_NONE, game->window);

			SSL_Image_Draw(gold_icon, 10, 5, 0, 0, SDL_FLIP_NONE, game->window);

			itoa(player->coins, buf, 10);
			SSL_Font_Draw(10, 37, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			SSL_Image_Draw(skull_icon, 75, 5, 0, 0, SDL_FLIP_NONE, game->window);

			itoa(player->health, buf, 10);
			SSL_Font_Draw(75, 40, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			SSL_Image_Draw(time_icon, 140, 5, 0, 0, SDL_FLIP_NONE, game->window);

			itoa(current_round, buf, 10);
			SSL_Font_Draw(140, 40, 0 ,SDL_FLIP_NONE, buf, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

			if (start_round == 0 && SSL_List_Size(entities) == 0) {
				SSL_Image_Draw(ui_back, 270, 100, 0, 0, SDL_FLIP_NONE, game->window);
				SSL_Font_Draw(280, 110, 0 ,SDL_FLIP_NONE, "Press", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
				SSL_Font_Draw(340, 110, 0 ,SDL_FLIP_NONE, game->config->start_round, calibri_small, SSL_Color_Create(255,255,255,0), game->window);
				SSL_Font_Draw(280, 140, 0 ,SDL_FLIP_NONE, "For Next round", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
				if (played_round_end == 0) {
					Mix_PlayChannel(-1, round_end, 0);
					played_round_end = 1;
				}
			}
		}

		int mx;
		int my;
		SDL_GetMouseState(&mx,&my);
		SSL_Image_Draw(cursor, mx, my, 0, 0, SDL_FLIP_NONE, game->window);

		if (SDL_GetTicks() - timer > 1000) {
			timer += 1000;
		//	s_fps = fps;
			fps = 0;
			tick = 0;

			if (!shop_open) {
				uptime++;
			}

			if (gamemode == 0) {
				if (start_round == 1) {
					current_round++;
					total_gold_collected_round = 0;
					player->health = max_health;
					int max = 50;
					int amount = current_round*current_round/2;

					if (amount > max) {
						amount = max;
					}
					if (amount == 0) {
						amount++;
					}
					while (amount >= 0) {
						int x = (rand() % 22 + 1) * tile_size;
						int y = (rand() % 22 + 1) * tile_size;
						int layer = SSL_Tiled_Get_LayerIndex(level->map, "collsion");
						int valid = 0;

						while (!valid) {
							x = (rand() % 22 + 1) * tile_size;
							y = (rand() % 22 + 1) * tile_size;

							double dx = (player->x - x);
							double dy = (player->y - y);
							double dist = sqrt(dx*dx+dy*dy);

							if (SSL_Tiled_Get_TileId(level->map, (x / tile_size), (y / tile_size), layer) != 1 && dist > 400) {
								valid = 1;

								for (i = 1; i <= SSL_List_Size(entities); i++) {
									entity *e = SSL_List_Get(entities, i);
									if (collides(x,y,32,32,e->x,e->y,32,32)) {
										valid = 0;
										break;
									}
								}
							}
						}

						entity *e = create_entity("fire", SSL_Image_Load("../extras/resources/sprites/fire_man.png", 32, 32, game->window), up, x,y);
						e->damage = (rand() % 20 + 15);
						e->health = rand() % (current_round*100) + (((current_round*100) / 2) - ((current_round*100) / 2) - 20);
						int dir = (rand() % 4 + 1);
						switch (dir) {
							case 1: {
								e->direction = up;
								break;
							}
							case 2: {
								e->direction = down;
								break;
							}
							case 3: {
								e->direction = left;
								break;
							}
							case 4: {
								e->direction = right;
								break;
							}
						}

						e->speed = (rand() % 3 + 1);
						e->attack_speed = 2000;
						e->last_shot = 0;
						SSL_List_Add(entities, e);
						amount--;
					}
					start_round = 0;
					played_round_end = 0;
				}
			}
		}
	}

	SSL_List_Destroy(snowballs);
	free(snowballs);
	SSL_List_Destroy(fireballs);
	free(fireballs);
	SSL_List_Destroy(collectibles);
	free(collectibles);
	SSL_List_Destroy(entities);
	free(entities);
	free(player);
	SSL_Font_Destroy(debug_font);
	free(debug_font);
	SSL_Font_Destroy(calibri);
	free(calibri);
	SSL_Font_Destroy(calibri_small);
	free(calibri_small);

	SSL_Image_Destroy(stats_back);
	free(stats_back);
	SSL_Image_Destroy(gold_icon);
	free(gold_icon);
	SSL_Image_Destroy(skull_icon);
	free(gold_icon);
	SSL_Image_Destroy(shop_back);
	free(shop_back);
	SSL_Image_Destroy(time_icon);
	free(time_icon);
	SSL_Image_Destroy(ui_back);
	free(ui_back);
	SSL_Interface_Destroy(shop_inter);
	free(speed_buy);
	free(attack_speed_buy);
	free(range_buy);
	free(projectile_speed_buy);
	free(health_buy);
	free(damage_buy);
	SSL_Tiled_Map_Destroy(level->map);
	free(level);

	start_game(game);
}

