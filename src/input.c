#include <input.h>

#include <components.h>
#include <manager.h>

#define CONTROL_VELOCITY 		300
#define JUMP_VELOCITY			1000

key_status_t key_status;

void input_init(void) {
	key_status.left = 0;
	key_status.right = 0;
	key_status.space = 0;
	key_status.l_space = 0;
}

void control(iterator_t* iter) {
	iterator_restart(iter);
	while (iterator_has_next(iter)) {
		unsigned int e = *(unsigned int*) iterator_next(iter);
		velocity_t* vc = (velocity_t*) mgr_get_component(e, VELOCITY);

		if (key_status.left) vc->x = -CONTROL_VELOCITY;
		else if (key_status.right) vc->x = CONTROL_VELOCITY;
		else vc->x = 0;

		if (key_status.space) {
			if (!key_status.l_space) {
				// Jump
				vc->y = -JUMP_VELOCITY;
				key_status.l_space = 1;
			}
		} else {
			key_status.l_space = 0;
		}
	}
}
