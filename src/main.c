#include <revel.h>

#include <manager.h>
#include <components.h>
#include <render.h>
#include <movement.h>

int main() {
	
    unsigned int ent;

	int quit = 0;
	SDL_Event e;
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;

	revel_init();

    install_bmp_font("font", 8, 8, 1, 1, "font");

    mgr_add_system("render", TRANSFORM | RENDER, render); // render.h
    mgr_add_system("velocity", TRANSFORM | VELOCITY, velocity); // movement.h

    ent = mgr_new_entity();
    mgr_add_component(ent, transform_new(500, 100, 32, 32));
    mgr_add_component(ent, render_texture_new("circle"));
    mgr_add_component(ent, velocity_new(20.0f, 15.0f));
    mgr_register(ent);

    ent = mgr_new_entity();
    mgr_add_component(ent, transform_new(300, 200, 64, 64));
    mgr_add_component(ent, render_texture_new("circle"));
    mgr_register(ent);

    ent = mgr_new_entity();
    mgr_add_component(ent, transform_new(100, 400, 16, 20));
    mgr_add_component(ent, render_string_new("font", "Hola que tal"));
    mgr_register(ent);

	while(!quit)
    {
        //Handle events on queue
        while(SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if(e.type == SDL_QUIT)
            {
                quit = 1;
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
