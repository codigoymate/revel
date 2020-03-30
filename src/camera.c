#include <camera.h>

#include <revel.h>
#include <manager.h>

unsigned int camera_focus;

void process_camera(iterator_t* iter) {
	transform_t* ftc = (transform_t*) mgr_get_component(camera_focus, TRANSFORM);
	float dx = ftc->x - WINDOW_WIDTH / 2;
    float dy = ftc->y - (WINDOW_HEIGHT / 2 + 100);
    ftc->x = WINDOW_WIDTH / 2;
    ftc->y = WINDOW_HEIGHT / 2 + 100;
	iterator_restart(iter);
	while (iterator_has_next(iter)) {
		unsigned int e = *(unsigned int *) iterator_next(iter);
		transform_t* tc;
		if (e == camera_focus) continue;
		tc = (transform_t*) mgr_get_component(e, TRANSFORM);
		tc->x -= dx;
        tc->y -= dy;
	}
}
