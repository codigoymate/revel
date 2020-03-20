#ifndef COMPONENTS_H
#define COMPONENTS_H

#define TRANSFORM		1

// Base
typedef struct {
	unsigned int id;
} component_t;

// Position and Size
typedef struct {
	component_t base;
	float x, y;
	int w, h;
} transform_t;

component_t* transform_new(float x, float y, int w, int h);

#endif
