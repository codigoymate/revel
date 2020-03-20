#ifndef MANAGER_H
#define MANAGER_H

#define ENTITY_MAX		1000
#define COMPONENT_MAX	10

#include <components.h>

void mgr_init(void);
void mgr_close(void);
unsigned int mgr_new_entity(void);
void mgr_add_component(unsigned int, component_t*);

/** Returns val != 0 if entity e has component c */
int mgr_has_component(unsigned int e, unsigned int c);

void mgr_register(unsigned int);


#endif
