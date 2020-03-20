#include <components.h>

#include <stdlib.h>

component_t* transform_new(float x, float y, int w, int h) {
	transform_t* comp = (transform_t*) malloc(sizeof(transform_t));
	comp->base.id = TRANSFORM;
	comp->x = x;
	comp->y = y;
	comp->w = w;
	comp->h = h;

	return (component_t*)comp;
}
