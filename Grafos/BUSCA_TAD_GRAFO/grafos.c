/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Exercício - Grafos 
  *Nome: Pedro Fernando Christofoletti dos Santos 
  *NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"
#include "queue.h"

#define INITIAL 1
#define WAITING 2
#define VISITED 3

//Auxiliary function header
int __GRAPH_checkNode(node, node, int);
int __GRAPH_checkWeight(weight);
int __GRAPH_initializeGraph(GRAPH*, int);
int __GRAPH_insertEdge(node, node, weight, GRAPH*);
int __GRAPH_checkEdge(node, node, GRAPH*);
void __GRAPH_DFS_recursive(int, int*, int, GRAPH*);
void __GRAPH_BFS(int, int*, GRAPH*);

//========================== MAIN FUNCTIOS ==========================\\

void GRAPH_printMenu(){
    printf("\n                    MENU\n\n");
    printf("==============================================");
    printf("\n\nType the option number of your choice\n\n");
    printf("1- Create graph using adjacency matrix\n");
    printf("2- Insert edge\n");
    printf("3- Check for edge existence\n");
    printf("4- Depth First Search\n");
    printf("5- Breadth First Search\n\n");
    printf("==============================================\n\n");
    printf("Type 0 to exit\n\n");
}

// MATRIX GRAPH FUNCTIOS

void GRAPH_create(GRAPH *graph){

  int num_vertices=9;

  printf("How many vertices? (MAXIMUM: %d)\n\n",MAXNUMVERTICES);
  while(num_vertices > MAXNUMVERTICES || num_vertices <=0){
    scanf("%d",&num_vertices);
    if(num_vertices >= (MAXNUMVERTICES+1)) printf("\nPlease enter values lower than %d!\n\n",MAXNUMVERTICES+1);
    if(num_vertices <= 0) printf("\nPlease enter positive values!\n\n");
  }
  __GRAPH_initializeGraph(graph, num_vertices);
}

int GRAPH_insert(GRAPH *graph){

  if(!graph) return INVALID_GRAPH;

  node v,u;
  weight w;
  int valid=0;
  while(!valid){
    printf("First node: ");scanf("%d",&v);
    printf("Second node: ");scanf("%d",&u);
    valid = __GRAPH_checkNode(v,u,graph->num_vertices);
  }
  valid=0;
  while(!valid){
    printf("Weight: ");scanf("%d",&w);
    valid = __GRAPH_checkWeight(w);
  }
 
  __GRAPH_insertEdge(v,u,w,graph);

  return SUCCESS;

}

int GRAPH_edgeExistence(GRAPH* graph){

  node v,u;
  int valid=0;
  while(!valid){
    printf("First node: ");scanf("%d",&v);
    printf("Second node: ");scanf("%d",&u);
    valid = __GRAPH_checkNode(v,u,graph->num_vertices);
  }
  int w = __GRAPH_checkEdge(v,u,graph);
  if(w>0) printf("\nEdge exists and its weight is: %d\n",w);

  return w;
}

int GRAPH_depthFirstSearch(GRAPH *graph){
  
  if(!graph) return INVALID_GRAPH;

  int n = graph->num_vertices;
  int visited[n],vertex;
  for(int i=0;i<n;i++) visited[i]=0;
  printf("Enter Start Vertex for DFS: ");scanf("%d",&vertex);
  __GRAPH_DFS_recursive(vertex, visited, n, graph);

  return SUCCESS;
}

int GRAPH_breadthFirstSearch(GRAPH* graph){

  if(!graph) return INVALID_GRAPH;

  int v,state[graph->num_vertices];
	
	for(v=0; v<graph->num_vertices; v++) 
		state[v] = INITIAL;
	
	printf("Enter Start Vertex for BFS: ");scanf("%d", &v);
  printf("\n");
	__GRAPH_BFS(v,state,graph); 

  return SUCCESS;
}

//========================== AUXILIARY FUNCTIOS ======================\\

int __GRAPH_checkNode(node v, node u, int num_vertices){
  if(v>(num_vertices-1) || u>(num_vertices-1) || v<0 || u<0){
    printf("\nPlease enter node values equal or higher than 0 and lower than %d\n\n",num_vertices);
    return 0;
  } 
  else return 1;
}

int __GRAPH_checkWeight(weight w){
  if(w<=0){
    printf("\nPlease enter weight values higher than 0\n\n");
    return 0;
  } 
  else return 1; 
}

int __GRAPH_initializeGraph(GRAPH *graph, int num_vertices){

  if(!graph) return INVALID_GRAPH;

  graph->num_vertices = num_vertices;
  
  for(int i=0;i<graph->num_vertices;i++)
    for(int j=0;j<graph->num_vertices;j++)
      graph->matrix[i][j]=0;

  printf("\nBuild Successful!\n\n");
  
  return SUCCESS;
}

int __GRAPH_checkEdge(node v, node u, GRAPH* graph){

  if(!graph) return INVALID_GRAPH;

  if(graph->matrix[v][u] == 0){
    printf("\nThere is no edge\n");
  }

  return graph->matrix[v][u];
}

int __GRAPH_insertEdge(node v, node u, weight w, GRAPH* graph){
  
  graph->matrix[v][u] = w;

  printf("\nSuccessful insert!\n\n");

  return SUCCESS;
}

void __GRAPH_DFS_recursive(int vertex, int *visited,int n,GRAPH *graph){

  int j;
	printf("\n%d\n",vertex);
  visited[vertex]=1;
	
	for(j=0;j<n;j++){
    if(!visited[j]&&graph->matrix[vertex][j]!=0){
      __GRAPH_DFS_recursive(j,visited,n,graph);
    }
  }

}

void __GRAPH_BFS(int v,int *state, GRAPH *graph){
	int i;
	
  QUEUE *queue = queue_create();
	queue_enqueue(queue, v);
	state[v] = WAITING;
  int error;
	
	while(queue_size(queue)){
		v = queue_dequeue(queue, &error);
		printf("%d ",v);
		state[v] = VISITED;
		
		for(i=0; i<graph->num_vertices; i++){
			if(graph->matrix[v][i] != 0 && state[i] == INITIAL){
				queue_enqueue(queue, i);
				state[i] = WAITING;
			}
		}
	}
	printf("\n");
}