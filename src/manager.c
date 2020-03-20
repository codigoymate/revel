#include <manager.h>

#include <hash.h>

hash_table_t* entities;
unsigned int count;

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
