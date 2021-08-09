/*  SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 2 - Índices
Nome: Pedro Fernando Christofoletti dos Santos 
NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

//# MENU
void printMenu(){
    printf("\n                    MENU\n\n");
    printf("==============================================");
    printf("\n\nType the option number of your choice\n\n");
    printf("1- Register\n");
    printf("2- Search\n");
    printf("3- Remove\n");
    printf("==============================================");
    printf("\n\nType 0 to exit\n\n");
}

int checkFile(FILE *file){
  if(file == NULL){
    printf("ERROR, cannot open file");
    return 1;    
  }
  return 0;
}

// #Create Index in RAM
INDEX *createIndex(FILE *index_file){
  fseek(index_file, 0, SEEK_END);
  int size = ftell(index_file);
  int i=0;
  if(size == 0){ //If there inst any registry
    INDEX *index = (INDEX *) calloc(1, sizeof(INDEX));
    return index;
  }else{ //If there is at least one registry
    INDEX *index = (INDEX *) calloc(1, sizeof(INDEX));
    index->first = (INDEX_ELEM *) malloc(sizeof(INDEX_ELEM)*index->counter+1);
    fseek(index_file, 0, SEEK_SET);
    while(fread(&index->first[i], sizeof(INDEX_ELEM), 1, index_file)){//Copying to RAM
      index->first = (INDEX_ELEM *) realloc(index->first,sizeof(INDEX_ELEM)*(index->counter+1));
      index->counter++;
      i++;
    }
    return index;
  }
  return NULL;
}

/*# Insertion Sort
I used insertionSort because its great for almost sorted arrays*/
void __insertionSort(INDEX *index, int counter){
  int i, j, byteoffset;  
  keyType key;
  for (i = 1; i < counter; i++){  
    key = index->first[i].numUSP;  
    byteoffset = index->first[i].byteoffset;  
    j = i - 1;  
    while (j >= 0 && index->first[j].numUSP > key){  
      index->first[j + 1].numUSP = index->first[j].numUSP;
      index->first[j + 1].byteoffset = index->first[j].byteoffset;  
      j = j - 1;  
    }  
    index->first[j + 1].numUSP = key;
    index->first[j + 1].byteoffset = byteoffset;  
  }  
}

//# Insert student
int insertRegistry(FILE *file, INDEX *index){

  if(!file) return INVALID_FILE;
  if(!index)return INVALID_INDEX;

  index->first = (INDEX_ELEM *) realloc(index->first,sizeof(INDEX_ELEM)*index->counter+1);
  index->counter++;

  STUDENT student;
  //Reading input
  printf("Name: ");scanf("%s",student.name);
  printf("Last Name: ");scanf("%s",student.lastname);
  printf("NUSP: ");scanf("%d",&student.numUSP);
  printf("Course: ");scanf("%s",student.course);
  printf("Grade: ");scanf("%f",&student.grade);

  //Adding to index
  fseek(file, 0, SEEK_END);
  index->first[index->counter-1].numUSP = student.numUSP;
  index->first[index->counter-1].byteoffset = ftell(file);
  fwrite(&student,sizeof(STUDENT),1,file);

  //Sorting index
  __insertionSort(index, index->counter);
  
  printf("\nSuccessful registration!\n\n");

  return SUCCESS;

}

//# Print Registry
void __printRegistry(STUDENT student){
  printf("\nName: %s\n",student.name);
  printf("Last Name: %s\n",student.lastname);
  printf("NUSP: %d\n",student.numUSP);
  printf("Course: %s\n",student.course);
  printf("Grade: %.2f\n\n",student.grade);
}

// #Compare
int __compare(keyType a, keyType b){
  if (a == b)return 0;
	else if (a < b)return -1;
	else return 1;
}

// Search Index
int __searchIndex(INDEX *index, keyType key, int start, int end){
  //Binary search
	int middle, r; 
	if (start > end)return -1;
	middle = (start + end) / 2; 
	r = __compare(key, index->first[middle].numUSP);
	if (r == 0)return middle; 
	else if (r < 0)return __searchIndex(index, key, start, middle-1); 
	else return __searchIndex(index, key, middle+1, end); 
}

// Search Position
int __searchPosition(INDEX *index){
  int pos;
  keyType nusp;
  //Reading input
  printf("NUSP: ");scanf("%d",&nusp);
  printf("Searching...\n");
  //Searching key in index and getting its position
  pos = __searchIndex(index, nusp, 0, index->counter);
  return pos;
}

// #Search Registry
int searchRegistry(FILE *file, INDEX *index){

  if(!file) return INVALID_FILE;
  if(!index) return INVALID_INDEX;

  int byteoffset,pos;
  keyType nusp;
  STUDENT student;

  //Getting respective position
  pos = __searchPosition(index);
  
  if(pos == -1)printf("\nINVALID NUSP or NOT FOUND\n\n");
  else{//Locating student in file    
    byteoffset = index->first[pos].byteoffset;
    fseek(file, byteoffset, SEEK_SET);
    fread(&student, sizeof(STUDENT), 1, file);
    char aux[2]="**";
    if(!strncmp(student.name, aux,1)){
      printf("\nINVALID NUSP or NOT FOUND\n\n");
    }else __printRegistry(student);
  }

  return SUCCESS;
}

//Remove Registry from index and data_file
int removeRegistry(FILE *file, INDEX *index){
  if(!file) return INVALID_FILE;
  if(!index) return INVALID_INDEX;

  int pos = __searchPosition(index);
  int byteoffset = index->first[pos].byteoffset;
  char aux[SIZE], asterisco[SIZE];
  asterisco[0]='*';

  //Removing from index 
  for(int i=pos;i<index->counter-1;i++) index->first[i] = index->first[i+1]; 
  index->counter--;
  index->first = (INDEX_ELEM *) realloc(index->first,sizeof(INDEX_ELEM)*index->counter);
  
  fclose(file);
  file = fopen("alunos.dad", "r+b");
  //Removing from file using marker "*"
  fseek(file, byteoffset, SEEK_SET);
  fread(&aux, sizeof(aux), 1, file);
  strcat(asterisco, aux);
  fseek(file, byteoffset, SEEK_SET);
  fwrite(&asterisco, sizeof(asterisco), 1, file);

  fclose(file);
  fopen("alunos.dad", "a+b");

  printf("\nRemoved!\n\n");

  return SUCCESS;

}
//# Rewrite the index
int rewriteIndexFile(INDEX *index, FILE *index_file){
  if(!index_file) return INVALID_FILE;
  if(!index) return INVALID_INDEX;

  fclose(index_file);

  index_file = fopen("index_file","wb"); 
  fseek(index_file, 0, SEEK_SET);
  for(int i=0;i<index->counter;i++){//Copyng RAM's index to the index_file
    fwrite(&index->first[i], sizeof(INDEX_ELEM), 1, index_file);
  }
  closeFile(index_file);

  return SUCCESS;
}

//# Close File
void closeFile(FILE *file){
  fclose(file);
}