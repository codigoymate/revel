#ifndef RS_MANAGER_H
#define RS_MANAGER_H

#include <SDL2/SDL.h>
#include <bmp_font.h>

void rs_manager_init(void);
void rs_manager_close(void);

SDL_Texture* rs_manager_get_texture(char* str);

void rs_manager_add_bmp_font(char* name, bmp_font_t* font);
bmp_font_t* rs_manager_get_bmp_font(char* name);

#endif
