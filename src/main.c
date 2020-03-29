#include <revel.h>

#include <manager.h>
#include <components.h>
#include <render.h>
#include <movement.h>
#include <input.h>

void load(void) {
    unsigned int ent;
    
    install_bmp_font("font", 8, 8, 1, 1, "font");

    mgr_add_system("render", TRANSFORM | RENDER, render); // render.h
    mgr_add_system("velocity", TRANSFORM | VELOCITY, velocity); // movement.h
    mgr_add_system("control", TRANSFORM | VELOCITY | CONTROL, control); // input.h
    mgr_add_system("wall", TRANSFORM | WALL, NULL);
    

    ent = mgr_new_entity();
    mgr_add_component(ent, transform_new(500, 100, 32, 32));
    mgr_add_component(ent, render_texture_new("circle"));
    mgr_add_component(ent, velocity_new(0.0f, 0.0f));
    mgr_add_component(ent, control_new());
    mgr_register(ent);

    /*
    ent = mgr_new_entity();
    mgr_add_component(ent, transform_new(300, 200, 64, 64));
    mgr_add_component(ent, render_texture_new("circle"));
    mgr_register(ent);

    ent = mgr_new_entity();
    mgr_add_component(ent, transform_new(100, 400, 16, 20));
    mgr_add_component(ent, render_string_new("font", "Hola que tal"));
    mgr_add_component(ent, velocity_new(100.0f, 0.0f));
    mgr_register(ent);
    */
}

int main() {

	int quit = 0;
	SDL_Event e;
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;

	revel_init();

    load();

	while(!quit)
    {
        //Handle events on queue
        while(SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_UP: key_status.up = 1; break;
                case SDLK_DOWN: key_status.down = 1; break;
                case SDLK_LEFT: key_status.left = 1; break;
                case SDLK_RIGHT: key_status.right = 1; break;
                }
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_UP: key_status.up = 0; break;
                case SDLK_DOWN: key_status.down = 0; break;
                case SDLK_LEFT: key_status.left = 0; break;
                case SDLK_RIGHT: key_status.right = 0; break;
                }
            }
        }

        last = now;
        now = SDL_GetPerformanceCounter();

        delta_time = (double)((now - last) * 1000.0 / (double) SDL_GetPerformanceFrequency());
        delta_time *= 0.001;

        //Clear screen
        SDL_RenderClear(renderer);

        // Systems process
        mgr_process_systems();

        //Update screen
        SDL_RenderPresent(renderer);
    }

	revel_close();

	return 0;
}
