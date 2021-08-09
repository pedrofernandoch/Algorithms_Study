/*  SCC0503 - Algoritmos e Estruturas de Dados II - Pratica 1 - fileuivos 
Nome: Pedro Fernando Christofoletti dos Santos 
NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "file.h"

int checkFile(FILE *file){
  if(file == NULL){
    printf("ERROR, cannot open file");
    return 1;    
  }
  return 0;
}

//#MENU
void printMenu(){
    printf("\n                    MENU\n\n");
    printf("==============================================");
    printf("\n\nType the option number of your choice\n\n");
    printf("1- Register\n");
    printf("2- Search\n");
    printf("==============================================");
    printf("\n\nType 0 to exit\n\n");
}

//#Insert student
void insertRegistry(FILE *file){
  //int size;
  char buffer[100],size;
  STUDENT student;
  //Reading input
  printf("Name: ");scanf("%s",student.name);
  printf("Last Name: ");scanf("%s",student.lastname);
  printf("NUSP: ");scanf("%d",&student.numUSP);
  printf("Course: ");scanf("%s",student.course);
  printf("Grade: ");scanf("%f",&student.grade);
  
  //Inserting in file
  sprintf(buffer, "%d|%s|%s|%s|%f|", student.numUSP, student.name,student.lastname,student.course,student.grade);
  size = strlen(buffer);
  fwrite(&size, sizeof(size), 1, file);
  fwrite(buffer, size, 1, file);

  printf("\nSuccessful registration!\n\n");

}

//#Print Registry
void printRegistry(STUDENT student){
  printf("\nName: %s\n",student.name);
  printf("Last Name: %s\n",student.lastname);
  printf("NUSP: %d\n",student.numUSP);
  printf("Course: %s\n",student.course);
  printf("Grade: %.2f\n\n",student.grade);
}

char *parser(char *buffer, int *pos) {
    int posi = *pos;
    while(buffer[*pos]!='|')(*pos)++;
    buffer[*pos] = '\0';
    (*pos)++;
    return &buffer[posi];
}

//#Search registry
void searchRegistry(FILE *file){
  int flag=0,pos, nusp;
  char buffer[100], size;
  STUDENT student;

  //Reading input
  printf("NUSP: ");scanf("%d",&nusp);
  fseek(file,0,SEEK_SET);

  //Searching student in file
  printf("\nSearching...\n");
  while(fread(&size, sizeof(size), 1, file)){
    fread(buffer, size, 1, file);
    pos = 0;
    sscanf(parser(buffer, &pos), "%d", &student.numUSP);
    if (nusp == student.numUSP){
      strcpy(student.name, parser(buffer, &pos));
      strcpy(student.lastname, parser(buffer, &pos));
      strcpy(student.course, parser(buffer, &pos));
      sscanf(parser(buffer, &pos), "%f", &student.grade);
      printRegistry(student);
      flag=1;
      break;
    }
  }

  if(!flag)printf("INVALID NUSP or NOT FOUND\n\n");
}

//#Close File
void closeFile(FILE *file){
  fclose(file);
}