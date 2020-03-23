#include <revel.h>

#include <rs_manager.h>
#include <manager.h>
#include <components.h>

void render(void) {
    
}

int main() {
	
    unsigned int ent;

	int quit = 0;
	SDL_Event e;

	revel_init();

    mgr_add_system("render", TRANSFORM | RENDER, render);

    ent = mgr_new_entity();
    mgr_add_component(ent, transform_new(100, 100, 32, 32));
    mgr_add_component(ent, render_new("circle"));
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

        //Clear screen
        SDL_RenderClear(renderer);

        //Render texture to screen
        //SDL_RenderCopy(renderer, circle, NULL, NULL);
        mgr_process_systems();

        //Update screen
        SDL_RenderPresent(renderer);
    }

	revel_close();

	return 0;
}
