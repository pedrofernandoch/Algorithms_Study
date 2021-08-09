/*  SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 2 - Índices 
Nome: Pedro Fernando Christofoletti dos Santos 
NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include "file.h"

int main(void) {
	FILE *data_file = fopen("alunos.dad","a+b");
  FILE *index_file = fopen("index_file","a+b"); 
	int op=0;
  STUDENT aluno;

  if (checkFile(data_file))return 0;
  if (checkFile(index_file))return 0;

  INDEX *index = createIndex(index_file);
  closeFile(index_file);

	do {
		printMenu();
    scanf("%d",&op);
    system("clear");
    switch(op){
      case 1: { //Insert
        insertRegistry(data_file, index);
        break;
      }
      case 2:{ //Search
        searchRegistry(data_file, index);
        break;
      }
      case 3:{ //Remove
        removeRegistry(data_file, index);
        break;
      }
    }  
	} while(op != 0);

  rewriteIndexFile(index,index_file);

	closeFile(data_file);

return 0;

}