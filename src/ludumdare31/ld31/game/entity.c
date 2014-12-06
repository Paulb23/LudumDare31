#include "entity.h"

entity *create_entity(char *name, SSL_Image *image, direction dir, int x,  int y) {
	entity *entitys = malloc(sizeof(entity));

	entitys->name = name;
	entitys->image = image;
	entitys->direction = dir;
	entitys->x = x;
	entitys->y = y;
	entitys->angle = 0;

	entitys->attack_damage = 0;
	entitys->attack_speed = 0;
	entitys->projectle_speed = 0;
	entitys->speed = 0;
	entitys->range = 0;
	entitys->coins = 0;

	return entitys;
}
