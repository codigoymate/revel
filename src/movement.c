#include <movement.h>

#include <components.h>
#include <manager.h>

void velocity(iterator_t* iter) {
	iterator_restart(iter);
	while (iterator_has_next(iter)) {
		unsigned int e = *(unsigned int*) iterator_next(iter);
		transform_t* tc = (transform_t*) mgr_get_component(e, TRANSFORM);
		velocity_t* vc = (velocity_t*) mgr_get_component(e, VELOCITY);

		tc->x += vc->x;
		tc->y += vc->y;
	}
}
