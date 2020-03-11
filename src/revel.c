#include <stdio.h>

#include <SDL2/SDL.h>

int main() {

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error\n");

	} else {
		window = SDL_CreateWindow("SDL Test",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			1000, 600, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Error\n");
		} else {
			screenSurface = SDL_GetWindowSurface(window);

			SDL_FillRect(screenSurface, NULL,
				SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			SDL_UpdateWindowSurface(window);

			SDL_Delay(2000);
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
