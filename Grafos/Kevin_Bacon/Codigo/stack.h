/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho II - Grafos 
  *Integrantes:
  *Daniel De Marco Fucci                            11218639
  *Pedro Fernando Christofoletti dos Santos         11218560
*/

#ifndef _STACK_H_
#define _STACK_H_

#define INVALID_STACK	-1
#define EMPTY_STACK	-2

struct stack_element {
	char elem[100];
	struct stack_element *next;
};

typedef struct LIST_ELEMENT {
  char *actorName;
  char *movieName;
  int ancestorPos;
} LIST_ELEMENT;

typedef struct LIST {
  LIST_ELEMENT *actors;
  int size;
} LIST;

struct stack {
	struct stack_element *top;
	int counter;
};

typedef struct stack STACK;
typedef struct stack_element STACK_ELEMENT;

LIST* list_create();
STACK* stack_create();
int stack_push(STACK *, char *);
char* stack_pop(STACK *);
char* stack_top(STACK *);
int stack_size(STACK *);
int stack_free(STACK *);
int add_to_list(LIST *,char *,char *, int);
int free_list(LIST *);

#endif
