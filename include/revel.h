#ifndef REVEL_H
#define REVEL_H

#include <SDL2/SDL.h>

extern SDL_Renderer* renderer;
extern double delta_time;

int revel_init(void);

void revel_close(void);

#endif

