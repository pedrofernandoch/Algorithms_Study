/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho II - Grafos 
  *Integrantes:
  *Daniel De Marco Fucci                            11218639
  *Pedro Fernando Christofoletti dos Santos         11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

int main(void) {

  int op,flag = 0;
  GRAPH *graph;

  do {
		GRAPH_printMenu();
    scanf("%d",&op);
    system("clear");
    switch(op){
      case 1:{ //Read file and create graph
        if(!flag){
          GRAPH_start(&graph);
          flag=1;
        }else printf("\nYou have already created the graph!\n");
        break;
      }
      case 2:{ //Search Actor/Actress KB's number
        if(!flag) printf("\nPlease read file and create the graph first!\n");
        else GRAPH_searchKB(graph);
        break;
      }
      case 3:{ //Average KB's number and standard deviation
        if(!flag) printf("\nPlease read file and create the graph first!\n");
        else GRAPH_averageKB(graph);
        break;
      }
      case 4:{ // Free Graph and exit
        if(!flag) printf("\nPlease read file and create the graph first!\n");
        else{
          GRAPH_freeGraph(graph);
        }
        break;
      }
    }  
	} while(op != 4);
  
  return 0;
}