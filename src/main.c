#include <revel.h>

#include <rs_manager.h>
#include <manager.h>
#include <components.h>

int main() {
	
    unsigned int ent;

	int quit = 0;
	SDL_Texture* circle;
	SDL_Event e;

	revel_init();

	circle = rs_manager_get_texture("circle");

    ent = mgr_new_entity();
    mgr_add_component(ent, transform_new(100, 100, 32, 32));

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
        SDL_RenderCopy(renderer, circle, NULL, NULL);

        //Update screen
        SDL_RenderPresent(renderer);
    }

	revel_close();

	return 0;
}
