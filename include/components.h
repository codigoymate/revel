#ifndef COMPONENTS_H
#define COMPONENTS_H

#define TRANSFORM		1
#define RENDER			2
#define VELOCITY		4
#define CONTROL			8
#define WALL			16

#define RENDER_TEXTURE		0
#define RENDER_STRING		1

#include <SDL2/SDL.h>
#include <bmp_font.h>

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

/********************************************************/
// Render Base
typedef struct {
	component_t base;
	int type;
} render_t;

typedef struct {
	render_t base;
	SDL_Texture* texture;
} render_texture_t;

component_t* render_texture_new(char* texture);

typedef struct {
	render_t base;
	bmp_font_t* font;
	char string[50];
} render_string_t;

component_t* render_string_new(char* font, char* string);

// Movement: Velocity
typedef struct {
	component_t base;
	float x, y;
} velocity_t;

component_t* velocity_new(float x, float y);

typedef struct {
	component_t base;
} control_t;

component_t* control_new(void);

typedef struct {
	component_t base;
} wall_t;

component_t* wall_new(void);

#endif
