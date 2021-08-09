/*  SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho I - Árvore B 
Integrantes:
Nome: Guilherme Filipe Feitosa dos Santos           NUSP: 11275092
Nome: Pedro Fernando Christofoletti dos Santos      NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

int main(void) {

	FILE *data_file = fopen("dados.txt","a+b");
  FILE *b_tree_index = fopen("index.dat","a+b");  
  int op=0;

  if (checkFile(data_file)) return 0;
  if (checkFile(b_tree_index)) return 0;

	do {
		printMenu();
    scanf("%d",&op);
    system("clear");
    switch(op){
      case 1: { //Create data file and b tree
        b_tree_setup(data_file,b_tree_index);
        break;
      }
      case 2:{ //Insert
        b_tree_insertRegistry(data_file,b_tree_index);
        break;
      }
      case 3:{ //Search by USP number
        b_tree_searchRegistry(data_file, b_tree_index);
        break;
      }
    }  
	} while(op != 0);

	closeFile(data_file);
  closeFile(b_tree_index);

  return 0;
}