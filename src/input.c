#include <input.h>

key_status_t key_status;

void input_init(void) {
	key_status.left = 0;
	key_status.right = 0;
	key_status.up = 0;
	key_status.down = 0;
}

void control(iterator_t* iter) {

}
