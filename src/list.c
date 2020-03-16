#include <list.h>

#include <stdlib.h>

struct node_t* new_node(void* data) {
	struct node_t* node = malloc(sizeof(struct node_t));
	node->data = data;
	node->prev = NULL;
	node->next = NULL;

	return node;
}

void remove_node(list_t* list, struct node_t* node) {
	if (list->first == list->last) {
		list_pop(list);
	} else if (node == list->first) {
		list_pop(list);
	} else if (node == list->last) {
		list_pop_back(list);
	} else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node);
	}
}

list_t* list_new(void) {
	list_t* list = malloc(sizeof(list_t));
	list->first = NULL;
	list->last = NULL;

	return list;
}

void list_delete(list_t* list) {
	while (list->first != NULL) {
		list_pop(list);
	}

	free(list);
}

void list_push(list_t* list, void* data) {

	if (list->first == NULL) {
		list->first = new_node(data);
		list->last = list->first;
	} else {
		struct node_t* node = new_node(data);
		node->next = list->first;
		list->first->prev = node;
		list->first = node;
	}
}

void* list_pop(list_t* list) {
	void* data = NULL;
	struct node_t* node = list->first;
	if (node == NULL) return data;

	if (node->next != NULL) {
		node->next->prev = NULL;
		list->first = node->next;
	} else {
		list->first = NULL;
		list->last = NULL;
	}

	data = node->data;
	free(node);

	return data;
}

void list_push_back(list_t* list, void* data) {
	if (list->first == NULL) {
		list->first = new_node(data);
		list->last = list->first;
	} else {
		struct node_t* node = new_node(data);
		node->prev = list->last;
		list->last->next = node;
		list->last = node;
	}
}

void* list_pop_back(list_t* list) {
	void* data = NULL;
	struct node_t* node = list->last;

	if (node == NULL) return data;

	if (node->prev != NULL) {
		node->prev->next = NULL;
		list->last = node->prev;
	} else {
		list->first = NULL;
		list->last = NULL;
	}

	data = node->data;
	free(node);
	return data;
}

unsigned int list_size(list_t* list) {
	unsigned int i = 0;
	struct node_t* node = list->first;

	while (node != NULL) {
		node = node->next; i ++;
	}

	return i;
}

void* list_get(list_t* list, unsigned int index) {
	unsigned int i = 0;
	struct node_t* node = list->first;

	while (node != NULL) {
		if (index == i) return node->data;
		node = node->next; i ++;
	}

	return NULL;
}

void list_set(list_t* list, unsigned int index, void* data) {
	unsigned int i = 0;
	struct node_t* node = list->first;

	while (node != NULL) {
		if (index == i) node->data = data;
		node = node->next; i ++;
	}
}

void list_remove(list_t* list, void* data) {
	struct node_t* node = list->first;

	while (node != NULL) {
		if (node->data == data) {
			break;
		}
		node = node->next;
	}

	if (node == NULL) return ;

	remove_node(list, node);
}

void list_remove_index(list_t* list, unsigned int index) {
	unsigned int i = 0;
	struct node_t* node = list->first;

	while (node != NULL) {
		if (i == index) {
			break;
		}
		node = node->next; i ++;
	}

	if (node == NULL) return ;

	remove_node(list, node);
}

void list_swap(list_t* list, unsigned int i1, unsigned int i2) {
	void* data = list_get(list, i1);
	list_set(list, i1, list_get(list, i2));
	list_set(list, i2, data);
}

iterator_t* iterator_new(list_t* list) {
	iterator_t* iter = (iterator_t*) malloc(sizeof(iterator_t));
	iter->list = list;
	iter->node = list->first;

	return iter;
}

void iterator_delete(iterator_t* iter) {
	free(iter);
}

int iterator_has_next(iterator_t* iter) {
	return iter->node != NULL;
}

void* iterator_next(iterator_t* iter) {
	void* data = iter->node->data;
	iter->node = iter->node->next;

	return data;
}

