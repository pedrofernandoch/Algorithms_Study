/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 3 - Índices 
  *Nome: Pedro Fernando Christofoletti dos Santos 
  *NUSP: 11218560
*/

#ifndef _FILE_
#define _FILE_

#define SIZE 30
#define SUCCESS 1
#define INVALID_INDEX -1
#define INVALID_FILE -2
#define INVALID_LIST -3;

typedef int keyType;

// #Primary Index

// List element
typedef struct{
  keyType numUSP;
  int byteoffset;
} PRIMARY_INDEX_ELEM;
// List descriptor
typedef struct{
  PRIMARY_INDEX_ELEM *first;
  int counter;
} PRIMARY_INDEX;

// #Secondary Index 

// Dynamic list element
struct dyn_list_simple_elem {
	keyType numUSP;
	struct dyn_list_simple_elem* next;
};
typedef struct dyn_list_simple_elem DYN_LIST_SIMPLE_ELEM;
// Dynamic list descriptor
typedef struct{
	DYN_LIST_SIMPLE_ELEM *first;
	int counter;
}DYN_LIST_SIMPLE;

// List element
typedef struct{
  char lastname[SIZE];
  DYN_LIST_SIMPLE *numUSP;
} SECONDARY_INDEX_ELEM;
// List descriptor
typedef struct{
  SECONDARY_INDEX_ELEM *first;
  int counter;
} SECONDARY_INDEX;

// Student
typedef struct {
	char name[SIZE];
  keyType numUSP;
	char lastname[SIZE];
	char course[SIZE];
	float grade;
} STUDENT;

//Functions
void printMenu();
void printRegistry(STUDENT);
void closeFile(FILE *);
int checkFile(FILE *);
int insertRegistry(FILE *, PRIMARY_INDEX *, SECONDARY_INDEX *);
int searchRegistryByNusp(FILE *, PRIMARY_INDEX *);
int searchRegistryByLN(FILE *, SECONDARY_INDEX *, PRIMARY_INDEX *);
int removeRegistryByNusp(FILE *, PRIMARY_INDEX *, SECONDARY_INDEX *);
int removeRegistryByLN(FILE *, SECONDARY_INDEX *, PRIMARY_INDEX *);
int rewritePrimaryIndexFile(PRIMARY_INDEX *, FILE *);
int rewriteSecondaryIndexFile(SECONDARY_INDEX *, FILE *, FILE *);
int freePrimaryIndex(PRIMARY_INDEX *);
int freeSecondaryIndex(SECONDARY_INDEX *);
PRIMARY_INDEX *createPrimaryIndex(FILE *);
SECONDARY_INDEX *createSecondaryIndex(FILE *, FILE *);

#endif