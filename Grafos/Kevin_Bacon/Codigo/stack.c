/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho II - Grafos 
  *Integrantes:
  *Daniel De Marco Fucci                            11218639
  *Pedro Fernando Christofoletti dos Santos         11218560
*/

#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define SUCCESS 1;

STACK *stack_create() {
	return (STACK *) calloc(1, sizeof(STACK));
}

LIST* list_create() {
  LIST *list = (LIST *) malloc(sizeof(LIST));
  list->size = 0;
  list->actors = (LIST_ELEMENT *) malloc(sizeof(LIST_ELEMENT) * 10000);
  return list;
}

int add_to_list(LIST *list,char *actorName, char *movieName, int ancestorPos) {
  list->actors[list->size].actorName = (char *) malloc(sizeof(char) * 100);
  list->actors[list->size].movieName = (char *) malloc(sizeof(char) * 100);
  strcpy(list->actors[list->size].actorName, actorName);
  strcpy(list->actors[list->size].movieName, movieName);
  list->actors[list->size].ancestorPos = ancestorPos;
  list->size++;
  return SUCCESS;
}
int free_list(LIST *list) {
  for (int i=0; i<list->size; i++) {
    free(list->actors[i].actorName);
    free(list->actors[i].movieName);
  }
  free(list->actors);
  free(list);
}

int stack_push(STACK *stack, char *elem) {
	if (!stack) return INVALID_STACK;
	STACK_ELEMENT *e = (STACK_ELEMENT *) malloc(sizeof(STACK_ELEMENT));
	strcpy(e->elem,elem);
	e->next = stack->top;
	stack->top = e;
	stack->counter++;

	return SUCCESS;
}

char *stack_pop(STACK *stack) {
	if (!stack) return NULL;

	if (!stack->counter) return NULL;

	char *e = (char*) malloc(100*sizeof(char));
	STACK_ELEMENT *elem = stack->top;
	stack->top = elem->next;
	strcpy(e, elem->elem);
	free(elem);
	stack->counter--;

	return e;
}

char *stack_top(STACK *stack) {
	if (!stack) return NULL;
	if (!stack->counter)	return NULL;
	return stack->top->elem;
}

int stack_size(STACK *stack) {
	if (!stack) return INVALID_STACK;
	return stack->counter;
}

int stack_free(STACK *stack) {
	if (!stack) return INVALID_STACK;
	int i;
	STACK_ELEMENT *e;
	for (i = 0; i < stack->counter; i++) {
		e = stack->top;
		stack->top = e->next;
		free(e);
	}
	free(stack);
	return SUCCESS;
}