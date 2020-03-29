#ifndef MANAGER_H
#define MANAGER_H

#define ENTITY_MAX		1000
#define COMPONENT_MAX	10
#define SYSTEM_MAX		10

#include <list.h>
#include <components.h>

//extern list_t* systems;
//extern iterator_t* system_iter;

void mgr_init(void);
void mgr_close(void);
unsigned int mgr_new_entity(void);
void mgr_add_component(unsigned int, component_t*);

void mgr_register(unsigned int);

/** Returns val != 0 if entity e has component c */
int mgr_has_component(unsigned int e, unsigned int c);
component_t* mgr_get_component(unsigned int e, unsigned int c);

void mgr_add_system(char* name, unsigned int flags, void(*process_ptr)(iterator_t*));

iterator_t* mgr_get_system_iterator(char* name);

void mgr_process_systems(void);

#endif
