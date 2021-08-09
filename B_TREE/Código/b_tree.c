/*  SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho I - Árvore B 
Integrantes:
Nome: Guilherme Filipe Feitosa dos Santos           NUSP: 11275092
Nome: Pedro Fernando Christofoletti dos Santos      NUSP: 11218560
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "b_tree.h"

//Auxiliary function header 
int __checkfilesize(FILE *,FILE *);
void __printRegistry(STUDENT);
int __compare(int, int);
char * __generateName(int);
char * __generateCourse(int);
float __generateGrade(int);
void __b_tree_create(FILE *);
int __b_tree_search(FILE*, long, int);
int __b_tree_empty_node_beginning_in_pos(B_TREE_NODE*, int);
int __b_tree_insert(FILE*, KEY, long, KEY**, short);


//========================== MAIN FUNCTIOS ==========================\\

void printMenu(){
    printf("\n                    MENU\n\n");
    printf("==============================================");
    printf("\n\nType the option number of your choice\n\n");
    printf("1- Create data file and B Tree\n");
    printf("2- Register\n");
    printf("3- Search\n");
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

// Create and fill data_file and b_tree_index with random registries
int b_tree_setup(FILE *file, FILE *b_tree_index){
  
  // Check possible errors/problems
  if(!file) return INVALID_FILE;
  if(!b_tree_index) return INVALID_B_TREE_INDEX;
  if(!__checkfilesize(file,b_tree_index)){
    printf("You have alredy set up the environment!\n");
    return SUCCESS;
  }

  STUDENT student;
  long root_RRN;
  int i = 0, total;
  KEY key;

  //Guarantee at least 2 tree levels
  total = (ORDER / 2) * ORDER + 1;
  printf("Wait while the %d examples are loaded...\n\n", total);
  
  fclose(b_tree_index);
  b_tree_index = fopen("index.dat","rb+");

  // Initialize tree
  __b_tree_create(b_tree_index);
  
  while(i < total){
    //Generating random registry
    strcpy(student.name, __generateName(i));
    strcpy(student.lastname, __generateName(i+1));
    strcpy(student.course, __generateCourse(i));
    student.grade = __generateGrade(i);
    student.numUSP = i;

    //Inserting in file
    fseek(file, 0, SEEK_END);
    fwrite(&student,sizeof(STUDENT),1,file);
    
    //Inserting in B_tree
    key.NUSP = i;
    key.RRN = i;
    fseek(b_tree_index, 0, SEEK_SET);
    fread(&root_RRN, sizeof(long), 1, b_tree_index);
    __b_tree_insert(b_tree_index, key, root_RRN, NULL, 0);

    i++;
  }

  printf("Build Successful!\n\n");
  
  return SUCCESS;
  
}

// Insert a student in data file and b_tree_index;
int b_tree_insertRegistry(FILE *file, FILE *b_tree_index){

  if(!file) return INVALID_FILE;
  if(!b_tree_index) return INVALID_B_TREE_INDEX;
  if(__checkfilesize(file,b_tree_index)){
    printf("Please create file and B Tree before register or search\n");
    return EMPTY_FILE;
  } 

  STUDENT student;

  //Reading input
  printf("Name: ");scanf(" %[^\n]s",student.name);
  printf("Last Name: ");scanf(" %[^\n]s",student.lastname);
  printf("NUSP: ");scanf("%d",&student.numUSP);
  printf("Course: ");scanf(" %[^\n]s",student.course);
  printf("Grade: ");scanf("%f",&student.grade);

  KEY key;
  key.NUSP = student.numUSP;
  fseek(file, 0, SEEK_END);
  key.RRN = ftell(file) / sizeof(STUDENT);
  
  //Inserting in file
  fwrite(&student, sizeof(STUDENT), 1, file);
  
  long root_RRN;
  fseek(b_tree_index, 0, SEEK_SET);
  fread(&root_RRN, sizeof(long), 1, b_tree_index);

  //Inserting in B_tree
  __b_tree_insert(b_tree_index, key, root_RRN, NULL, 0);

  printf("\nSuccessful registration!\n\n");

  return SUCCESS;
}

// Search a registry by USP number
int b_tree_searchRegistry(FILE *file, FILE *b_tree_index){

  if(!file) return INVALID_FILE;
  if(!b_tree_index) return INVALID_B_TREE_INDEX;
  if(__checkfilesize(file,b_tree_index)){
    printf("Please create file and B Tree before register or search\n");
    return EMPTY_FILE;
  } 

  long root_RRN, byteoffset, RRN;
  STUDENT student;
  keyType nusp;

  printf("NUSP: ");scanf("%d",&nusp);
  printf("Searching...\n");

  fseek(b_tree_index, 0, SEEK_SET);
  fread(&root_RRN, sizeof(long), 1, b_tree_index);

  //Searching RRN
  RRN = __b_tree_search(b_tree_index, root_RRN, nusp);

  if(RRN == RRN_NOT_FOUND){
    printf("NUSP not found\n\n");
  } else {
    byteoffset = RRN * sizeof(STUDENT);
    fseek(file, byteoffset, SEEK_SET);
    fread(&student, sizeof(student), 1, file);
    __printRegistry(student);
  }

  return SUCCESS;
}

void closeFile(FILE *file){
  fclose(file);
}


//========================== AUXILIARY FUNCTIOS ==========================\\

// Check if b_tree and data file are filled with data
int __checkfilesize(FILE *file, FILE *b_tree_index){
  fseek(file, 0, SEEK_END);
  fseek(b_tree_index, 0, SEEK_END);
  if(ftell(file) == 0 && ftell(b_tree_index) == 0) return 1;
  else return 0;
}

// Initialize tree
void __b_tree_create(FILE *b_tree_index){
  printf("Inicializando b_tree...\n\n");

  long RRN = 0;
  B_TREE_NODE *root;

  // Inicializando e no raiz totalmente vazio
  root = (B_TREE_NODE *) calloc(1, sizeof(B_TREE_NODE));
  __b_tree_empty_node_beginning_in_pos(root, 0);

  // Inserindo informacoes iniciais no arquivo
  fseek(b_tree_index, 0, SEEK_SET);
  fwrite(&RRN, sizeof(long), 1, b_tree_index);
  fwrite(root, sizeof(B_TREE_NODE), 1, b_tree_index);
}

void __printRegistry(STUDENT student){
  printf("\nName: %s\n",student.name);
  printf("Last Name: %s\n",student.lastname);
  printf("NUSP: %d\n",student.numUSP);
  printf("Course: %s\n",student.course);
  printf("Grade: %.2f\n\n",student.grade);
}

int __compare(int a, int b){
  if (a==b) return 0;
  else if (a<b) return -1;
  else return 1;
}

char * __generateName(int i){
  srand(time(NULL)+i);
  char consonants[21] = "bcdfghjklmnpqrstvwxyz";
  char vowels[5] = "aeiou";
  char *str = (char*) malloc(SIZE*sizeof(char));
  int pos=0;
  int syllables = (rand() % 3) + 2;
  for (int i=0;i<syllables;i++){
    str[pos] = consonants[(rand() % 21)];
    str[pos+1] = vowels[(rand() % 5)];
    pos+=2;
  }
  str[0] = toupper(str[0]);
  return str;
}

char * __generateCourse(int i){
  char courses[7][100] = {"Bacharelado em Matematica","Licenciatura em Matematica","Bacharelado em Matematica Aplicada e Computacao Cientifica","Bacharelado em Ciencias de Computacao","Bacharelado em Sistemas de Informacao","Bacharelado em Estatistica e Ciencia da Dados","Engenharia de Computacao"};
  srand(time(NULL)+i);
  int pos = rand() % 7;
  char *str = (char*) malloc(SIZE*sizeof(char));
  strcpy(str,courses[pos]);
  return str;
}

float __generateGrade(int i){
  srand(time(NULL)+i);
  float grade = rand() % 11;
  return grade;
}

// Searching NUSP in the tree and returning its respective RRN
int __b_tree_search(FILE *b_tree_index, long RRN, int key){
  
  if (RRN == -1) return RRN_NOT_FOUND;
  else{
    int i = 0;
    B_TREE_NODE *node = (B_TREE_NODE *) malloc(sizeof(B_TREE_NODE));
    fseek(b_tree_index, ((sizeof(B_TREE_NODE) * RRN) + sizeof(long)), SEEK_SET);
    fread(node, sizeof(B_TREE_NODE), 1, b_tree_index);
    
    while(i<node->counter){
      int cmp = __compare(node->keys[i].NUSP, key);
      if(!cmp){
        return node->keys[i].RRN;
      } else if(cmp<0){ // key > node->keys->nusp
        i++;
      } else { // key < node->keys->nusp
        RRN = node->children[i];
        return __b_tree_search(b_tree_index, RRN, key);
      }
    }
    RRN = node->children[i];
    return __b_tree_search(b_tree_index, RRN, key);
  }
}

// Insert -1 in positions ahead pos
int __b_tree_empty_node_beginning_in_pos(B_TREE_NODE *node, int pos){
  if(!node) return INVALID_NODE;
  for(int i = pos; i < ORDER - 1; i++){
    node->keys[i].NUSP = -1;
    node->keys[i].RRN = -1;
    node->children[i+1] = -1;
  }
  if(pos == 0) node->children[0] = -1;
  return SUCCESS;
}

// Insert key in node
int __b_tree_put_key_in_node(FILE *b_tree_index, B_TREE_NODE *node,
        long node_RRN, KEY *key, long RRN, int pos, KEY **over_key){
  long over_RRN = 0;
  if(node->counter == 0){ // Empty node
    node->keys[0].NUSP = key->NUSP;
    node->keys[0].RRN = key->RRN;
    node->children[0] = -1;
    node->counter = 1;

    // Set unused spaces with -1
    __b_tree_empty_node_beginning_in_pos(node, 1);

    *over_key = NULL; // None key needs to be replaced
  } else if(node->counter < (ORDER - 1)){ // Node with space
    // Insere em pos
    memcpy(&node->keys[pos+1], &node->keys[pos], (node->counter - pos) * sizeof(KEY));
    memcpy(&node->children[pos+2], &node->children[pos+1], (node->counter - pos) * sizeof(long));
    node->keys[pos].NUSP = key->NUSP;
    node->keys[pos].RRN = key->RRN;
    node->children[pos+1] = RRN;
    node->counter++;

    *over_key = NULL; // None key needs to be replaced
  } else { // Full node
    // Split
    int new_size = (ORDER - 1) / 2, i = 0, cmp;
    B_TREE_NODE *new_children, *to_insert;

    // Separete nodes
    new_children = (B_TREE_NODE *) calloc(1, sizeof(B_TREE_NODE));
    memmove(new_children->keys, &node->keys[ORDER - 1 - new_size], new_size * sizeof(KEY));
    memmove(new_children->children, &node->children[ORDER - 1 - new_size], (new_size + 1) * sizeof(long));
    node->children[ORDER - 1 - new_size] = -1;
    
    // Set unused spaces with -1
    __b_tree_empty_node_beginning_in_pos(node, ORDER - 1 - new_size);
    __b_tree_empty_node_beginning_in_pos(new_children, new_size);

    // Reajust sizes
    new_children->counter = new_size;
    node->counter -= new_size;

    // Verify where to promote
    if(pos < node->counter) to_insert = node;
    else {
      pos -= node->counter;
      to_insert = new_children;
    }

    // Insert in the right place to discover who needs to be promoted
    memcpy(&to_insert->keys[pos+1], &to_insert->keys[pos],
      (to_insert->counter - pos) * sizeof(KEY));
    memcpy(&to_insert->children[pos+2], &to_insert->children[pos+1],
      (to_insert->counter - pos) * sizeof(long));
    to_insert->keys[pos].NUSP = key->NUSP;
    to_insert->keys[pos].RRN = key->RRN;
    to_insert->children[pos+1] = RRN;
    to_insert->counter++;

    // Define the promotion and reajust node counter
    *over_key = (KEY*) calloc(1, sizeof(KEY)); // A key needs to be replaced
    fseek(b_tree_index, 0, SEEK_END);
    over_RRN = (ftell(b_tree_index) - sizeof(long)) / sizeof(B_TREE_NODE);
    if(to_insert == node){
      memmove(*over_key, &node->keys[node->counter - 1], sizeof(KEY));
      node->keys[node->counter - 1].NUSP = -1;
      node->keys[node->counter - 1].RRN = -1;
      node->children[node->counter] = -1;
    }else{
      memmove(*over_key, &new_children->keys[0], sizeof(KEY));
      memmove(&new_children->keys[0], &new_children->keys[1],  (new_children->counter - 1) * sizeof(KEY));
      memmove(&new_children->children[0], &new_children->children[1],  (new_children->counter) * sizeof(KEY));
    }
    to_insert->counter--;
    to_insert->keys[to_insert->counter].NUSP = -1;
    to_insert->keys[to_insert->counter].RRN = -1;
    to_insert->children[to_insert->counter + 1] = -1;

    // Update b_tree_index
    fwrite(new_children, sizeof(B_TREE_NODE), 1, b_tree_index);
  }
  fseek(b_tree_index, ((sizeof(B_TREE_NODE) * node_RRN) + sizeof(long)), SEEK_SET);
  fwrite(node, sizeof(B_TREE_NODE), 1, b_tree_index);
  return over_RRN;
}

int __b_tree_new_root_node(FILE *b_tree_index, long left_RRN, long right_RRN, KEY *over_key){
  B_TREE_NODE *new_root;
  long root_RRN;
  
  // Create new root
  new_root = (B_TREE_NODE *) calloc(1, sizeof(B_TREE_NODE));
  
  // Fill new root
  new_root->keys[0].NUSP = over_key->NUSP;
  new_root->keys[0].RRN = over_key->RRN;
  new_root->children[0] = left_RRN;
  new_root->children[1] = right_RRN;
  new_root->counter = 1;
  __b_tree_empty_node_beginning_in_pos(new_root, 1);

  // Insert new root node
  fseek(b_tree_index, 0, SEEK_END);
  root_RRN = (ftell(b_tree_index) - sizeof(long)) / sizeof(B_TREE_NODE);
  fwrite(new_root, sizeof(B_TREE_NODE), 1, b_tree_index);

  // Update root's RRN in file
  fseek(b_tree_index, 0, SEEK_SET);
  fwrite(&root_RRN, sizeof(long), 1, b_tree_index);

  return SUCCESS;
}

void __b_tree_free_over_key(KEY **over_key){
  free(over_key);
  free(*over_key);
}

int __b_tree_insert(FILE *b_tree_index, KEY key, long node_RRN, KEY **over_key, short level){
  if(over_key == NULL) { // Initialize over_key
    over_key = (KEY **) malloc(sizeof(KEY*));
    *over_key = (KEY *) malloc(sizeof(KEY));
  }
  
  int i = 0;
  long offset = ((sizeof(B_TREE_NODE) * node_RRN) + sizeof(long));
  B_TREE_NODE *node = (B_TREE_NODE *) calloc(1, sizeof(B_TREE_NODE));
  fseek(b_tree_index, offset, SEEK_SET);
  fread(node, sizeof(B_TREE_NODE), 1, b_tree_index);

  while(i<node->counter){
    int cmp = __compare(node->keys[i].NUSP, key.NUSP);
    if(cmp==0) return RRN_EXISTENT;
    else if(cmp<0) i++; // key > node->keys->nusp
    else if(cmp>0) break; // key < node->keys->nusp
  }

  long over_RRN = -1;
  if(node->counter == 0 || node->children[i] == -1){ // Leaf node
    over_RRN = __b_tree_put_key_in_node(b_tree_index, node, node_RRN, &key, -1, i, over_key);
    if(over_RRN){ // Done split and promote key
      if(level == 0){ // Root node
        __b_tree_new_root_node(b_tree_index, node_RRN, over_RRN, *over_key);
        if(level == 0) __b_tree_free_over_key(over_key);
        return 0;
      }
      if(level == 0) __b_tree_free_over_key(over_key);
      return over_RRN;
    }
    if(level == 0) __b_tree_free_over_key(over_key);
    return 0;
  } else { // Branch node
    over_RRN = __b_tree_insert(b_tree_index, key, node->children[i], over_key, level+1);
    if(over_RRN){ // Verify split in next node
      memcpy(&key, *over_key, sizeof(KEY));
      over_RRN = __b_tree_put_key_in_node(b_tree_index, node, node_RRN, &key, over_RRN, i, over_key);
      if(over_RRN && level == 0){ // Root node
        __b_tree_new_root_node(b_tree_index, node_RRN, over_RRN, *over_key);
        if(level == 0) __b_tree_free_over_key(over_key);
        return 0;
      }
      if(level == 0) __b_tree_free_over_key(over_key);
      return over_RRN;
    }
    if(level == 0) __b_tree_free_over_key(over_key);
    return 0;
  }
}