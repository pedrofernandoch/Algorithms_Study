/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho II - Grafos 
  *Integrantes:
  *Daniel De Marco Fucci                            11218639
  *Pedro Fernando Christofoletti dos Santos         11218560
*/

#ifndef _QUEUE_H_
#define _QUEUE_H_

#define INVALID_QUEUE	-1
#define EMPTY_QUEUE	-2

struct queue_element {
	char elem[100];
	struct queue_element *next;
};

struct queue {
	struct queue_element *first, *last;
	int counter;
};

typedef struct queue QUEUE;
typedef struct queue_element QUEUE_ELEMENT;

QUEUE *queue_create();
int queue_enqueue(QUEUE *, char*);
char* queue_dequeue(QUEUE *);
int queue_size(QUEUE *);
int queue_free(QUEUE *);

#endif
