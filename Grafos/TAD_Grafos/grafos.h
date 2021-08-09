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
} MATRIX_GRAPH;

struct LIST_GRAPH_EDGE{
  node edge_node;
  weight edge_weight;
  struct LIST_GRAPH_EDGE *next;
};

typedef struct LIST_GRAPH_EDGE LIST_GRAPH_EDGE;

typedef LIST_GRAPH_EDGE* graphPointer;

typedef struct{
  graphPointer vector[MAXNUMVERTICES];
  int num_vertices;
} LIST_GRAPH;

//Header functions

void GRAPH_printMenu();
int GRAPH_checkNode(node,node,int);
int GRAPH_checkWeight(weight);

//List graph functions
void LIST_GRAPH_create(LIST_GRAPH**);
int LIST_GRAPH_insert(LIST_GRAPH*);
int LIST_GRAPH_edgeExistence(LIST_GRAPH*);
int LIST_GRAPH_freeGraph(LIST_GRAPH*);

//Matrix graph functions
void MATRIX_GRAPH_create(MATRIX_GRAPH*);
int MATRIX_GRAPH_insert(MATRIX_GRAPH*);
int MATRIX_GRAPH_edgeExistence(MATRIX_GRAPH*);


#endif