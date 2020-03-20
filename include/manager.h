#ifndef MANAGER_H
#define MANAGER_H

#define ENTITY_MAX		1000
#define COMPONENT_MAX	10

#include <components.h>

void mgr_init(void);
void mgr_close(void);
unsigned int mgr_new_entity(void);
void mgr_add_component(unsigned int, component_t*);
void mgr_register(unsigned int);


#endif
