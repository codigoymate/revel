#include <components.h>

#include <stdlib.h>
#include <rs_manager.h>

component_t* transform_new(float x, float y, int w, int h) {
	transform_t* comp = (transform_t*) malloc(sizeof(transform_t));
	comp->base.id = TRANSFORM;
	comp->x = x;
	comp->y = y;
	comp->w = w;
	comp->h = h;

	return (component_t*)comp;
}

component_t* render_new(char* sprite) {
	render_t* comp = (render_t*) malloc(sizeof(render_t));
	comp->base.id = RENDER;
	comp->texture = rs_manager_get_texture(sprite);

	return (component_t*)comp;
}

component_t* velocity_new(float x, float y) {
	velocity_t* comp = (velocity_t*) malloc(sizeof(velocity_t));
	comp->base.id = VELOCITY;
	comp->x = x;
	comp->y = y;

	return (component_t*)comp;
}
