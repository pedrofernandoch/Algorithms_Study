#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

int main(void) {

  int op,flag = 0;
  MATRIX_GRAPH matrix_graph;
  LIST_GRAPH *list_graph;

  do {
		GRAPH_printMenu();
    scanf("%d",&op);
    system("clear");
    switch(op){
      case 1: { //Create graph using adjacency list
        if(flag==0){
          LIST_GRAPH_create(&list_graph);
          flag = 1;
        }else printf("\nYou have already created a graph!\n");
        break;
      }
      case 2:{ //Create graph using matrix list
        if(flag==0){
          MATRIX_GRAPH_create(&matrix_graph);
          flag = 2;
        }else printf("\nYou have already created a graph!\n");
        break;
      }
      case 3:{ 
        if(!flag) printf("\nPlease create the graph first!\n");
        else if(flag==1){ //Insert edge in list_graph
          LIST_GRAPH_insert(list_graph);
        } 
        else { //Insert edge in matrix_graph
          MATRIX_GRAPH_insert(&matrix_graph);
        }
        break;
      }
      case 4:{ 
        if(!flag) printf("\nPlease create the graph first!\n");
        else if(flag==1){ //Check edge existence in list_graph
          LIST_GRAPH_edgeExistence(list_graph);
        }
        else{ //Check edge existence in matrix_graph
          MATRIX_GRAPH_edgeExistence(&matrix_graph);
        }
        break;
      }
      case 5:{ // Free Graph and exit
        if(!flag) printf("\nPlease create the graph first!\n");
        else{
          LIST_GRAPH_freeGraph(list_graph);
        }
        break;
      }
    }  
	} while(op != 5);
  
  return 0;
}