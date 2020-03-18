#include <rs_manager.h>

#include <hash.h>
#include <revel.h>

#include <stdio.h>
#include <string.h>

#include <SDL2/SDL_image.h>


str_hash_table_t* ht;

SDL_Texture* rs_manager_load_texture(char* str);

void rs_manager_init(void) {
	ht = str_hash_table_new(1000);
}

void rs_manager_close(void) {
	str_hash_iterator_t* iter = str_hash_iterator_new(ht);

	while (str_hash_iterator_has_next(iter)) {
		char *key = str_hash_iterator_next(iter);

		printf("Clean \"%s\".\n", key);
		SDL_DestroyTexture((SDL_Texture*)str_hash_table_get(ht, key));
	}

	str_hash_table_delete(ht);
}

SDL_Texture* rs_manager_get_texture(char* str) {

	SDL_Texture* texture = (SDL_Texture*)str_hash_table_get(ht, str);

	if (texture == NULL) {
		texture = rs_manager_load_texture(str);
	}

	return texture;
}

SDL_Texture* rs_manager_load_texture(char* str) {
	char full[80];
	SDL_Texture* texture;

	sprintf(full, "assets/%s/.png", str);

	SDL_Surface* surface = IMG_Load(full);
	if (surface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", full, IMG_GetError());
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s\n", full, SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(surface);

	str_hash_table_put(ht, str, texture);

	return texture;
}
