#include <manager.h>

#include <hash.h>

hash_table_t* entities;
hash_table_t* components;

void mgr_init(void) {
	entities = hash_table_new(ENTITY_MAX);
}

void mgr_close(void) {
	hash_table_delete(entities);
}
