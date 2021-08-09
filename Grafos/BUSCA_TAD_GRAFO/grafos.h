/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Exercício - Grafos 
  *Nome: Pedro Fernando Christofoletti dos Santos 
  *NUSP: 11218560
*/

#ifndef _GRAFOS_
#define _GRAFOS_

#define MAXNUMVERTICES 6
#define SUCCESS 1
#define INVALID_GRAPH 0

typedef int weight;
typedef int node;
typedef int pointer;

typedef struct{
  weight matrix[MAXNUMVERTICES][MAXNUMVERTICES];
  int num_vertices;
} GRAPH;

//Header functions
void GRAPH_printMenu();
void GRAPH_create(GRAPH*);
int GRAPH_insert(GRAPH*);
int GRAPH_edgeExistence(GRAPH*);
int GRAPH_depthFirstSearch(GRAPH*);
int GRAPH_breadthFirstSearch(GRAPH*);

#endif