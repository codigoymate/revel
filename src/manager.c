#include <manager.h>

#include <hash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	void (*process_ptr)(iterator_t*);
	list_t* list;
	iterator_t* iterator;
	unsigned int flags;
	char* name;
} system_t;

hash_table_t* entities;
unsigned int count;
list_t* systems;
iterator_t* system_iter;

void clean_components(hash_table_t* comp) {
	hash_iterator_t* iter = hash_iterator_new(comp);
	while (hash_iterator_has_next(iter)) {
		free(
			hash_table_get(comp, hash_iterator_next(iter))
		);
	}

	// Remove itarator
	hash_iterator_delete(iter);
} 

void mgr_init(void) {
	entities = hash_table_new(ENTITY_MAX);
	count = 0;
	systems = list_new();
	system_iter = iterator_new(systems);
}

void mgr_close(void) {
	hash_iterator_t* iter = hash_iterator_new(entities);
	unsigned int i;

	// Clean systems
	for (i = 0; i < list_size(systems); i ++) {
		system_t* sys = list_get(systems, i);
		list_delete(sys->list);
		iterator_delete(sys->iterator);
		free(sys->name);
		free(sys);
	}
	list_delete(systems);
	iterator_delete(system_iter);

	// Remove components hash tables
	while (hash_iterator_has_next(iter)) {
		hash_table_t* components;
		components = hash_table_get(entities, hash_iterator_next(iter));
		clean_components(components);
		hash_table_delete(components);
	}

	// Remove itarator
	hash_iterator_delete(iter);

	// Remove entities hash table
	hash_table_delete(entities);
}

unsigned int mgr_new_entity(void) {
	hash_table_t* components;
	count ++;
	components = hash_table_new(COMPONENT_MAX);
	hash_table_put(entities, count, components);
	return count;
}

void mgr_add_component(unsigned int e, component_t* comp) {
	hash_table_t* components = hash_table_get(entities, e);
	hash_table_put(components, comp->id, comp);
}

int mgr_has_component(unsigned int e, unsigned int c) {
	hash_table_t* components = (hash_table_t*)hash_table_get(entities, e);
	return hash_table_get(components, c) != NULL;
}

component_t* mgr_get_component(unsigned int e, unsigned int c) {
	hash_table_t* components = (hash_table_t*)hash_table_get(entities, e);
	return (component_t*)hash_table_get(components, c);
}

void mgr_register(unsigned int e) {
	iterator_restart(system_iter);
	while (iterator_has_next(system_iter)) {
		system_t* sys = (system_t*) iterator_next(system_iter);
		hash_table_t* components = (hash_table_t*)hash_table_get(entities, e);
		hash_iterator_t* iter = hash_iterator_new(components);
		unsigned int flags = 0;
		unsigned int* ent;
		while (hash_iterator_has_next(iter)) {
			component_t* comp = (component_t*)hash_table_get(components, hash_iterator_next(iter));
			flags |= comp->id;
		}
		hash_iterator_delete(iter);
		if ((flags & sys->flags) == sys->flags) {
			ent = (unsigned int*) malloc(sizeof(unsigned int));
			*ent = e;
			list_push_back(sys->list, ent);
		}
	}
}

void mgr_add_system(char* name, unsigned int flags, void(*process_ptr)(iterator_t*)) {
	system_t* sys = (system_t*) malloc(sizeof(system_t));
	sys->name = strdup(name);
	sys->flags = flags;
	sys->process_ptr = process_ptr;
	sys->list = list_new();
	sys->iterator = iterator_new(sys->list);

	list_push_back(systems, sys);
	printf("Created %s system.\n", sys->name);
}

void mgr_process_systems(void) {
	iterator_restart(system_iter);
	while (iterator_has_next(system_iter)) {
		system_t* sys = (system_t*)iterator_next(system_iter);
		if (sys->process_ptr != NULL)
			sys->process_ptr(sys->iterator);
	}
}
