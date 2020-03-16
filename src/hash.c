#include <hash.h>
#include <stdlib.h>

unsigned int hash(hash_table_t* ht, unsigned int key) {
	return key % ht->size;
}

void delete_node(struct hash_node_t* n) {
	struct hash_node_t* remove, * node;

	node = n;
	while (node != NULL) {
		remove = node;
		node = node->next;

		free(remove);
	}
}

struct hash_node_t *get_node(hash_table_t* ht, unsigned int key) {
	unsigned int hkey = hash(ht, key);
	struct hash_node_t* node = ht->table[hkey];
	if (node == NULL) return NULL;

	while (node != NULL) {
		if (node->key == key) return node;
		node = node->next;
	}

	return NULL;
}

hash_table_t* hash_table_new(unsigned int size) {
	unsigned int i;
	hash_table_t* ht = (hash_table_t *) malloc(sizeof(hash_table_t));
	ht->table = /*(struct hash_node_t *)*/ malloc(sizeof(struct hash_node_t *) * size);
	ht->size = size;

	// cleans table
	for (i = 0; i < size; i ++) ht->table[i] = NULL;

	return ht;
}

void hash_table_delete(hash_table_t* ht) {
	unsigned int i = 0;

	for (; i < ht->size; i ++) {
		struct hash_node_t* node = ht->table[i];
		if (node == NULL) continue;
		delete_node(node);
	}

	free(ht->table);
	free(ht);
}

void hash_table_put(hash_table_t* ht, unsigned int key, void* value) {
	
	// Find for existing key
	unsigned int hkey;
	struct hash_node_t* node = get_node(ht, key);

	if (node != NULL) {
		node->value = value;
	} else {
		node = (struct hash_node_t*) malloc(sizeof(struct hash_node_t));
		node->key = key;
		node->value = value;
		node->next = NULL;

		hkey = hash(ht, key);

		if (ht->table[hkey] == NULL) {
			ht->table[hkey] = node;
		} else {
			struct hash_node_t* n = ht->table[hkey];
			while (n->next != NULL) {
				n = n->next;
			}
			n->next = node;
		}
	}
}

void* hash_table_get(hash_table_t* ht, unsigned int key) {
	unsigned int hkey = hash(ht, key);
	struct hash_node_t* node = ht->table[hkey];

	if (node == NULL) return NULL;

	while (node != NULL) {
		if (node->key == key) return node->value;
		node = node->next;
	}

	return NULL;
}

void* hash_table_remove(hash_table_t* ht, unsigned int key) {
	unsigned int hkey = hash(ht, key);
	struct hash_node_t* node = ht->table[hkey];
	struct hash_node_t* prev = NULL;
	struct hash_node_t* remove = NULL;
	void* value;

	while (node != NULL) {
		if (node->key == key) {
			remove = node;
			value = node->value;
			if (prev == NULL)
				ht->table[hkey] = node->next;
			else
				prev->next = node->next;
			free(remove);
			return value;
		}

		prev = node;
		node = node->next;
	}

	return NULL;
}

void next_node(hash_iterator_t* iter) {
	if (iter->node != NULL) {
		iter->node = iter->node->next;
	}

	while (iter->node == NULL && iter->index < iter->ht->size) {
		iter->index ++; if (iter->index >= iter->ht->size) break;
		iter->node = iter->ht->table[iter->index];
	}
}

hash_iterator_t* hash_iterator_new(hash_table_t* ht) {
	hash_iterator_t* iter = (hash_iterator_t*) malloc(sizeof(hash_iterator_t));
	iter->ht = ht;
	iter->index = 0;
	iter->node = ht->table[0];
	while (iter->node == NULL && iter->index < iter->ht->size) {
		iter->index ++; if (iter->index >= iter->ht->size) break;
		iter->node = iter->ht->table[iter->index];
	}

	return iter;
}

void hash_iterator_delete(hash_iterator_t* iter) {
	free(iter);
}

int hash_iterator_has_next(hash_iterator_t* iter) {
	return iter->node != NULL;
}

unsigned int hash_iterator_next(hash_iterator_t* iter) {
	unsigned int key = iter->node->key;

	next_node(iter);

	return key;
}
