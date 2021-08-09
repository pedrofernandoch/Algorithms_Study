/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Exercício - Grafos 
  *Nome: Pedro Fernando Christofoletti dos Santos 
  *NUSP: 11218560
*/

#ifndef _QUEUE_H_
#define _QUEUE_H_

#define INVALID_QUEUE	-1
#define EMPTY_QUEUE	-2

struct queue_element {
	int elem;
	struct queue_element *next;
};

struct queue {
	struct queue_element *first, *last;
	int counter;
};

typedef struct queue QUEUE;
typedef struct queue_element QUEUE_ELEMENT;

QUEUE *queue_create();
int queue_enqueue(QUEUE *, int);
int queue_dequeue(QUEUE *, int *);
int queue_size(QUEUE *);
int queue_free(QUEUE *);

#endif
