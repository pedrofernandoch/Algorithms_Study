#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

int main(void)
{
  int size=0,i,op=1, op2=-1;
  char *nome, *cidade, *nascimento,*intervalo1,*intervalo2;
  unsigned long long rg, cpf;
  avltree *CPFtree, *DATATree, *Nometree;
  PESSOA *result;
  DATE *date1 = (DATE *) malloc (sizeof(DATE));
  DATE *date2 = (DATE *) malloc (sizeof(DATE));
  unsigned int e;
  PESSOA **pessoas;
  CPFtree = avltree_create((avltree_cmpfn)compareCPF); // Criando uma arvore ordenada por CPF
  DATATree = avltree_create((avltree_cmpfn)compareDate); // Criando uma arvore ordenada por RG
  Nometree = avltree_create((avltree_cmpfn)compareNome); // Criando uma arvore ordenada por Nome

  //=======================================================================================//
  //                                        MENU                                           //
  //=======================================================================================//
  system("clear");
  while(op!=0){
    printf("\n                    MENU\n\n");
    printf("==============================================");
    printf("\n\nDigite o número da operação desejada\n\n");
    printf("1-  Ler arquivo\n");
    printf("2-  Consulta\n");
    printf("3-  Inserir novo cadastro\n");
    printf("4-  Remover cadastro\n");
    printf("5-  Imprimir cadastros\n");
    printf("6-  Apagar banco de dados\n\n");
    printf("==============================================");
    printf("\n\nDigite 0 para sair\n\n");
    scanf("%d",&op);
    system("clear");
    switch(op){
      case 1: { //OP 1
        pessoas = read_arq(&size);
        for(i=0;i<size;i++){
        avltree_add(CPFtree, pessoas[i]);
        avltree_add(DATATree, pessoas[i]);
        avltree_add(Nometree, pessoas[i]);
        }
        break;
      }
      case 2: { // OP 2
        printf("\nDigite o número da operação desejada\n\n");
        printf("1-  Consulta por CPF\n");
        printf("2-  Conuslta por Nome\n");
        printf("3-  Conuslta por Data de Nascimento\n\n");
        scanf("%d",&op2);
        system("clear");
        switch(op2){ 
          case 1:{  // OP 2.1
            if (CPFtree) {
              printf(" Consulta por CPF\n\n");
              PESSOA *pessoaAux;
              char nomeAux[3] = "Aux";
              char dataAux[10] = "00/00/0000";
              char cidadeAux[3] = "Aux";
              printf("CPF: ");scanf("%llu",&cpf);
              pessoaAux = createPessoa(cpf, 0, nomeAux, dataAux, cidadeAux);
              result = avltree_find(CPFtree, pessoaAux);
              if (result) {
                printf("\nEncontrado: \n");
                printPessoa(result);
              }
              else printf("\nNão Encontrado\n");
              freePessoa(pessoaAux);
            }
            break;
          }
          case 2:{  //OP 2.2
            if (Nometree) { 
              printf(" Conuslta por Nome\n\n");
              PESSOA *pessoaAux;
              char dataAux[10] = "00/00/0000";
              char cidadeAux[3] = "Aux";
              printf("\nNome: ");
              scanf (" %ms", &nome);
              for (int i=0;i<strlen(nome);i++)nome[i] = toupper(nome[i]);
              avltree_search_names(Nometree, nome);
            }
            break;
          }
          case 3:{ //OP 2.3
            printf(" Conuslta por Data de Nascimento\n\n");
            if (DATATree) {
              char nomeAux[3] = "Aux";
              char cidadeAux[3] = "Aux";
              printf("Intervalo entre Datas:\n\n");
              printf("Depois de -> ");scanf(" %ms",&intervalo1);
              printf("\n");
              printf("Antes de -> ");scanf(" %ms",&intervalo2);
              printf("\n");
              convertData(date1, date2, intervalo1, intervalo2);
              avltree_search_dates(DATATree, date1, date2);
            }
            break;
          }
        }
        break;
      }
      case 3: { //OP 3
        if (DATATree && CPFtree && Nometree) {
          PESSOA *pessoa;
          printf("\nNome: ");scanf (" %m[^\n]s", &nome);
          for (int i=0;i<strlen(nome);i++)nome[i] = toupper(nome[i]);
          printf("RG: ");scanf("%llu",&rg);
          printf("CPF: ");scanf("%llu",&cpf);
          printf("Cidade: ");scanf (" %m[^\n]s\n", &cidade);
          for (int i=0;i<strlen(cidade);i++)cidade[i] = toupper(cidade[i]);
          strcat(cidade, "\n");
          printf("Data de Nascimento: ");scanf("%ms",&nascimento);
          pessoa = createPessoa(cpf, rg, nome, nascimento, cidade);
          avltree_add(CPFtree, pessoa);
          avltree_add(DATATree, pessoa);
          avltree_add(Nometree, pessoa);
          printf("\nCadastro inserido sucesso!\n\n");
        }
        break;
      }
      case 4: { //OP 4
        printf("\nDigite o número da operação desejada\n\n");
        printf("1-  Remover pelo nome\n");
        printf("2-  Remover pelo CPF\n");
        printf("3-  Remover pela data de nascimento\n\n");
        scanf("%d",&op2);
        system("clear");
        PESSOA *auxPessoa;
        switch(op2){
          case 1: { //OP 4.1
            if (Nometree) {
              printf(" Remover pelo nome\n\n");
              PESSOA *pessoaAux;
              char dataAux[10] = "00/00/0000";
              char cidadeAux[3] = "Aux";
              printf("\nNome: ");
              scanf (" %m[^\n]s", &nome);
              for (int i=0;i<strlen(nome);i++)nome[i] = toupper(nome[i]);
              pessoaAux = createPessoa(0, 0, nome, dataAux, cidadeAux);
              result = avltree_find(Nometree, pessoaAux);
              if (result) {
                printf("\nExcluindo:\n\n");
                printPessoa(result);
                avltree_remove(Nometree, result);
                avltree_remove(CPFtree, result);
                avltree_remove(DATATree, result);
                printf("\nCadastro removido com sucesso!\n");
              }
              else printf("\nNão Encontrado\n");
              freePessoa(pessoaAux);
              free (result);
            }
            break;
          }
          case 2: { //OP 4.2
            if (CPFtree) {
              printf(" Remover pelo CPF\n\n");
              PESSOA *pessoaAux;
              char nomeAux[3] = "Aux";
              char dataAux[10] = "00/00/0000";
              char cidadeAux[3] = "Aux";
              printf("CPF: ");scanf("%llu",&cpf);
              pessoaAux = createPessoa(cpf, 0, nomeAux, dataAux, cidadeAux);
              result = avltree_find(CPFtree, pessoaAux);
              if (result) {
                printf("\nExcluindo:\n\n");
                printPessoa(result);
                avltree_remove(Nometree, result);
                avltree_remove(CPFtree, result);
                avltree_remove(DATATree, result);
                printf("\nCadastro removido com sucesso!\n");
              }
              else printf("\nNão Encontrado\n");
              freePessoa(pessoaAux);
              free (result);
            }
            break;
          }
          case 3: { //OP 4.3
            if (DATATree) {
              printf(" Remover pela data de nascimento\n\n");
              PESSOA *pessoaAux;
              char nomeAux[3] = "Aux";
              char cidadeAux[3] = "Aux";
              printf("Data de Nascimento: ");
              scanf("%ms",&nascimento);
              pessoaAux = createPessoa(0, 0, nomeAux, nascimento, cidadeAux);
              result = avltree_find(DATATree, pessoaAux);
              if (result) {
                printf("\nExcluindo:\n\n");
                printPessoa(result);
                avltree_remove(Nometree, result);
                avltree_remove(CPFtree, result);
                avltree_remove(DATATree, result);
                printf("\nCadastro removido com sucesso!\n");
              }
              else printf("\nNão Encontrado\n");
              freePessoa(pessoaAux);
              freePessoa(pessoaAux);
              free (result);
            }
            break;
          }
        }
        break;
      }
      case 5: { //OP 5
        printf("\nDigite o número da operação desejada\n\n");
        printf("1-  Imprimir cadastros ordenados pelo Nome\n");
        printf("2-  Imprimir cadastros ordenados pelo CPF\n");
        printf("3-  Imprimir cadastros ordenados pela Data de Nascimento\n\n");
        scanf("%d",&op2);
        system("clear");
        switch(op2){
          case 1:{  //OP 5.1
            printf(" Imprimir cadastros ordenados pelo Nome\n\n");
            if (Nometree) {
              avltree_for_each(Nometree, (avltree_forfn)printPessoa);
            }
            break;
          }
          case 2:{ //OP 5.2
            printf(" Imprimir cadastros ordenados pelo CPF\n\n");
            if (CPFtree) {
            avltree_for_each(CPFtree, (avltree_forfn)printPessoa);
            }
            break;
          }
          case 3:{ //OP 5.3
            printf(" Imprimir cadastros ordenados pela Data de Nascimento\n\n");
            if (DATATree) {
              avltree_for_each(DATATree, (avltree_forfn)printPessoa);
            }
            break;
          }
        }
        break;
      }
      case 6: { //OP 6
        avltree_delete(CPFtree);
        CPFtree = NULL;
        avltree_delete(DATATree);
        DATATree = NULL;
        avltree_delete(Nometree);
        Nometree = NULL;
        free (pessoas);
        printf("\nBanco de dados apagado com sucesso!\n");
        break;  
      }      
    }
  }

  return 0;
}