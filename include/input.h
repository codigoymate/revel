#ifndef INPUT_H
#define INPUT_H

#include <list.h>

typedef struct  {
	int left, right, space;
	int l_space;
} key_status_t;

extern key_status_t key_status;

void input_init(void);

// Control system process
void control(iterator_t* iter);

#endif
