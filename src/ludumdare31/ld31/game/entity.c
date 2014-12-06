#include "entity.h"

entity *create_entity(char *name, SSL_Image *image, direction dir, int x,  int y) {
	entity *entitys = malloc(sizeof(entity));

	entitys->name = name;
	entitys->image = image;
	entitys->direction = dir;
	entitys->x = x;
	entitys->y = y;

	return entitys;
}
