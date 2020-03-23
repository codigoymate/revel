#include <render.h>

#include <SDL2/SDL.h>
#include <components.h>
#include <revel.h>
#include <manager.h>

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
        SDL_RenderCopy(renderer, rc->texture, NULL, &rect);
    }
}