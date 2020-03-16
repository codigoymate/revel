#ifndef LIST_H
#define LIST_H

struct node_t {
	void* data;
	struct node_t* next, * prev;
};

typedef struct {
	struct node_t* first, * last;
} list_t;

typedef struct {
	list_t* list;
	struct node_t* node;
} iterator_t;

list_t* list_new(void);
void list_delete(list_t*);

void list_push(list_t*, void*);
void* list_pop(list_t*);

void list_push_back(list_t*, void*);
void* list_pop_back(list_t*);

unsigned int list_size(list_t*);

void* list_get(list_t*, unsigned int);
void list_set(list_t*, unsigned int, void*);

void list_remove(list_t*, void*);
void list_remove_index(list_t*, unsigned int);

void list_swap(list_t*, unsigned int, unsigned int);

iterator_t* iterator_new(list_t* list);
void iterator_delete(iterator_t* iter);

int iterator_has_next(iterator_t* iter);
void* iterator_next(iterator_t* iter);

#endif
