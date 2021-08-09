#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"
#define BUFFER_SIZE 1024

//CREATE TREE
avltree *avltree_create(avltree_cmpfn compare){
  avltree *tree = malloc(sizeof(avltree));
  if (tree != NULL){
    tree->root = NULL;
    tree->compare = compare;
    tree->count = 0;
  }
  return tree;
}

//COMPARE
int compareCPF(PESSOA *pessoa1, PESSOA *pessoa2) {
    if (pessoa1->cpf == pessoa2->cpf) return 0;
    else if (pessoa1->cpf > pessoa2->cpf) return 1;
    else return -1;
}
int compareNome(PESSOA *pessoa1, PESSOA *pessoa2) {
  if (strcmp(pessoa1->nome, pessoa2->nome) == 0) return 0;
  else if (strcmp(pessoa1->nome, pessoa2->nome) > 0) return 1;
  else return -1;
}
int compareDate(PESSOA *pessoa1, PESSOA *pessoa2) { 
  if (pessoa1->nascimento->year > pessoa2->nascimento->year) return 1;
  else if (pessoa1->nascimento->year < pessoa2->nascimento->year) return -1;
  else {
    if (pessoa1->nascimento->month > pessoa2->nascimento->month) return 1;
    else if (pessoa1->nascimento->month < pessoa2->nascimento->month) return -1; 
    else {
      if (pessoa1->nascimento->day > pessoa2->nascimento->day) return 1;
      else if (pessoa1->nascimento->day < pessoa2->nascimento->day) return -1; 
      else return 0;
      }
  }
    
}

//CREATE PESSOA
PESSOA *createPessoa (unsigned long long cpf, unsigned long long rg, char *nome, char *nascimento, char *cidade) {
    PESSOA *new = (PESSOA *) malloc (sizeof(PESSOA));
    new->cpf=cpf;
    new->rg=rg;
    new->nome = (char *) malloc (sizeof(char) * 40);
    new->nome = nome;
    new->cidade= (char *) malloc(sizeof(char) * 40);
    strcpy(new->cidade, cidade);
    DATE *nascimentoDate = (DATE *) malloc (sizeof(DATE));
    char *tok = strtok(nascimento, "/");
    nascimentoDate->day= atof(tok);
    tok = strtok(NULL, "/");
    nascimentoDate->month=atof(tok);
    tok = strtok(NULL, "/");
    nascimentoDate->year=atof(tok);
    new->nascimento=nascimentoDate;
    
    return new;
}

static void avltreenode_delete(avltreenode *node){
  free(node);
}

static void avltree_empty_recursive(avltreenode *root){
  if (root->left)avltree_empty_recursive(root->left);
  if (root->right)avltree_empty_recursive(root->right);
  avltreenode_delete(root);
}

void avltree_empty(avltree *tree){
  if (tree->root){
    avltree_empty_recursive(tree->root);
    tree->root = NULL;
    tree->count = 0;
  }
}

void avltree_delete(avltree *tree){
  if (tree){
    avltree_empty(tree);
    free(tree);
  }
}

static void avltree_for_each_recursive(const avltreenode *root, avltree_forfn fun){
  if (root->left != NULL)avltree_for_each_recursive(root->left, fun);
  fun(root->pessoa);
  if (root->right != NULL)avltree_for_each_recursive(root->right, fun);
}

void avltree_for_each(const avltree *tree, avltree_forfn fun){
  if (tree->root)avltree_for_each_recursive(tree->root, fun);
}

struct avlsearchresult{
  avltreenode *node;
  avltreenode *parent;
};
typedef struct avlsearchresult avlsearchresult;

static int avltree_search(const avltree *tree, avlsearchresult *result, const PESSOA *pessoa){
    int found = 0;
    result->node = tree->root;
    while (!found && result->node != NULL){
      int rv = tree->compare(result->node->pessoa, pessoa);
      if (rv == 0) found = 1;
      else{
        result->parent = result->node;
        if (rv > 0) result->node = result->node->left;
        else if (rv < 0) result->node = result->node->right;
      }
    }
    return found;
}

static avltreenode *avltreenode_create(PESSOA *pessoa){
  avltreenode *node = malloc(sizeof(avltreenode));
  if (node){
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->leftheight = 0;
    node->rightheight = 0;
    node->pessoa = pessoa;
  }
  return node;
}

static int avltreenode_get_max_height(const avltreenode *node){
  int height;
  if (node->leftheight > node->rightheight) height = node->leftheight;
  else height = node->rightheight;
  return height;
}

static void avltreenode_fix_height(avltreenode *node){
    node->leftheight = 0;
    node->rightheight = 0;
    if (node->left) node->leftheight = avltreenode_get_max_height(node->left) + 1;
    if (node->right) node->rightheight = avltreenode_get_max_height(node->right) + 1;
}

static void avltree_rotate_left(avltree *tree, avltreenode *node){
  avltreenode *right = node->right;
  if (node == tree->root) tree->root = right;
  else if (node == node->parent->left) node->parent->left = right;
  else node->parent->right = right;
  right->parent = node->parent;
  if (right->left){
    node->right = right->left;
    node->right->parent = node;
  }
  else node->right = NULL;
  right->left = node;
  node->parent = right;
  avltreenode_fix_height(node);
  avltreenode_fix_height(right);
}

static void avltree_rotate_right(avltree *tree, avltreenode *node){
  avltreenode *left = node->left;
  if (node == tree->root) tree->root = left;
  else if (node == node->parent->left) node->parent->left = left;
  else node->parent->right = left;
  left->parent = node->parent;
  if (left->right){
    node->left = left->right;
    node->left->parent = node;
  }
  else node->left = NULL;
  left->right = node;
  node->parent = left;
  avltreenode_fix_height(node);
  avltreenode_fix_height(left);
}

static int avltreenode_get_balance_factor(const avltreenode *node){
  return node->leftheight - node->rightheight;
}

static void avltree_rebalance(avltree *tree, avltreenode *node){
  avltreenode *current = node;
  while (current != NULL){
    avltreenode *parent = current->parent;
    int balance;
    avltreenode_fix_height(current);
    balance = avltreenode_get_balance_factor(current);
    if (balance == -2){
      /* Right heavy */
      const int rightbalance = avltreenode_get_balance_factor(current->right);
      if (rightbalance < 0) avltree_rotate_left(tree, current);
      else{
        avltree_rotate_right(tree, current->right);
        avltree_rotate_left(tree, current);
      }
    }
    else if (balance == 2){
      /* Left heavy */
      const int leftbalance = avltreenode_get_balance_factor(current->left);
      if (leftbalance > 0) avltree_rotate_right(tree, current);
      else{
        avltree_rotate_left(tree, current->left);
        avltree_rotate_right(tree, current);
      }
    }
    current = parent;
  }
}

void *avltree_add(avltree *tree, PESSOA *pessoa){
  void *temp = NULL;
  avlsearchresult result;
  result.node = NULL;
  result.parent = NULL;
  
  if (avltree_search(tree, &result, pessoa)){
    temp = result.node->pessoa;
    result.node->pessoa = pessoa;
  }
  else{
    avltreenode *node = avltreenode_create(pessoa);
    if (result.node == tree->root) tree->root = node;
    else{
      int rv = tree->compare(pessoa, result.parent->pessoa);
      if (rv < 0) result.parent->left = node;
      else result.parent->right = node;
      node->parent = result.parent;
      avltree_rebalance(tree, node);
    }
    tree->count++;
  }
  return temp;
}

void *avltree_find(const avltree *tree, const PESSOA *pessoa){
  void *temp = NULL;
  avlsearchresult result;
  result.node = NULL;
  result.parent = NULL;

  if (avltree_search(tree, &result, pessoa)) temp = result.node->pessoa;
  return temp;
}
static void avltree_for_each_recursive_dates(const avltreenode *root, avltree_forfn fun, DATE *date1, DATE *date2){
  if (root->left != NULL)avltree_for_each_recursive_dates(root->left, fun, date1, date2);
  if (compareDate_Group(root->pessoa, date1, date2) == 0) fun(root->pessoa);
  if (root->right != NULL)avltree_for_each_recursive_dates(root->right, fun, date1, date2);
}

void avltree_search_dates(const avltree *tree, DATE *date1, DATE *date2){
    avltree_for_each_recursive_dates(tree->root, (avltree_forfn)printPessoa, date1, date2);
}

static int StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

static void avltree_for_each_recursive_names(const avltreenode *root, avltree_forfn fun, char *name){
  if (root->left != NULL)avltree_for_each_recursive_names(root->left, fun, name);
  if (StartsWith(root->pessoa->nome, name)) fun(root->pessoa);
  if (root->right != NULL)avltree_for_each_recursive_names(root->right, fun, name);
}

void avltree_search_names(const avltree *tree, char *name) {
    avltree_for_each_recursive_names(tree->root, (avltree_forfn)printPessoa, name);
}



static avltreenode *avltreenode_find_min(avltreenode *node){
  avltreenode *current = node;

  while (current->left) current = current->left;
  return current;
}

static void avltree_remove_node(avltree *tree, avltreenode *node){
  if (node->left && node->right){
    /* Node with 2 children */
    avltreenode *successor = avltreenode_find_min(node->right);
    node->pessoa = successor->pessoa;
    avltree_remove_node(tree, successor);
  }
  else{
    avltreenode *parent = node->parent;
    if (node->left){
      /* Node with only left child */
      if (node->parent){
        if (node == node->parent->left){
          node->parent->left = node->left;
          node->parent->left->parent = node->parent;
        }
        else{
          node->parent->right = node->left;
          node->parent->right->parent = node->parent;
        }
      }
      else{
        tree->root = node->left;
        tree->root->parent = NULL;
      }
    }
    else if (node->right){
      /* Node with only right child */
      if (node->parent){
        if (node == node->parent->left){
          node->parent->left = node->right;
          node->parent->left->parent = node->parent;
        }
        else{
          node->parent->right = node->right;
          node->parent->right->parent = node->parent;
        }
      }
      else{
        tree->root = node->right;
        tree->root->parent = NULL;
      }
    }
    else{
      /* Node with no children */
      if (node->parent){
        if (node == node->parent->left) node->parent->left = NULL;
        else node->parent->right = NULL;
      }
      else tree->root = NULL;
    }
    avltreenode_delete(node);
    avltree_rebalance(tree, parent);
    tree->count--;
  }
}

void *avltree_remove(avltree *tree, const PESSOA *pessoa){
  void *temp = NULL;
  avlsearchresult result;
  result.node = NULL;
  result.parent = NULL;

  if (avltree_search(tree, &result, pessoa)){
    temp = result.node->pessoa;
    avltree_remove_node(tree, result.node);
  }
  return temp;
}

size_t avltree_get_count(const avltree *tree){
  return tree->count;
}

PESSOA** read_arq(int *size){

  int i=0;
  PESSOA **pessoas = (PESSOA**) malloc(sizeof(PESSOA));
  char buffer[BUFFER_SIZE], *nome_arq;
  FILE *arq_pessoas;

  printf("\nDigite o nome do arquivo a ser lido: ");scanf("%ms",&nome_arq);

  arq_pessoas = fopen(nome_arq, "r");
  if (!arq_pessoas){
    printf("\nERRO! O arquivo não foi aberto!\n");
    return NULL;
  } 
  else printf("\nO arquivo foi aberto e lido com sucesso!\n");
  
  while(fgets(buffer, sizeof(buffer), arq_pessoas)!= NULL){
    char *nome, *cidade, *nascimento;
    unsigned long long *rg, *cpf;
    nome = (char*) malloc(50*sizeof(char));
    cidade = (char*) malloc(50*sizeof(char));
    nascimento = (char*) malloc(11*sizeof(char));
    rg = (unsigned long long*) malloc(sizeof(unsigned long long));
    cpf = (unsigned long long*) malloc(sizeof(unsigned long long));
    char *tok = strtok(buffer, ";");
    *cpf = atof(tok);
    tok = strtok(NULL, ";");
    *rg = atof(tok);
    tok = strtok(NULL, ";");
    strcpy(nome, tok);
    tok = strtok(NULL, ";");
    strcpy(nascimento, tok);
    tok = strtok(NULL, ";");
    strcpy(cidade, tok);
    pessoas[i] = createPessoa(*cpf, *rg, nome, nascimento, cidade);
    pessoas = (PESSOA**) realloc(pessoas, (i+2) * sizeof(PESSOA*));
    i++;
    *size+=1;
  }
  fclose(arq_pessoas);

  return pessoas;
}

void freePessoa (PESSOA *pessoa) {
  free (pessoa->nascimento);
  free (pessoa);
}

void printPessoa(PESSOA *pessoa) {
  printf (" Nome: %s\n CPF: %llu\n RG: %llu\n Nascimento: %d/%d/%d\n Cidade: %s\n", pessoa->nome, pessoa->cpf, pessoa->rg, pessoa->nascimento->day, pessoa->nascimento->month, pessoa->nascimento->year, pessoa->cidade);
}

int compareDate_Group(PESSOA *pessoa, DATE *date1, DATE *date2) { 
  if (pessoa->nascimento->year < date1->year) return -1;
  else if (pessoa->nascimento->year > date2->year) return 1;
  else if ((pessoa->nascimento->year == date1->year) && (pessoa->nascimento->month < date1->month)) return -1;
  else if ((pessoa->nascimento->year == date2->year) && (pessoa->nascimento->month > date2->month)) return 1;
  else if ((pessoa->nascimento->year == date1->year) && (pessoa->nascimento->month == date1->month) && (pessoa->nascimento->day < date1->day)) return -1;
  else if ((pessoa->nascimento->year == date2->year) && (pessoa->nascimento->month == date2->month) && (pessoa->nascimento->day > date2->day)) return 1;
  else return 0; 
}

void convertData(DATE *date1, DATE *date2, char *string1, char *string2) {
    //primeira data
    char *tok = strtok(string1, "/");
    date1->day= atof(tok);
    tok = strtok(NULL, "/");
    date1->month=atof(tok);
    tok = strtok(NULL, "/");
    date1->year=atof(tok);
    //segunda data
    tok = strtok(string2, "/");
    date2->day= atof(tok);
    tok = strtok(NULL, "/");
    date2->month=atof(tok);
    tok = strtok(NULL, "/");
    date2->year=atof(tok);
}