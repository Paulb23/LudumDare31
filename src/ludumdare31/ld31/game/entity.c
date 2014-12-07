#include "entity.h"
#include <time.h>
#include <stdlib.h>



entity *create_entity(char *name, SSL_Image *image, direction dir, int x,  int y) {
	entity *entitys = malloc(sizeof(entity));

	entitys->name = name;
	entitys->image = image;
	entitys->direction = dir;
	entitys->x = x;
	entitys->y = y;
	entitys->angle = 0;

	entitys->attack_speed = 0;
	entitys->projectle_speed = 0;
	entitys->speed = 0;
	entitys->range = 0;
	entitys->coins = 0;
	entitys->health = 100;
	entitys->damage = 0;

	return entitys;
}

Collectible *create_collectible(char *name, SSL_Image *image, int x,  int y) {
	Collectible *entitys = malloc(sizeof(Collectible));

	srand(time(NULL));

	entitys->name = name;
	entitys->image = image;
	entitys->x = x;
	entitys->y = y;
	entitys->angle = rand() % 360 + 0;

	if (strcmp(name, "health") == 0) {
		entitys->value = rand() % 15 + 10;
	} else {
		entitys->value = rand() % 10 + 1;
	}

	return entitys;
}
