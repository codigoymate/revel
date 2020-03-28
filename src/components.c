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

component_t* render_texture_new(char* sprite) {
	render_texture_t* comp = (render_texture_t*) malloc(sizeof(render_texture_t));
	comp->base.base.id = RENDER;
	comp->base.type = RENDER_TEXTURE;
	comp->texture = rs_manager_get_texture(sprite);

	return (component_t*)comp;
}

component_t* render_string_new(char* font, char* string) {
	render_string_t* comp = (render_string_t*) malloc(sizeof(render_string_t));
	comp->base.base.id = RENDER;
	comp->base.type = RENDER_STRING;
	comp->font = rs_manager_get_bmp_font(font);
	strcpy(comp->string, string);

	return (component_t*) comp;
}

component_t* velocity_new(float x, float y) {
	velocity_t* comp = (velocity_t*) malloc(sizeof(velocity_t));
	comp->base.id = VELOCITY;
	comp->x = x;
	comp->y = y;

	return (component_t*)comp;
}

component_t* control_new(void) {
	control_t* comp = (control_t*) malloc(sizeof(control_t));
	comp->base.id = CONTROL;

	return (component_t*)comp;
}

component_t* wall_new(void) {
	wall_t* comp = (wall_t*) malloc(sizeof(wall_t));
	comp->base.id = WALL;

	return (component_t*)comp;
}