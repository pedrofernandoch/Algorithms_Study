/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 3 - Índices 
  *Nome: Pedro Fernando Christofoletti dos Santos 
  *NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int main(void) {

	FILE *data_file = fopen("alunos.dad","a+b");
  FILE *primary_index_file = fopen("primary_index_file","a+b");
  FILE *secondary_index_file = fopen("secondary_index_file","a+b");
  FILE *secondary_list_file = fopen("secondary_list_file","a+b");   
  STUDENT aluno;
  int op=0;

  if (checkFile(data_file))return 0;
  if (checkFile(primary_index_file))return 0;
  if (checkFile(secondary_index_file))return 0;
  if (checkFile(secondary_list_file))return 0;

  PRIMARY_INDEX *primary_index = createPrimaryIndex(primary_index_file);
  SECONDARY_INDEX *secondary_index = createSecondaryIndex(secondary_index_file,secondary_list_file);

  closeFile(primary_index_file);
  closeFile(secondary_index_file);
  closeFile(secondary_list_file);

	do {
		printMenu();
    scanf("%d",&op);
    system("clear");
    switch(op){
      case 1: { //Insert
        insertRegistry(data_file, primary_index, secondary_index);
        break;
      }
      case 2:{ //Search by USP number
        searchRegistryByNusp(data_file, primary_index);
        break;
      }
      case 3:{ //Search by last name
        searchRegistryByLN(data_file, secondary_index, primary_index);
        break;
      }
      case 4:{ //Remove by USP number
        removeRegistryByNusp(data_file, primary_index, secondary_index);
        break;
      }
      case 5:{ //Remove by last name
        removeRegistryByLN(data_file, secondary_index, primary_index);
        break;
      }
    }  
	} while(op != 0);

  rewritePrimaryIndexFile(primary_index,primary_index_file);
  rewriteSecondaryIndexFile(secondary_index,secondary_index_file, secondary_list_file);
	closeFile(data_file);
  freePrimaryIndex(primary_index);
  freeSecondaryIndex(secondary_index);

  return 0;
}