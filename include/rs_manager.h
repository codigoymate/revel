#ifndef RS_MANAGER_H
#define RS_MANAGER_H

#include <SDL2/SDL.h>

void rs_manager_init(void);
void rs_manager_close(void);

SDL_Texture* rs_manager_get_texture(char* str);

#endif
