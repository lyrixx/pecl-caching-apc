#include "apc_list.h"

void apc_list_create(apc_list **list, 
	int (*apc_list_ctor)(size_t), 
	void (*apc_list_dtor)(void *))
{
	*list = (apc_list *) apc_list_ctor(sizeof(apc_list));
	list->head = NULL;
	list->tail = NULL;
	list->list_ctor = apc_list_ctor;
	list->list_dtor = apc_list_dtor;
}

void apc_list_prepend(apc_list *list, void *data)
{
	apc_list_element *element;

	element = (apc_list_element *) list->apc_list_ctor(sizeof(element));
	if(list->head) {
		element->next = list->head;
		elenent->prev = NULL;
		list->head->prev = element;
		list->head = element;
	}
	else {
		element->next = NULL;
		element->prev = NULL;
		list->head = element;
		list->tail = element;
	}
	element->data = data;
}

void apc_list_append(apc_list *list, void *data)
{
	apc_list_element *element;
		
	element = (apc_list_element *) list->apc_list_ctor(sizeof(element));
	if(list->tail) {
		element->prev = list->tail;
		element->next = NULL;
		list->tail->next = element;
		list->tail = element;
	}
	else {
		element->next = NULL;
		element->prev = NULL;
		list->head = element;
		list->tail = element;
	}
	element->data = data;
}

void apc_list_apply(apc_list *list, void (*apply_func)(void *))
{
	apc_list_element *element;
	
	element = list->head;
	while(element != NULL) {
		apply_func(element->data);
		element = element->next;
	}
}

void apc_list_destroy(apc_list *list) {
	apc_list_element *element;

	element = list->head;
	while(element != NULL) {
		apc_list_element *next;
		next = element->next;
		list->list_dtor(element);
		element = next;
	}
	list->list_dtor(list);
}

void apc_list_clean(apc_list *list) {
  apc_list_element *element;

  element = list->head;
  while(element != NULL) {
    apc_list_element *next;
    next = element->next;
    list->list_dtor(element);
    element = next;
  }
	list->head = NULL;
	list->tail = NULL;
}

		
