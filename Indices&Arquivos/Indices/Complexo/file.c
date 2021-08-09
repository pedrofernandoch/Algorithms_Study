/*  
  *SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 3 - Índices 
  *Nome: Pedro Fernando Christofoletti dos Santos 
  *NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file.h"

//Auxiliary function header
int __dyn_list_simple_add(DYN_LIST_SIMPLE *, int);
int __compare(int, int);
int __binarySearchSecondaryIndex(SECONDARY_INDEX *, char *, int, int);
int __binarySearchPrimaryIndex(PRIMARY_INDEX *, keyType, int, int);
char *__toupperCase(char *);
void __primaryInsertionSort(PRIMARY_INDEX *, int);
void __secondaryInsertionSort(SECONDARY_INDEX *, int);


//========================== MAIN FUNCTIOS ==========================\\

// #Print the menu
void printMenu(){
    printf("\n                    MENU\n\n");
    printf("==============================================");
    printf("\n\nType the option number of your choice\n\n");
    printf("1- Register\n");
    printf("2- Search by USP number\n");
    printf("3- Search by last name\n");
    printf("4- Remove by USP number\n");
    printf("5- Remove by last name\n");
    printf("==============================================");
    printf("\n\nType 0 to exit\n\n");
}

// #Print a registry
void __printRegistry(STUDENT student){
  printf("\nName: %s\n",student.name);
  printf("Last Name: %s\n",student.lastname);
  printf("NUSP: %d\n",student.numUSP);
  printf("Course: %s\n",student.course);
  printf("Grade: %.2f\n\n",student.grade);
}

// #Check if its a valid file
int checkFile(FILE *file){
  if(file == NULL){
    printf("ERROR, cannot open file");
    return 1;    
  }
  return 0;
}

// #Charge the primary index in RAM
PRIMARY_INDEX *createPrimaryIndex(FILE *index_file){
  fseek(index_file, 0, SEEK_END);
  int size = ftell(index_file);
  int i=0;
  if(size == 0){ //If there inst any registry
    PRIMARY_INDEX *index = (PRIMARY_INDEX *) calloc(1, sizeof(PRIMARY_INDEX));
    return index;
  }else{ //If there is at least one registry
    PRIMARY_INDEX *index = (PRIMARY_INDEX *) calloc(1, sizeof(PRIMARY_INDEX));
    index->first = (PRIMARY_INDEX_ELEM *) malloc(sizeof(PRIMARY_INDEX_ELEM)*((size+1)/(sizeof(int)*2)));
    fseek(index_file, 0, SEEK_SET);
    while(fread(&index->first[i], sizeof(PRIMARY_INDEX_ELEM), 1, index_file)){//Copying to RAM
      index->counter++;
      i++;
    }
    return index;
  }
  return NULL;
}

// #Charge the secondary index in RAM
SECONDARY_INDEX *createSecondaryIndex(FILE *index_file, FILE *list_file){
  fseek(index_file, 0, SEEK_END);
  int size = ftell(index_file);
  int i;
  if(size == 0){ //If there inst any registry
    SECONDARY_INDEX *index = (SECONDARY_INDEX *) calloc(1, sizeof(SECONDARY_INDEX));
    return index;
  }else{ //If there is at least one registry
    SECONDARY_INDEX *index = (SECONDARY_INDEX *) calloc(1, sizeof(SECONDARY_INDEX));
    int auxSize = (size+1)/(SIZE+sizeof(int));
    index->first = (SECONDARY_INDEX_ELEM *) malloc(sizeof(SECONDARY_INDEX_ELEM)*auxSize);
    for(int j=0;j<auxSize;j++){
      index->first[j].numUSP = (DYN_LIST_SIMPLE *) calloc(1,sizeof(DYN_LIST_SIMPLE));
    }
    fseek(index_file, 0, SEEK_SET);
    fseek(list_file,0,SEEK_SET);
    i=0;
    while(fread(&index->first[i].lastname, SIZE, 1, index_file)){//Copying to RAM
      index->counter++;
      fseek(index_file,4,SEEK_CUR);
      int nusp,nextByte;
      while(fread(&nusp, sizeof(int), 1, list_file)){
        fread(&nextByte, sizeof(int), 1, list_file);
        __dyn_list_simple_add(index->first[i].numUSP, nusp);
        if(nextByte==-1)break;
      }
      i++;
    }  
    return index;
  }
  return NULL;
}

// #Insert a student in data file, primary index and secondary index;
int insertRegistry(FILE *file, PRIMARY_INDEX *primary_index, SECONDARY_INDEX *secondary_index){

  if(!file) return INVALID_FILE;
  if(!primary_index)return INVALID_INDEX;
  if(!secondary_index)return INVALID_INDEX;

  primary_index->first = (PRIMARY_INDEX_ELEM *) realloc(primary_index->first,sizeof(PRIMARY_INDEX_ELEM)*(primary_index->counter+1));
  primary_index->counter++;

  STUDENT student;
  //Reading input
  printf("Name: ");scanf(" %[^\n]s",student.name);
  printf("Last Name: ");scanf(" %[^\n]s",student.lastname);
  printf("NUSP: ");scanf("%d",&student.numUSP);
  printf("Course: ");scanf(" %[^\n]s",student.course);
  printf("Grade: ");scanf("%f",&student.grade);

  //Adding to primary index
  fseek(file, 0, SEEK_END);
  primary_index->first[primary_index->counter-1].numUSP = student.numUSP;
  primary_index->first[primary_index->counter-1].byteoffset = ftell(file);
  fwrite(&student,sizeof(STUDENT),1,file);

  //Sorting primary index
  __primaryInsertionSort(primary_index, primary_index->counter);

  //Adding to secondary index
  char *aux = __toupperCase(student.lastname);
  int r = __binarySearchSecondaryIndex(secondary_index, aux, 0, secondary_index->counter);
  if(r==-1){
    secondary_index->first = (SECONDARY_INDEX_ELEM *) realloc(secondary_index->first,sizeof(SECONDARY_INDEX_ELEM)*(secondary_index->counter+1));
    secondary_index->counter++;
    strcpy(secondary_index->first[secondary_index->counter-1].lastname, aux);
    secondary_index->first[secondary_index->counter-1].numUSP = (DYN_LIST_SIMPLE *) calloc(1, sizeof(DYN_LIST_SIMPLE));
    __dyn_list_simple_add(secondary_index->first[secondary_index->counter-1].numUSP,student.numUSP);
  }else{
    __dyn_list_simple_add(secondary_index->first[r].numUSP,student.numUSP);
  }
  //Sorting secondary index
  __secondaryInsertionSort(secondary_index, secondary_index->counter);
  
  printf("\nSuccessful registration!\n\n");

  return SUCCESS;
}

//# Search a registry by USP number
int searchRegistryByNusp(FILE *file, PRIMARY_INDEX *index){

  if(!file) return INVALID_FILE;
  if(!index) return INVALID_INDEX;

  int byteoffset,pos;
  STUDENT student;
  keyType nusp;

  printf("NUSP: ");scanf("%d",&nusp);
  printf("Searching...\n");
 
  pos = __binarySearchPrimaryIndex(index, nusp, 0, index->counter);
  
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

// #Search a registry by last name
int searchRegistryByLN(FILE *file, SECONDARY_INDEX *secondary_index, PRIMARY_INDEX *primary_index){

  if(!file) return INVALID_FILE;
  if(!secondary_index) return INVALID_INDEX;

  char lastname[SIZE];
  int pos1,pos2,key,byteoffset,flag=0;
  STUDENT student;

  printf("Last name: ");scanf(" %[^\n]s",lastname);
  printf("Searching...\n");
  char *aux2 =  __toupperCase(lastname);

  for(int i=0;i<secondary_index->counter;i++){
    if (strstr(secondary_index->first[i].lastname,aux2)!=NULL){
      pos1=i;
      flag = 1;
      DYN_LIST_SIMPLE_ELEM *elem = secondary_index->first[pos1].numUSP->first;
      for(int j=0;j<secondary_index->first[pos1].numUSP->counter;j++){
        key = elem->numUSP;
        pos2 = __binarySearchPrimaryIndex(primary_index, key, 0, primary_index->counter);
        if(pos2 == -1)printf("\nINVALID NUSP or NOT FOUND\n\n");
        else{//Locating student in file    
          byteoffset = primary_index->first[pos2].byteoffset;
          fseek(file, byteoffset, SEEK_SET);
          fread(&student, sizeof(STUDENT), 1, file);
          char aux[2]="**";
          if(!strncmp(student.name, aux,1)){
            printf("\nINVALID NUSP or NOT FOUND\n\n");
          }else __printRegistry(student);
        }
        elem = elem->next;
      }
    }
  }
  free(aux2);
  if(flag==0)printf("\nINVALID LAST NAME or NOT FOUND\n\n");

  return SUCCESS;
}

// #Remove a registry from both indexes and data_file by USP number 
int removeRegistryByNusp(FILE *file, PRIMARY_INDEX *primary_index, SECONDARY_INDEX *secondary_index){
  if(!file) return INVALID_FILE;
  if(!primary_index) return INVALID_INDEX;
  if(!secondary_index) return INVALID_INDEX;

  char auxWord[SIZE], asterisco[SIZE];
  int pos1,pos2,key,byteoffset,nusp;
  STUDENT student;

  printf("NUSP: ");scanf("%d",&nusp);
  printf("Searching...\n");

  pos1 = __binarySearchPrimaryIndex(primary_index, nusp, 0, primary_index->counter);

  if(pos1==-1)printf("\nINVALID NUSP or NOT FOUND\n\n");
  else{
    //Removing from Primary index 
    byteoffset = primary_index->first[pos1].byteoffset;
    for(int i=pos1;i<primary_index->counter-1;i++) primary_index->first[i] = primary_index->first[i+1]; 
    primary_index->counter--;
    primary_index->first = (PRIMARY_INDEX_ELEM *) realloc(primary_index->first,sizeof(PRIMARY_INDEX_ELEM)*primary_index->counter);

    //Removing from Secondary index 
    fseek(file,byteoffset,SEEK_SET);
    fread(&student, sizeof(STUDENT),1,file);
    char *aux = __toupperCase(student.lastname);
    pos2 = __binarySearchSecondaryIndex(secondary_index, aux, 0,secondary_index->counter);
    free(aux);
    if(secondary_index->first[pos2].numUSP->counter==1){
      for(int i=pos2;i<secondary_index->counter-1;i++) secondary_index->first[i] = secondary_index->first[i+1]; 
      secondary_index->counter--;
      secondary_index->first = (SECONDARY_INDEX_ELEM *) realloc(secondary_index->first,sizeof(SECONDARY_INDEX_ELEM)*secondary_index->counter);
    }else{
      DYN_LIST_SIMPLE_ELEM *elem,*prev;
      elem = secondary_index->first[pos2].numUSP->first;
      prev=NULL;
      while(elem->numUSP!=nusp){
        prev = elem;
        elem = elem->next;
      }
      if(prev){
        prev->next = elem->next;
      } else secondary_index->first[pos2].numUSP->first = elem->next;
      free(elem);
      secondary_index->first[pos2].numUSP->counter--;
    }

    //Removing from file using marker "*"
    asterisco[0]='*';
    fclose(file);
    file = fopen("alunos.dad", "r+b");
    fseek(file, byteoffset, SEEK_SET);
    fread(&auxWord, sizeof(auxWord), 1, file);
    strcat(asterisco, auxWord);
    fseek(file, byteoffset, SEEK_SET);
    fwrite(&asterisco, sizeof(asterisco), 1, file);
    fclose(file);
    fopen("alunos.dad", "a+b");

    printf("\nRemoved!\n\n");
  }
  return SUCCESS;
}

//# Remove a registry from both index and data_file by last name 
int removeRegistryByLN(FILE *file, SECONDARY_INDEX *secondary_index, PRIMARY_INDEX *primary_index){
  if(!file) return INVALID_FILE;
  if(!primary_index) return INVALID_INDEX;
  if(!secondary_index) return INVALID_INDEX;

  char auxWord[SIZE], asterisco[SIZE], lastname[SIZE];
  int pos1,pos2,byteoffset;

  printf("Last name: ");scanf(" %[^\n]s",lastname);
  char *word = __toupperCase(lastname);
  pos1 = __binarySearchSecondaryIndex(secondary_index, word, 0, secondary_index->counter);
  free(word);

  if(pos1==-1)printf("\nINVALID LAST NAME or NOT FOUND\n\n");
  else{
    int aux[secondary_index->first[pos1].numUSP->counter],i;
    DYN_LIST_SIMPLE_ELEM *elem = secondary_index->first[pos1].numUSP->first;
    for(i=0;i<secondary_index->first[pos1].numUSP->counter;i++){
      aux[i] = elem->numUSP;
      elem = elem->next;
    }
    //Removing from Secondary index 
    for(int i=pos1;i<secondary_index->counter-1;i++) secondary_index->first[i] = secondary_index->first[i+1]; 
    secondary_index->counter--;
    secondary_index->first = (SECONDARY_INDEX_ELEM *) realloc(secondary_index->first,sizeof(SECONDARY_INDEX_ELEM)*secondary_index->counter);
    fclose(file);
    file = fopen("alunos.dad", "r+b");
    asterisco[0]='*';
    //Removing from Primary index
    for(int j=0;j<i;j++){
      pos2 = __binarySearchPrimaryIndex(primary_index, aux[j], 0, primary_index->counter);
      byteoffset = primary_index->first[pos2].byteoffset;
      for(int i=pos2;i<primary_index->counter-1;i++) primary_index->first[i] = primary_index->first[i+1];
      primary_index->counter--;
      primary_index->first = (PRIMARY_INDEX_ELEM *) realloc(primary_index->first,sizeof(PRIMARY_INDEX_ELEM)*primary_index->counter);
      //Removing from file using marker "*"
      fseek(file, byteoffset, SEEK_SET);
      fread(&auxWord, sizeof(auxWord), 1, file);
      strcat(asterisco, auxWord);
      fseek(file, byteoffset, SEEK_SET);
      fwrite(&asterisco, sizeof(asterisco), 1, file);
    }
    fclose(file);
    file = fopen("alunos.dad", "a+b");

    printf("\nRemoved!\n\n");
  }
  return SUCCESS;
}

// #Rewrite the primary index RAM -> FILE
int rewritePrimaryIndexFile(PRIMARY_INDEX *index, FILE *index_file){
  if(!index_file) return INVALID_FILE;
  if(!index) return INVALID_INDEX;

  fclose(index_file);

  index_file = fopen("primary_index_file","wb"); 
  fseek(index_file, 0, SEEK_SET);
  for(int i=0;i<index->counter;i++){//Copyng RAM's index to the index_file
    fwrite(&index->first[i], sizeof(PRIMARY_INDEX_ELEM), 1, index_file);
  }

  closeFile(index_file);

  return SUCCESS;
}

// #Rewrite the secondary index RAM -> FILE
int rewriteSecondaryIndexFile(SECONDARY_INDEX *index, FILE *index_file, FILE *list_file){
  if(!index_file) return INVALID_FILE;
  if(!list_file) return INVALID_FILE;
  if(!index) return INVALID_INDEX;

  fclose(index_file);
  fclose(list_file);

  index_file = fopen("secondary_index_file","wb");
  list_file = fopen("secondary_list_file","wb"); 

  for(int i=0;i<index->counter;i++){//Copyng RAM's index to the index_file
    int RRN = ftell(list_file);
    fwrite(&index->first[i].lastname, SIZE, 1, index_file);
    fwrite(&RRN, sizeof(int), 1, index_file);
    DYN_LIST_SIMPLE_ELEM *aux = index->first[i].numUSP->first;
    for(int j=0;j<index->first[i].numUSP->counter;j++){
      fwrite(&aux->numUSP, sizeof(int), 1, list_file);
      if(index->first[i].numUSP->counter == j+1){
        int RRN = -1;
        fwrite(&RRN, sizeof(int), 1, list_file);
      }else{
        int RRN = ftell(list_file)+4;
        fwrite(&RRN, sizeof(int), 1, list_file);
        aux = aux->next;
      }
    }
  }

  closeFile(index_file);
  closeFile(list_file);

  return SUCCESS;
}

// #Close a file
void closeFile(FILE *file){
  fclose(file);
}

// #Free the primary index 
int freePrimaryIndex(PRIMARY_INDEX *index){
  if(!index)return INVALID_INDEX;
  free(index->first);
  free(index);
  return SUCCESS;
}

// #Free the secondary index 
int freeSecondaryIndex(SECONDARY_INDEX *index){
  if(!index)return INVALID_INDEX;
  DYN_LIST_SIMPLE_ELEM *p, *auxDyn;
  for(int i=0;i<index->counter;i++)free(index->first[i].numUSP);
  free(index->first);
  free(index);
  return SUCCESS;
}

//========================== AUXILIARY FUNCTIOS ==========================\\

// Add element to the dynamic simple list
int __dyn_list_simple_add(DYN_LIST_SIMPLE *list, int numUSP) {

	if (!list) return INVALID_LIST;

	DYN_LIST_SIMPLE_ELEM **p;
	DYN_LIST_SIMPLE_ELEM *new = (DYN_LIST_SIMPLE_ELEM *) malloc(sizeof(DYN_LIST_SIMPLE_ELEM));

	new->numUSP = numUSP;
	p = &list->first;

  if(!(*p)){
    list->first = new;
  }else{
    while((*p)->numUSP < new->numUSP && (*p)->next){
      p = &(*p)->next;
    }
    new->next = *p;
	  *p = new;
  }
	list->counter++;
	return SUCCESS;
}

// Compare two integers
int __compare(int a, int b){
  if (a==b) return 0;
  else if (a<b) return -1;
  else return 1;
}

// Search respective key's position in secondary index
int __binarySearchSecondaryIndex(SECONDARY_INDEX *index, char *key, int start, int end){
	int middle, r; 
	if (start > end || !index->first)return -1;
	middle = (start + end) / 2;
	r = strcmp(key,index->first[middle].lastname);
	if (r == 0)return middle; 
	else if (r < 0)return __binarySearchSecondaryIndex(index, key, start, middle-1); 
	else return __binarySearchSecondaryIndex(index, key, middle+1, end); 
}

// Search respective key's position in primary index
int __binarySearchPrimaryIndex(PRIMARY_INDEX *index, keyType key, int start, int end){
	int middle, r; 
	if (start > end)return -1;
	middle = (start + end) / 2; 
	r = __compare(key, index->first[middle].numUSP);
	if (r == 0)return middle; 
	else if (r < 0)return __binarySearchPrimaryIndex(index, key, start, middle-1); 
	else return __binarySearchPrimaryIndex(index, key, middle+1, end); 
}

// Change all charecteres into uppercase
char *__toupperCase(char *str){
  char *strResult = (char *) malloc(sizeof(char));
  for(int i=0;i<strlen(str);i++){
    strResult[i] = toupper((str[i])); 
  }
  strResult[strlen(str)] = '\0';
  return strResult;
}

/* Insertion Sort the primary index
I used insertionSort because its great for almost sorted arrays*/
void __primaryInsertionSort(PRIMARY_INDEX *index, int counter){
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

/* Insertion Sort the secondary index
I used insertionSort because its great for almost sorted arrays*/
void __secondaryInsertionSort(SECONDARY_INDEX *index, int counter){
  int i, j;  
  DYN_LIST_SIMPLE *numUSP;
  char *aux1,*aux2,key[SIZE];
  for (i = 1; i < counter; i++){
    strcpy(key,index->first[i].lastname);   
    numUSP = index->first[i].numUSP;  
    j = i - 1;  
    while (j >= 0 && (strcmp(index->first[j].lastname,key)>=1)){
      strcpy(index->first[j + 1].lastname,index->first[j].lastname);  
      index->first[j + 1].numUSP = index->first[j].numUSP;  
      j = j - 1;
    }  
    strcpy(index->first[j + 1].lastname,key);
    index->first[j + 1].numUSP = numUSP;
  }  
}