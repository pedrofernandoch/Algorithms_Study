/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Exercício - Grafos 
  *Nome: Pedro Fernando Christofoletti dos Santos 
  *NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

int main(void) {

  int op,flag = 0;
  GRAPH matrix_graph;

  do {
		GRAPH_printMenu();
    scanf("%d",&op);
    system("clear");
    switch(op){
      case 1:{ //Create graph using matrix list
        if(flag==0){
         GRAPH_create(&matrix_graph);
          flag = 2;
        }else printf("\nYou have already created a graph!\n");
        break;
      }
      case 2:{ 
        if(!flag) printf("\nPlease create the graph first!\n");
        else { //Insert edge in matrix_graph
          GRAPH_insert(&matrix_graph);
        }
        break;
      }
      case 3:{ 
        if(!flag) printf("\nPlease create the graph first!\n");
        else{ //Check edge existence in matrix_graph
          int edge_weight = GRAPH_edgeExistence(&matrix_graph);
        }
        break;
      }
      case 4:{ // Depth First Search
        if(!flag) printf("\nPlease create the graph first!\n");
        else{
          GRAPH_depthFirstSearch(&matrix_graph);
        }
        break;
      }
      case 5:{ // Breadth First Search
        if(!flag) printf("\nPlease create the graph first!\n");
        else{
          GRAPH_breadthFirstSearch(&matrix_graph);
        }
        break;
      }
    }  
	} while(op != 0);
  
  return 0;
}