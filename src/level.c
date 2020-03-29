#include <level.h>

#include <stdlib.h>
#include <stdio.h>

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

void load_level() {}

void level_destroy(level_t* level) {
	free(level->data);
	free(level);
}
