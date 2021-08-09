/*  SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 1 - fileuivos 
Nome: Pedro Fernando Christofoletti dos Santos 
NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include "file.h"

int main(void) {
	FILE *file = fopen("alunos.dad","ab+");
	int op= 0;
  STUDENT aluno;

  if (checkFile(file))return 0;

	do {
		printMenu();
    scanf("%d",&op);
    system("clear");
    switch(op){
      case 1: { //Insert
        insertRegistry(file);
        break;
      }
      case 2:{ //Search
        searchRegistry(file);
        break;
      }
    }  
	} while(op != 0);

	closeFile(file);

return 0;

}