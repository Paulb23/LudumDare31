#ifndef ENTITY_H_
#define ENTITY_H_

#include "../../config.h"

typedef enum _direction_ {
		up,down,left,right
} direction;

typedef struct _ld31_entity_ {
	char *name;
	SSL_Image *image;
	direction direction;
	float x;
	float y;
	int angle;

	float speed;
	int projectle_speed;
	int attack_damage;
	int attack_speed;
	int range;
	int damage;
	int coins;
	int health;
} entity;

typedef struct _snowball_ {
	entity *entity;
	long deletion_time;
	int damage;
} Snowball;

typedef struct _collectibles_ {
	char *name;
	int x;
	int y;
	SSL_Image *image;
	int angle;
	int value;
} Collectible;

entity *create_entity(char *name, SSL_Image *image, direction dir, int x,  int y);
Collectible *create_collectible(char *name, SSL_Image *image, int x,  int y);

#endif
