/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho II - Grafos 
  *Integrantes:
  *Daniel De Marco Fucci                            11218639
  *Pedro Fernando Christofoletti dos Santos         11218560
*/

#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define SUCCESS 1;

QUEUE *queue_create() {
	return (QUEUE *) calloc(1, sizeof(QUEUE));
}

int queue_enqueue(QUEUE *queue, char* elem) {
	if (!queue) return INVALID_QUEUE;

	QUEUE_ELEMENT *qelem = (QUEUE_ELEMENT *)	malloc(sizeof(QUEUE_ELEMENT));
	strcpy(qelem->elem,elem);
	qelem->next = NULL;

	if (!queue->counter) queue->first = qelem;
	else queue->last->next = qelem;
	queue->last = qelem;
	queue->counter++;
	return SUCCESS;
}

char* queue_dequeue(QUEUE *queue) {
	if (!queue) return NULL;
	if (!queue->counter) return NULL;

	char *e = (char*) malloc(100*sizeof(char));
	QUEUE_ELEMENT *elem = queue->first;
	queue->first = elem->next;
	queue->counter--;
	strcpy(e,elem->elem);
	free(elem);
	if (!queue->counter) queue->last = NULL;

	return e;
}

int queue_size(QUEUE *queue) {
	if (!queue) return  INVALID_QUEUE;
	return queue->counter;
}

int queue_free(QUEUE *queue) {
	if (!queue) return INVALID_QUEUE;
	int i;
	QUEUE_ELEMENT *elem;
	for (i = 0; i < queue->counter; i++) {
		elem = queue->first;
		queue->first = elem->next;
		free(elem);
	}
	free(queue);

	return SUCCESS;
}