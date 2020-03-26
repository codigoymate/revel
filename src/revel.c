#include <revel.h>
#include <stdio.h>

#include <rs_manager.h>
#include <manager.h>
#include <input.h>
#include <SDL2/SDL_image.h>

SDL_Window* window;
SDL_Renderer* renderer;
double delta_time;

int revel_init(void) {

	int imgFlags = IMG_INIT_PNG;

	printf("Init SDL.\n");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	printf("Init window.\n");
	window = SDL_CreateWindow("Revel",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1000, 600, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit(); return 0;
	}

	printf("Init renderer.\n");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    //Initialize PNG loading
    printf("Init PNG loading.\n");
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
		SDL_Quit();
    }

	printf("Init resource manager.\n");
	rs_manager_init();

	printf("Init entity manager.\n");
	mgr_init();

	printf("Init input.\n");
	input_init();

	return 1;
}

void revel_close(void) {

	printf("Destroy entity manager.\n");
	mgr_close();

	printf("Destroy resource manager\n");
	rs_manager_close();

	printf("Destroy renderer.\n");
	SDL_DestroyRenderer(renderer);
	printf("Destroy window.\n");
	SDL_DestroyWindow(window);

	printf("Close SDL.\n");
	IMG_Quit();
	SDL_Quit();
}