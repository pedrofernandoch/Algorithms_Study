/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho II - Grafos 
  *Integrantes:
  *Daniel De Marco Fucci                            11218639
  *Pedro Fernando Christofoletti dos Santos         11218560 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafos.h"
#include "queue.h"
#include "stack.h"

//Auxiliary function header
GRAPH* __GRAPH_initializeGraph(int);
void __GRAPH_create(GRAPH**);
int __GRAPH_readDataFromFile(GRAPH**);
int __GRAPH_binarySearchPosition(GRAPH*, char*, int, int);
int __GRAPH_insertNewActor(node, GRAPH*);
int __GRAPH_insertActor(node, node, weight, GRAPH*);
int __GRAPH_BFS(GRAPH*, char*, int);

//========================== MAIN FUNCTIOS ==========================\\

void GRAPH_printMenu(){
  printf("\n                    MENU\n\n");
  printf("==============================================");
  printf("\n\nType the option number of your choice\n\n");
  printf("1- Read file and create graph\n");
  printf("2- Search Actor/Actress KB's number\n");
  printf("3- Average KB's number and standard deviation\n");
  printf("4- Free graph and exit\n");
  printf("==============================================\n\n");
}

void GRAPH_start(GRAPH** graph){
  int returnReading=SUCCESS;
  //Allocating memory to graph
  __GRAPH_create(graph);

  //Reading data from file and inserting on graph
  returnReading = __GRAPH_readDataFromFile(graph);

  if (returnReading == ERROR_FILE) printf ("Falha ao abrir arquivo!\n");

  printf("\nBuild Successful!\n\n");

}

int GRAPH_searchKB(GRAPH* graph){

  if(!graph) return INVALID_GRAPH;

  char act[100];

	printf("Enter actor/actress: ");scanf(" %[^\n]s", act);
  printf("\n");
	__GRAPH_BFS(graph,act,1); 

  return SUCCESS;
}

int GRAPH_averageKB(GRAPH* graph){

  if(!graph) return INVALID_GRAPH;

  float kb_sum=0,kb;
  int n=0;
  float *vet = (float *) malloc(sizeof(float) * 10000);

  for(int i=0;i<graph->num_vertices;i++){
    kb = __GRAPH_BFS(graph, graph->vector[i]->edge_node,0);
    if(kb>0){
      vet[n] = kb;
      kb_sum+=kb;
      n++;
    } 
  }
  float sum=0;
  for(int i=0;i<n;i++){
    sum+= (float)((int)((vet[i]-(kb_sum/n)))^2);
  }
  printf("\nAverage KB's number: %f", kb_sum/n);
  printf("\nStandard deviation: %f\n\n\n",sqrt((sum/n)));
  
  free(vet);

  return SUCCESS;
}

int GRAPH_freeGraph(GRAPH* graph){

  if(!graph) return INVALID_GRAPH;

  for(int i=0;i<graph->num_vertices;i++){

    GRAPH_EDGE *aux1, *aux2;
    aux1 = graph->vector[i];   
  
    while (aux1) {
		aux2 = aux1->next;
		free(aux1);
		aux1 = aux2;
	  }
  }

  free(graph);

  printf("\nSuccessful free!\n\n");

  return SUCCESS;  
}

//========================== AUXILIARY FUNCTIOS ======================\\

void __GRAPH_create(GRAPH** graph){
  *graph = __GRAPH_initializeGraph(MAXNUMVERTICES+1);
  (*graph)->num_vertices = 0;
}

GRAPH* __GRAPH_initializeGraph(int num_vertices){
  return (GRAPH*) malloc(1*sizeof(GRAPH));
}

int __GRAPH_readDataFromFile(GRAPH** graph) {

  int arestas=0;
  int actorsCount = -1, pos = -1,size=0,aux=0;
  FILE* file = fopen("input-top-grossing.txt", "r");
  if (!file) return ERROR_FILE;
  char line[2000], *stringIterator, movie[200];
  ACTOR actors[250];

  while(fgets(line, sizeof(line), file)){
    aux++;
    actorsCount = -1;
    stringIterator = strtok(line, "/");
    while(stringIterator != NULL){
      actorsCount++;
      if(actorsCount > 0) {
        pos = __GRAPH_binarySearchPosition(*graph, stringIterator, 0, (*graph)->num_vertices-1);
        strcpy(actors[actorsCount-1].actor, stringIterator);
        size++;
        if (pos == -1) __GRAPH_insertNewActor(stringIterator, *graph); //New actor
      }else{
        strcpy(movie,stringIterator);
      }
      stringIterator = strtok(NULL, "/");
    }
    //Inserting edge to each actor with all other actors 
    for(int j=0;j<size;j++){
      for(int k=0;k<size;k++){
        if(strcmp(actors[j].actor, actors[k].actor)!=0){
          __GRAPH_insertActor(actors[j].actor, actors[k].actor, movie, *graph);
          arestas++;
        }
      }
    }
    size=0;
  }
  fclose(file);

  printf("Number of nodes: %d\n",(*graph)->num_vertices);
  printf("Number of edges: %d\n",arestas);

  return SUCCESS;
}

int __GRAPH_binarySearchPosition(GRAPH* graph, char* str, int start, int end){
  int middle, r; 

	if (start > end) { 
		return -1;
	}
	middle = (start + end) / 2; 
	r = strcmp(str, graph->vector[middle]->edge_node);
	if (r == 0) { 
		return middle; 
	} else if (r < 0) { 
		return __GRAPH_binarySearchPosition(graph, str, start, middle-1); 
	} else { 
		return __GRAPH_binarySearchPosition(graph, str, middle+1, end); 
	}

}

//New actor in index
int __GRAPH_insertNewActor(node actor, GRAPH* graph){

  graphPointer *iterator;
  int i;
  graph->num_vertices++;

  GRAPH_EDGE *newNode = (GRAPH_EDGE*) calloc(1,sizeof(GRAPH_EDGE));
  newNode->edge_node = (char *) malloc(sizeof(char) * 100);

  strcpy(newNode->edge_node, actor);
  newNode->edge_weight = NULL;
  newNode->next = NULL;

  iterator = graph->vector;
  i=graph->num_vertices-2;

  while(i >= 0 && (strcmp(iterator[i]->edge_node, newNode->edge_node) > 0)) {
    iterator[i + 1] = iterator[i];
    i--;
  }

  iterator[i+1]=newNode;

  return SUCCESS;
}

//Add actor to a list of an actor in index
int __GRAPH_insertActor(node first_actor, node next_actor, weight w, GRAPH* graph){

  GRAPH_EDGE *edgeNode = (GRAPH_EDGE*) calloc(1,sizeof(GRAPH_EDGE));
  edgeNode->edge_node = (char *) malloc(sizeof(char) * 100);
  edgeNode->edge_weight = (char *) malloc(sizeof(char) * 100);

  strcpy(edgeNode->edge_node,next_actor);
  strcpy(edgeNode->edge_weight,w);
  edgeNode->next = NULL;

  int pos = __GRAPH_binarySearchPosition(graph, first_actor, 0, graph->num_vertices);

  GRAPH_EDGE **aux = &graph->vector[pos];  
  
  while(*aux){
    aux = &(*aux)->next;
  }

  (*aux) = edgeNode;

  return SUCCESS;
}

//BFS algorithm
int __GRAPH_BFS(GRAPH* graph, char* startVertex, int show) {

  int pos1 = __GRAPH_binarySearchPosition(graph, startVertex, 0, graph->num_vertices -1);
  int ancestorPos = -1;
  GRAPH_EDGE *nodeIter;
  GRAPH_EDGE *nodeIterAux;

  if(pos1==-1){
    printf("Actor/actress not found!\n");
    return -1;
  }

  QUEUE *queue = queue_create();
  LIST* tracking_list = list_create();

  int kb,kb_flag=0,state[graph->num_vertices];
  for(int i=0;i<graph->num_vertices;i++)state[i]=0;
  state[pos1] = 1;
  queue_enqueue(queue, startVertex);
  add_to_list(tracking_list,startVertex,startVertex, ancestorPos);

  while (queue_size(queue) && kb_flag==0) {
    ancestorPos++;

    char currentVertex[200];
    strcpy(currentVertex,queue_dequeue(queue));
  
    int pos2 = __GRAPH_binarySearchPosition(graph, currentVertex, 0, graph->num_vertices -1); 
    GRAPH_EDGE* temp = graph->vector[pos2]->next;
    while (temp) {
      char adjVertex[200]; 
      strcpy(adjVertex,temp->edge_node);
      if(!strcmp(adjVertex,"Bacon, Kevin")){
        kb_flag = 1;
        add_to_list(tracking_list, adjVertex, temp->edge_weight, ancestorPos);
        break;
      }
      int pos3 = __GRAPH_binarySearchPosition(graph, adjVertex, 0, graph->num_vertices-1);
      if (state[pos3] == 0) {
        state[pos3] = 1;
        queue_enqueue(queue, adjVertex);
        add_to_list(tracking_list, adjVertex, temp->edge_weight, ancestorPos);
      }
      temp = temp->next;
    }
  }
  queue_free(queue);

  GRAPH_EDGE *wayToBacon = (GRAPH_EDGE *) malloc(sizeof(GRAPH_EDGE));
  wayToBacon->edge_node = (char *) malloc(sizeof(char) * 100);
  wayToBacon->edge_weight = (char *) malloc(sizeof(char) * 100);
  strcpy(wayToBacon->edge_node, tracking_list->actors[tracking_list->size-1].actorName);
  strcpy(wayToBacon->edge_weight, tracking_list->actors[tracking_list->size-1].movieName);
  wayToBacon->next = NULL;

  ancestorPos = tracking_list->actors[tracking_list->size-1].ancestorPos;

  GRAPH_EDGE *next_node = wayToBacon;
  
  kb = 0;
  while (ancestorPos != -1) {
    kb++;
    nodeIter = (GRAPH_EDGE *) malloc(sizeof(GRAPH_EDGE));
    nodeIter->edge_node = (char *) malloc(sizeof(char) * 100);
    nodeIter->edge_weight = (char *) malloc(sizeof(char) * 100);
    strcpy(nodeIter->edge_node, tracking_list->actors[ancestorPos].actorName);
    strcpy(nodeIter->edge_weight, tracking_list->actors[ancestorPos].movieName);
    nodeIter->next = next_node;

    next_node = nodeIter;
    ancestorPos = tracking_list->actors[ancestorPos].ancestorPos;
  }

  if(show){ //The function __GRAPH_BFS  is used for both purpose, find actos kb and average kb, so the parameter "show" determines if the trail will or will not be printed
    if(kb_flag){
      printf("%s tem KB = %d\n",startVertex,kb);
      while (nodeIter->next) {
        printf("%s atuou em %s com %s\n", nodeIter->edge_node, nodeIter->next->edge_weight, nodeIter->next->edge_node);
        nodeIterAux = nodeIter;
        nodeIter = nodeIter->next;
        free(nodeIterAux->edge_node);
        free(nodeIterAux->edge_weight);
        free(nodeIterAux);
      }
    }
    else{
      printf("%s tem KB = infinito\n",startVertex);
      kb=-1;
    } 
  }
  free_list(tracking_list);

  return kb;
}