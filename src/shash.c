#include <hash.h>

#include <stdlib.h>
#include <limits.h>
#include <string.h>

unsigned int s_hash(str_hash_table_t* ht, char* key) {
	unsigned int hkey, i = 0;

	while( hkey < UINT_MAX && i < strlen(key)) {
		hkey = hkey << 8;
		hkey += key[i];
		i ++;
	}

	return hkey % ht->size;
}

void s_delete_node(struct str_hash_node_t* n) {
	struct str_hash_node_t* remove, * node;

	node = n;
	while (node != NULL) {
		remove = node;
		node = node->next;

		free(remove->key);
		free(remove);
	}
}

struct str_hash_node_t* s_get_node(str_hash_table_t* ht, char* key) {
	unsigned int hkey = s_hash(ht, key);
	struct str_hash_node_t* node = ht->table[hkey];
	if (node == NULL) return NULL;

	while (node != NULL) {
		if (strcmp(node->key, key) == 0) return node;
		node = node->next;
	}

	return NULL;
}

str_hash_table_t* str_hash_table_new(unsigned int size) {
	unsigned int i;
	str_hash_table_t* ht = (str_hash_table_t *) malloc(sizeof(str_hash_table_t));
	ht->table = malloc(sizeof(struct str_hash_node_t *) * size);
	ht->size = size;

	// cleans table
	for (i = 0; i < size; i ++) ht->table[i] = NULL;

	return ht;
}

void str_hash_table_delete(str_hash_table_t* ht) {
	unsigned int i = 0;

	for (; i < ht->size; i ++) {
		struct str_hash_node_t* node = ht->table[i];
		if (node == NULL) continue;
		s_delete_node(node);
	}

	free(ht->table);
	free(ht);
}

void str_hash_table_put(str_hash_table_t* ht, char* key, void* value) {
	// Find for existing key
	unsigned int hkey;
	struct str_hash_node_t* node = s_get_node(ht, key);

	if (node != NULL) {
		node->value = value;
	} else {
		node = (struct str_hash_node_t*) malloc(sizeof(struct str_hash_node_t));
		node->key = strdup(key);
		node->value = value;
		node->next = NULL;

		hkey = s_hash(ht, key);

		if (ht->table[hkey] == NULL) {
			ht->table[hkey] = node;
		} else {
			struct str_hash_node_t* n = ht->table[hkey];
			while (n->next != NULL) {
				n = n->next;
			}
			n->next = node;
		}
	}
}

void* str_hash_table_get(str_hash_table_t* ht, char* key) {
	struct str_hash_node_t* node = s_get_node(ht, key);
	if (node == NULL) return NULL;
	return node->value;
}

void* str_hash_table_remove(str_hash_table_t* ht, char* key) {
	unsigned int hkey = s_hash(ht, key);
	struct str_hash_node_t* node = ht->table[hkey];
	struct str_hash_node_t* prev = NULL;
	struct str_hash_node_t* remove = NULL;
	void* value;

	while (node != NULL) {
		//if (node->key == key) {
		if (strcmp(node->key, key) == 0) {
			remove = node;
			value = node->value;
			if (prev == NULL)
				ht->table[hkey] = node->next;
			else
				prev->next = node->next;
			free(remove->key);
			free(remove);
			return value;
		}

		prev = node;
		node = node->next;
	}

	return NULL;
}

void s_next_node(str_hash_iterator_t* iter) {
	if (iter->node != NULL) {
		iter->node = iter->node->next;
	}

	while (iter->node == NULL && iter->index < iter->ht->size) {
		iter->index ++; if (iter->index >= iter->ht->size) break;
		iter->node = iter->ht->table[iter->index];
	}
}

str_hash_iterator_t* str_hash_iterator_new(str_hash_table_t* ht) {
	str_hash_iterator_t* iter = (str_hash_iterator_t*) malloc(sizeof(str_hash_iterator_t));
	iter->ht = ht;
	iter->index = 0;
	iter->node = ht->table[0];
	while (iter->node == NULL && iter->index < iter->ht->size) {
		iter->index ++; if (iter->index >= iter->ht->size) break;
		iter->node = iter->ht->table[iter->index];
	}

	//next_node(iter);

	return iter;
}

void str_hash_iterator_delete(str_hash_iterator_t* iter) {
	free(iter);
}

int str_hash_iterator_has_next(str_hash_iterator_t* iter) {
	return iter->node != NULL;
}

char* str_hash_iterator_next(str_hash_iterator_t* iter) {
	char* key = iter->node->key;

	s_next_node(iter);

	return key;
}
