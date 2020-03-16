#include <rs_manager.h>

#include <hash.h>
#include <stdio.h>

str_hash_table_t* ht;

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

SDL_Texture* rs_manager_get_texture(const char* str) {

	return NULL;
}
