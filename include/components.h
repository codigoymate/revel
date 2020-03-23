#ifndef COMPONENTS_H
#define COMPONENTS_H

#define TRANSFORM		1
#define RENDER			2

#include <SDL2/SDL.h>

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

typedef struct {
	component_t base;
	SDL_Texture* texture;
} render_t;

component_t* render_new(char* sprite);

#endif
