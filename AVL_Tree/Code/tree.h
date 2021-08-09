#ifndef _TREE_
#define _TREE_

#include <stdlib.h>

typedef struct date {
  int month;
  int year;
  int day;
} DATE;

typedef struct Pessoa {
  unsigned long long cpf, rg;
  char *nome, *cidade;
  DATE *nascimento;
} PESSOA;

struct avltreenode{
  struct avltreenode *left;
  struct avltreenode *right;
  struct avltreenode *parent;
  unsigned int leftheight;
  unsigned int rightheight;
  PESSOA *pessoa;
};

typedef struct avltreenode avltreenode;

typedef int (*avltree_cmpfn)(const void *, const void *);
typedef void (*avltree_forfn)(void *);

struct avltree{
  avltreenode *root;
  size_t count;
  avltree_cmpfn compare;
};

typedef struct avltree avltree;


avltree *avltree_create(avltree_cmpfn compare);
void avltree_delete(avltree *tree);
void avltree_for_each(const avltree *tree, avltree_forfn fun);
void *avltree_add(avltree *tree, PESSOA *pessoa);
void *avltree_find(const avltree *tree, const PESSOA *pessoa);
void *avltree_remove(avltree *tree, const PESSOA *pessoa);
void avltree_empty(avltree *tree);
size_t avltree_get_count(const avltree *tree);
PESSOA *createPessoa (unsigned long long cpf, unsigned long long rg, char *nome, char *nascimento, char *cidade);
int compareCPF(PESSOA *pessoa1, PESSOA *pessoa2);
int compareRG(PESSOA *pessoa1, PESSOA *pessoa2);
int compareNome(PESSOA *pessoa1, PESSOA *pessoa2);
int compareDate(PESSOA *pessoa1, PESSOA *pessoa2);
PESSOA** read_arq(int *);
void freePessoa (PESSOA *pessoa);
void printPessoa(PESSOA *pessoa);
int compareDate_Group(PESSOA *pessoa, DATE *date1, DATE *date2);
void avltree_search_dates(const avltree *tree, DATE *date1, DATE *date2);
void avltree_search_names(const avltree *tree, char *name);
void convertData(DATE *date1, DATE *date2, char *string1, char *string2);

#endif
