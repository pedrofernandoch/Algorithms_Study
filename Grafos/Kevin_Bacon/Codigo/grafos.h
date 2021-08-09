/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho II - Grafos 
  *Integrantes:
  *Daniel De Marco Fucci                            11218639
  *Pedro Fernando Christofoletti dos Santos         11218560
*/

#ifndef _GRAFOS_
#define _GRAFOS_

#define MAXNUMVERTICES 10000
#define SUCCESS 1
#define INVALID_GRAPH 0
#define ERROR_FILE -1

typedef char* weight;
typedef char* node;

typedef struct{
  char actor[100];
  int size;
}ACTOR;

struct GRAPH_EDGE{
  node edge_node;
  weight edge_weight;
  struct GRAPH_EDGE *next;
};

typedef struct GRAPH_EDGE GRAPH_EDGE;

typedef GRAPH_EDGE* graphPointer;

typedef struct{
  graphPointer vector[MAXNUMVERTICES];
  int num_vertices;
} GRAPH;

//Header functions
void GRAPH_printMenu();
void GRAPH_start(GRAPH**);
int readDataFromFile(GRAPH**);
int GRAPH_searchKB(GRAPH*);
int GRAPH_averageKB(GRAPH*);
int GRAPH_freeGraph(GRAPH*);

#endif