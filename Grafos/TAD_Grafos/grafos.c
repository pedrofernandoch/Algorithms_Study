/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Exercício - Grafos 
  *Nome: Pedro Fernando Christofoletti dos Santos 
  *NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

//Auxiliary function header
int __GRAPH_checkNode(node, node, int);
int __GRAPH_checkWeight(weight);
int __MATRIX_GRAPH_initializeGraph(MATRIX_GRAPH*, int);
int __LIST_GRAPH_insertEdge(node, node, weight, LIST_GRAPH*);
int __MATRIX_GRAPH_insertEdge(node, node, weight, MATRIX_GRAPH*);
int __LIST_GRAPH_check(node, node, LIST_GRAPH*);
int __MATRIX_GRAPH_check(node, node, MATRIX_GRAPH*);
LIST_GRAPH* __LIST_GRAPH_initializeGraph(int);


//========================== MAIN FUNCTIOS ==========================\\

void GRAPH_printMenu(){
    printf("\n                    MENU\n\n");
    printf("==============================================");
    printf("\n\nType the option number of your choice\n\n");
    printf("1- Create graph using adjacency list\n");
    printf("2- Create graph using adjacency matrix\n");
    printf("3- Insert edge\n");
    printf("4- Check for edge existence\n");
    printf("5- Free graph and exit\n");
    printf("==============================================\n\n");
}

// LIST GRAPH FUNCTIOS
void LIST_GRAPH_create(LIST_GRAPH** list_graph){
  
  int num_vertices=7;
  printf("How many vertices? (MAXIMUM: 6)\n");
  while(num_vertices > 6){
    scanf("%d",&num_vertices);
    if(num_vertices > 6) printf("\nPlease enter values lower than 7!\n");
  }
  *list_graph = __LIST_GRAPH_initializeGraph(num_vertices);
  (*list_graph)->num_vertices = num_vertices;
}

int LIST_GRAPH_insert(LIST_GRAPH *list_graph){

  if(!list_graph) return INVALID_GRAPH;

  node v,u;
  weight w;
  int valid=0;
  while(!valid){
    printf("First node: ");scanf("%d",&v);
    printf("Second node: ");scanf("%d",&u);
    valid = __GRAPH_checkNode(v,u,list_graph->num_vertices);
  }
  valid=0;
  while(!valid){
    printf("Weight: ");scanf("%d",&w);
    valid = __GRAPH_checkWeight(w);
  } 

  __LIST_GRAPH_insertEdge(v,u,w,list_graph);
        
  return SUCCESS;
}

int LIST_GRAPH_edgeExistence(LIST_GRAPH* list_graph){

  if(!list_graph) return INVALID_GRAPH;

  node v,u;
  int valid=0;
  while(!valid){
    printf("First node: ");scanf("%d",&v);
    printf("Second node: ");scanf("%d",&u);
    valid = __GRAPH_checkNode(v,u,list_graph->num_vertices);
  }
  int w = __LIST_GRAPH_check(v,u,list_graph);
  w = (w <= 0)?printf("\nThere is no edge\n") : printf("\nEdge weight: %d\n",w);

  return SUCCESS;
}

int LIST_GRAPH_freeGraph(LIST_GRAPH* list_graph){

  if(!list_graph) return INVALID_GRAPH;

  for(int i=0;i<list_graph->num_vertices;i++){

    LIST_GRAPH_EDGE *aux1, *aux2;
    aux1 = list_graph->vector[i];   
  
    while (aux1) {
		aux2 = aux1->next;
		free(aux1);
		aux1 = aux2;
	  }
  }

  free(list_graph);

  printf("\nSuccessful free!\n\n");

  return SUCCESS;  
}

// MATRIX GRAPH FUNCTIOS

void MATRIX_GRAPH_create(MATRIX_GRAPH *matrix_graph){

  int num_vertices=7;

  printf("How many vertices? (MAXIMUM: 6)\n");
  while(num_vertices > 6){
    scanf("%d",&num_vertices);
    if(num_vertices > 6) printf("\nPlease enter values lower than 7!\n");
  }
  __MATRIX_GRAPH_initializeGraph(matrix_graph, num_vertices);
}

int MATRIX_GRAPH_insert(MATRIX_GRAPH *matrix_graph){

  if(!matrix_graph) return INVALID_GRAPH;

  node v,u;
  weight w;
  int valid=0;
  while(!valid){
    printf("First node: ");scanf("%d",&v);
    printf("Second node: ");scanf("%d",&u);
    valid = __GRAPH_checkNode(v,u,matrix_graph->num_vertices);
  }
  valid=0;
  while(!valid){
    printf("Weight: ");scanf("%d",&w);
    valid = __GRAPH_checkWeight(w);
  }
 
  __MATRIX_GRAPH_insertEdge(v,u,w,matrix_graph);

  return SUCCESS;

}

int MATRIX_GRAPH_edgeExistence(MATRIX_GRAPH* matrix_graph){

  node v,u;
  int valid=0;
  while(!valid){
    printf("First node: ");scanf("%d",&v);
    printf("Second node: ");scanf("%d",&u);
    valid = __GRAPH_checkNode(v,u,matrix_graph->num_vertices);
  }
  int w = __MATRIX_GRAPH_check(v,u,matrix_graph);
  if(w>0) printf("\nEdge weight: %d\n",w);

  return SUCCESS;
}

//========================== AUXILIARY FUNCTIOS ======================\\

int __GRAPH_checkNode(node v, node u, int num_vertices){
  if(v>5 || u>5 || v<0 || u<0){
    printf("\nPlease enter node values bigger than 0 and lower than %d\n\n",num_vertices);
    return 0;
  } 
  else return 1;
}

int __GRAPH_checkWeight(weight w){
  if(w<=0){
    printf("\nPlease enter weight values bigger than 0\n\n");
    return 0;
  } 
  else return 1; 
}

// LIST GRAPH FUNCTIOS

LIST_GRAPH* __LIST_GRAPH_initializeGraph(int num_vertices){

  printf("\nBuild Successful!\n\n");
  
  return (LIST_GRAPH*) malloc(1*sizeof(LIST_GRAPH));
}

int __LIST_GRAPH_check(node v, node u, LIST_GRAPH* list_graph){

  LIST_GRAPH_EDGE *aux = list_graph->vector[v];
  int flag=0;
  weight w=0;

  while(aux && w == 0){
    if(aux->edge_node == u) w = aux->edge_weight;
    else aux = aux->next;
  }

  return w;
}

int __LIST_GRAPH_insertEdge(node v, node u, weight w, LIST_GRAPH* list_graph){

  LIST_GRAPH_EDGE *edgeNode = (LIST_GRAPH_EDGE*) calloc(1,sizeof(LIST_GRAPH_EDGE));

  edgeNode->edge_node = u;
  edgeNode->edge_weight = w;
  edgeNode->next = NULL;

  LIST_GRAPH_EDGE **aux = &list_graph->vector[v];  
  
  while(*aux){
    aux = &(*aux)->next;
  }

  (*aux) = edgeNode;

  printf("\nSuccessful insert!\n\n");

  return SUCCESS;
}

// MATRIX GRAPH FUNCTIOS

int __MATRIX_GRAPH_initializeGraph(MATRIX_GRAPH *matrix_graph, int num_vertices){

  if(!matrix_graph) return INVALID_GRAPH;

  matrix_graph->num_vertices = num_vertices;
  
  for(int i=0;i<matrix_graph->num_vertices;i++)
    for(int j=0;j<matrix_graph->num_vertices;j++)
      matrix_graph->matrix[i][j]=0;

  printf("\nBuild Successful!\n\n");
  
  return SUCCESS;
}

int __MATRIX_GRAPH_check(node v, node u, MATRIX_GRAPH* matrix_graph){

  if(!matrix_graph) return INVALID_GRAPH;

  if(matrix_graph->matrix[v][u] == 0){
    printf("\nThere is no edge\n");
  }

  return matrix_graph->matrix[v][u];
}

int __MATRIX_GRAPH_insertEdge(node v, node u, weight w, MATRIX_GRAPH* matrix_graph){
  
  matrix_graph->matrix[v][u] = w;

  printf("\nSuccessful insert!\n\n");

  return SUCCESS;
}