#include <factory.h>

#include <manager.h>
#include <components.h>

void create_player(float x, float y) {
	unsigned int e = mgr_new_entity();
	mgr_add_component(e, transform_new(x, y, 64, 64));
	mgr_add_component(e, velocity_new(0.0f, 0.0f));
	mgr_add_component(e, control_new());	
	mgr_add_component(e, render_texture_new("circle"));
	mgr_register(e);
}

void create_wall(float x, float y) {
	unsigned int e = mgr_new_entity();
	mgr_add_component(e, transform_new(x, y, 64, 64));
	mgr_add_component(e, render_texture_new("simple_grass"));
	mgr_register(e);
}
