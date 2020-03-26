#ifndef INPUT_H
#define INPUT_H

typedef struct  {
	int left, right, down, up;
} key_status_t;

extern key_status_t key_status;

void input_init(void);

#endif
