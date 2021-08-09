/*  SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 1 - arquivos 
Nome: Pedro Fernando Christofoletti dos Santos 
NUSP: 11218560
*/

#ifndef _FILE_
#define _FILE_

#define SIZE 16

typedef int keyType;

typedef struct {
	keyType numUSP;
	char name[SIZE];
	char lastname[SIZE];
	char course[2*SIZE];
	float grade;
} STUDENT;

//Functions
int checkFile(FILE *);
void printMenu();
void insertRegistry(FILE *);
void searchRegistry(FILE *);
void printRegistry(STUDENT);
void closeFile(FILE *);

#endif