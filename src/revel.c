#include <revel.h>
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;

int revel_init(void) {

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

	return 1;
}

void revel_close(void) {
	printf("Destroy renderer.\n");
	SDL_DestroyRenderer(renderer);
	printf("Destroy window.\n");
	SDL_DestroyWindow(window);

	printf("Close SDL.\n");
	SDL_Quit();
}