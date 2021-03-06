#include <revel.h>

#include <manager.h>
#include <components.h>
#include <render.h>
#include <movement.h>
#include <input.h>
#include <camera.h>
#include <level.h>
#include <rs_manager.h>

#define FPS     120

void load(void) {
    
    //install_bmp_font("font", 8, 8, 1, 1, "font");

    mgr_add_system("velocity", TRANSFORM | VELOCITY, velocity); // movement.h
    mgr_add_system("control", TRANSFORM | VELOCITY | CONTROL, control); // input.h
    mgr_add_system("wall", TRANSFORM | WALL, NULL);
    mgr_add_system("camera", TRANSFORM, process_camera); // camera.h
    mgr_add_system("render", TRANSFORM | RENDER, render); // render.h
    

    load_level("test_level");

}

/*int t;
while (run) {
    t = SDL_GetTicks ();
    // ...
    t = SDL_GetTicks () - t;

    // if the framerate is too high
    if (t < 1000 / FPS) {
        // compute the difference to have a total frame time of 1000 / FPS
        SDL_Delay ((1000 / FPS) - t);
    }
}*/

int main(int argc, char** argv) {

	int quit = 0, time;
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

        time = SDL_GetTicks();

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

        time = SDL_GetTicks() - time;

        if (time < 1000 / FPS)
            SDL_Delay ((1000 / FPS) - time);
    }

	revel_close();

	return 0;
}
