/**Hash Table Lib
*  Author: Javier Candales (Jasón)
*  Year: 2020
*  Description: Provides a hash_table_t data type to store a key/value pair and access to them
*       instantly through a hash algorithm.
*/

#ifndef HASH_H
#define HASH_H

struct hash_node_t {
	unsigned int key;
	void* value;
	struct hash_node_t* next;
};

typedef struct {
	struct hash_node_t** table;
	unsigned int size;
} hash_table_t;

struct str_hash_node_t {
	char* key;
	void* value;
	struct str_hash_node_t* next;
};

typedef struct {
	struct str_hash_node_t** table;
	unsigned int size;
} str_hash_table_t;

// unsigned int iterator
typedef struct {
	hash_table_t* ht;
	unsigned int index;
	struct hash_node_t* node;
} hash_iterator_t;

// str iterator
typedef struct {
	str_hash_table_t* ht;
	unsigned int index;
	struct str_hash_node_t* node;
} str_hash_iterator_t;

/**Returns a new instance of hash_table_t indicating the size.
*  @param size the number of elements
*/
hash_table_t* hash_table_new(unsigned int size);

/**Deletes the hash_table_t instance and the internal data of it
*/
void hash_table_delete(hash_table_t* ht);

/**Store a pair data (key/value) on the hash table
*/
void hash_table_put(hash_table_t* ht, unsigned int key, void* value);

/**Returns the pointer to value indicating the key. If the pair not
*  exists, then returns NULL
*/
void* hash_table_get(hash_table_t* ht, unsigned int key);

/**Removes the pair element indicating the key on hash table. If the
*  pair not exists then returns NULL, for otherwise, return the value
*  of removed pair
*/
void* hash_table_remove(hash_table_t*, unsigned int);


str_hash_table_t* str_hash_table_new(unsigned int size);

void str_hash_table_delete(str_hash_table_t* ht);

void str_hash_table_put(str_hash_table_t* ht, char* key, void* value);

void* str_hash_table_get(str_hash_table_t* ht, char* key);

void* str_hash_table_remove(str_hash_table_t*, char* key);


// unsgined int interator
hash_iterator_t* hash_iterator_new(hash_table_t* ht);
void hash_iterator_delete(hash_iterator_t* iter);

int hash_iterator_has_next(hash_iterator_t* iter);
unsigned int hash_iterator_next(hash_iterator_t* iter);

// str iterator
str_hash_iterator_t* str_hash_iterator_new(str_hash_table_t* ht);
void str_hash_iterator_delete(str_hash_iterator_t* iter);

int str_hash_iterator_has_next(str_hash_iterator_t* iter);
char* str_hash_iterator_next(str_hash_iterator_t* iter);

#endif
