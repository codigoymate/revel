#include <level.h>

#include <stdlib.h>
#include <stdio.h>

#include <rs_manager.h>
#include <factory.h>

level_t* level_load_from_file(char* filename) {
	FILE* file;
	level_t* lvl = (level_t*) malloc(sizeof(level_t));
	unsigned int i;

	file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Error reading: %s.\n", filename);
		return NULL;
	}
	fseek(file, 0L, SEEK_END);
	lvl->size = ftell(file);
	lvl->data = malloc(lvl->size);
	rewind(file);

	for (i = 0; i < lvl->size; i ++) {
		lvl->data[i] = fgetc(file);
	}

	fclose(file);

	return lvl;
}

void load_level(char* level_name) {
	unsigned int i;
	float x = 0, y = 0;
	level_t* level = rs_manager_get_level(level_name);

	// TODO: clears all manager data

	for (i = 0; i < level->size; i ++) {
		switch (level->data[i]) {
			case '@': create_player(x, y); break;
			case 'o': create_wall(x, y); break;

			case '\n': x = 0; y += 64; break;
			case '\r': break;
		}

		x += 64;
	}

}

void level_destroy(level_t* level) {
	free(level->data);
	free(level);
}
