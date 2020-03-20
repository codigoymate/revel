#include <manager.h>

#include <hash.h>
#include <stdlib.h>

hash_table_t* entities;
unsigned int count;

void clean_components(hash_table_t* comp) {
	hash_iterator_t* iter = hash_iterator_new(comp);
	while (hash_iterator_has_next(iter)) {
		free(
			hash_table_get(comp, hash_iterator_next(iter))
		);
	}
} 

void mgr_init(void) {
	entities = hash_table_new(ENTITY_MAX);
	count = 0;
}

void mgr_close(void) {
	// Remove components hash tables
	hash_iterator_t* iter = hash_iterator_new(entities);
	while (hash_iterator_has_next(iter)) {
		hash_table_t* components;
		components = hash_table_get(entities, hash_iterator_next(iter));
		clean_components(components);
		hash_table_delete(components);
	}

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