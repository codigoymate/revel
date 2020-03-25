#ifndef BMP_FONT_H
#define BMP_FONT_H

#include <SDL2/SDL.h>

typedef struct {
	int w, h, sep, border;
	SDL_Texture* texture;
} bmp_font_t;

void install_bmp_font(char* name, int w, int h, int sep, int border, char* texture);

#endif
