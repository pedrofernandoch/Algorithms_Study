/*  SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 2 - Índices
Nome: Pedro Fernando Christofoletti dos Santos 
NUSP: 11218560
*/

#ifndef _FILE_
#define _FILE_

#define SIZE 16
#define SUCCESS 1
#define INVALID_INDEX -1
#define INVALID_FILE -2

typedef int keyType;

typedef struct{
  keyType numUSP;
  int byteoffset;
} INDEX_ELEM;

typedef struct{
  INDEX_ELEM *first;
  int counter;
} INDEX;

typedef struct {
	char name[SIZE];
  keyType numUSP;
	char lastname[SIZE];
	char course[SIZE];
	float grade;
} STUDENT;

//Functions
int checkFile(FILE *);
INDEX *createIndex(FILE *);
void printMenu();
int insertRegistry(FILE *, INDEX *);
int searchRegistry(FILE *, INDEX *);
int removeRegistry(FILE *, INDEX *);
int rewriteIndexFile(INDEX *, FILE *);
void printRegistry(STUDENT);
void closeFile(FILE *);

#endif