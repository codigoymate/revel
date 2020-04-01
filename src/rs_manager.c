#include <rs_manager.h>

#include <hash.h>
#include <revel.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL_image.h>

str_hash_table_t* textures;
str_hash_table_t* fonts;
str_hash_table_t* levels;

SDL_Texture* rs_manager_load_texture(char* str);

void rs_manager_init(void) {
	textures = str_hash_table_new(1000);
	fonts = str_hash_table_new(10);
	levels = str_hash_table_new(100);
}

void rs_manager_close(void) {
	str_hash_iterator_t* iter = str_hash_iterator_new(textures);
	while (str_hash_iterator_has_next(iter)) {
		char *key = str_hash_iterator_next(iter);

		printf("Clean texture \"%s\".\n", key);
		SDL_DestroyTexture((SDL_Texture*)str_hash_table_get(textures, key));
	}
	str_hash_iterator_delete(iter);
	str_hash_table_delete(textures);

	iter = str_hash_iterator_new(fonts);
	while (str_hash_iterator_has_next(iter)) {
		char *key = str_hash_iterator_next(iter);

		printf("Clean font \"%s\".\n", key);
		free((bmp_font_t*)str_hash_table_get(fonts, key));
	}
	str_hash_iterator_delete(iter);
	str_hash_table_delete(fonts);

	iter = str_hash_iterator_new(levels);
	while (str_hash_iterator_has_next(iter)) {
		char *key = str_hash_iterator_next(iter);

		printf("Clean level \"%s\".\n", key);
		level_destroy((level_t*)str_hash_table_get(levels, key));
	}
	str_hash_iterator_delete(iter);
	str_hash_table_delete(levels);
}

SDL_Texture* rs_manager_get_texture(char* str) {

	SDL_Texture* texture = (SDL_Texture*)str_hash_table_get(textures, str);

	if (texture == NULL) {
		texture = rs_manager_load_texture(str);
	}

	return texture;
}

SDL_Texture* rs_manager_load_texture(char* str) {
	char full[80];
	SDL_Texture* texture;

	sprintf(full, "assets/%s.png", str);

	printf("Loading \"%s\".\n", full);

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

	str_hash_table_put(textures, str, texture);

	return texture;
}

void rs_manager_add_bmp_font(char* name, bmp_font_t* font) {
	str_hash_table_put(fonts, name, font);
}

bmp_font_t* rs_manager_get_bmp_font(char* name) {
	return (bmp_font_t*) str_hash_table_get(fonts, name);
}

level_t* rs_manager_get_level(char* str) {
	level_t* level = (level_t*) str_hash_table_get(levels, str);

	if (level == NULL) {
		char full[80];
		sprintf(full, "assets/%s.lvl", str);
		level = level_load_from_file(full);
		if (level != NULL) 
			str_hash_table_put(levels, str, level);
	}

	return level;
}