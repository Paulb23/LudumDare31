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
	int x;
	int y;
	int angle;
} entity;

typedef struct _snowball_ {
	entity *entity;
	long deletion_time;
} Snowball;

entity *create_entity(char *name, SSL_Image *image, direction dir, int x,  int y);

#endif
