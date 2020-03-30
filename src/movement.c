#include <movement.h>

#include <components.h>
#include <manager.h>
#include <revel.h>

int aabb(transform_t* t1, transform_t* t2) {
    if (t1->x < t2->x + t2->w &&
			t1->x + t1->w > t2->x &&
			t1->y < t2->y + t2->h &&
			t1->y + t1->h > t2->y) return 1;

    return 0;

}

void velocity(iterator_t* iter) {

	float xb, yb;

	iterator_restart(iter);
	while (iterator_has_next(iter)) {
		unsigned int e = *(unsigned int*) iterator_next(iter);
		transform_t* tc = (transform_t*) mgr_get_component(e, TRANSFORM);
		velocity_t* vc = (velocity_t*) mgr_get_component(e, VELOCITY);
		iterator_t* walls =  mgr_get_system_iterator("wall");

		if (mgr_has_component(e, GRAVITY)) {
			vc->y += 3;
		}

		// Backup
		xb = tc->x;
		yb = tc->y;

		tc->x += vc->x * delta_time;
		if (mgr_has_component(e, SOLID)) {
			int ew;
			iterator_restart(walls);
			while (iterator_has_next(walls)) {
				transform_t* tcw;
				ew = *(unsigned int *) iterator_next(walls);
				tcw = (transform_t*) mgr_get_component(ew, TRANSFORM);
				if (aabb(tc, tcw)) {
					tc->x = xb; break;
				}
			}
		}

		tc->y += vc->y * delta_time;
		if (mgr_has_component(e, SOLID)) {
			int ew;
			iterator_restart(walls);
			while (iterator_has_next(walls)) {
				transform_t* tcw;
				ew = *(unsigned int *) iterator_next(walls);
				tcw = (transform_t*) mgr_get_component(ew, TRANSFORM);
				if (aabb(tc, tcw)) {
					tc->y = yb;
					vc->y = 0;
					break;
				}
			}
		}
	}
}
