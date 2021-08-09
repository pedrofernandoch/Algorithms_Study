/*  SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho I - Árvore B 
Integrantes:
Nome: Guilherme Filipe Feitosa dos Santos           NUSP: 11275092
Nome: Pedro Fernando Christofoletti dos Santos      NUSP: 11218560
*/

#ifndef _B_TREE_
#define _B_TREE_

//Defines used as function's return
#define SUCCESS                    0
#define INVALID_FILE              -1
#define INVALID_NODE              -2
#define INVALID_B_TREE_INDEX      -3
#define RRN_NOT_FOUND             -4
#define RRN_EXISTENT              -5
#define EMPTY_FILE                -6

#define SIZE 100
#define ORDER 170 //Tree order based on a 4Kb page

typedef int keyType;

typedef struct {
  keyType NUSP; 
  long RRN; 
} KEY; 

typedef struct {
  int counter; 
  KEY keys[ORDER-1]; 
  long children[ORDER]; 
} B_TREE_NODE; 

typedef struct {
	char name[SIZE];
  keyType numUSP;
	char lastname[SIZE];
	char course[SIZE];
	float grade;
} STUDENT;

void printMenu();
void closeFile(FILE *);
int checkFile(FILE *);
int b_tree_setup(FILE *, FILE *);
int b_tree_insertRegistry(FILE *,FILE *);
int b_tree_searchRegistry(FILE *, FILE *);

#endif