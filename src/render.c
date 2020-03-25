#include <render.h>

#include <SDL2/SDL.h>
#include <components.h>
#include <revel.h>
#include <manager.h>

void render_texture(render_texture_t* rt, SDL_Rect* rect);
void render_string(render_string_t* rs, SDL_Rect* rect);

void render(iterator_t* iter) {
    iterator_restart(iter);
    while (iterator_has_next(iter)) {
        unsigned int e = *(unsigned int*)iterator_next(iter);
        SDL_Rect rect;
        transform_t* tc = (transform_t*) mgr_get_component(e, TRANSFORM);
        render_t* rc = (render_t*) mgr_get_component(e, RENDER);
        rect.x = tc->x;
        rect.y = tc->y;
        rect.w = tc->w;
        rect.h = tc->h;

        switch (rc->type) {
            case RENDER_TEXTURE:
                render_texture((render_texture_t*)rc, &rect);
                break;
            case RENDER_STRING:
                render_string((render_string_t*)rc, &rect);
                break;
        }
    }
}

void render_texture(render_texture_t* rt, SDL_Rect* rect) {
    SDL_RenderCopy(renderer, rt->texture, NULL, rect);
}

void render_string(render_string_t* rs, SDL_Rect* rect) {
    unsigned int i = 0;
    int xx = 0;
    for (; i < strlen(rs->string); i ++) {
        char ch = rs->string[i];
        int x = ch & 0x0F;
        int y = (ch & 0xF0) >> 4;
        SDL_Rect src, dest;
        src.x = x * (rs->font->w + rs->font->sep) + rs->font->border;
        src.y = y * (rs->font->h + rs->font->sep) + rs->font->border;
        src.w = rs->font->w;
        src.h = rs->font->h;
        dest.x = rect->x + xx;
        dest.y = rect->y;
        dest.w = rect->w;
        dest.h = rect->h;
        SDL_RenderCopy(renderer, rs->font->texture, &src, &dest);
        xx += rect->w;
    }
}
