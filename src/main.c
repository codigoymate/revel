#include <revel.h>

#include <manager.h>
#include <components.h>
#include <render.h>
#include <movement.h>
#include <input.h>
#include <camera.h>
#include <level.h>
#include <rs_manager.h>

void load(void) {
    
    //install_bmp_font("font", 8, 8, 1, 1, "font");

    mgr_add_system("velocity", TRANSFORM | VELOCITY, velocity); // movement.h
    mgr_add_system("control", TRANSFORM | VELOCITY | CONTROL, control); // input.h
    mgr_add_system("wall", TRANSFORM | WALL, NULL);
    mgr_add_system("camera", TRANSFORM, process_camera); // camera.h
    mgr_add_system("render", TRANSFORM | RENDER, render); // render.h
    

    load_level("test_level");

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
                case SDLK_LEFT: key_status.left = 1; break;
                case SDLK_RIGHT: key_status.right = 1; break;
                case SDLK_SPACE: key_status.space = 1; break;
                }
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT: key_status.left = 0; break;
                case SDLK_RIGHT: key_status.right = 0; break;
                case SDLK_SPACE: key_status.space = 0; break;
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
