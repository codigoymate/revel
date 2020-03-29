#ifndef LEVEL_H
#define LEVEL_H

typedef struct {
	char* data;
	unsigned int size;
} level_t;

level_t* level_load_from_file(char* filename);
void level_destroy(level_t* level);

#endif
