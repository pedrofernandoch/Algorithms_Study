#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<time.h>

void bubble(int *v, int n){
     clock_t start, end;
     double cpu_time_used;
     start = clock();
     int i, j, aux;
     long int comparacoes = 0, trocas = 0;
     for(i = n-1; i >= 0; i--){
           for(j = 0; j < i; j++){
                 if(v[j] > v[j+1]){
                         aux = v[j];
                         v[j] = v[j+1];
                         v[j+1] = aux;
                         trocas++;
                 }
                 comparacoes++;
           }
     }
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     printf("Comparacoes: %ld\nTrocas: %ld\nTempo de CPU usada em seg: %lf\n", comparacoes, trocas, cpu_time_used);
}

void bubbleSentinela(int *vetor, int n){
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int j, u, i, temp;
    long int comparacoes = 0, trocas = 0;
    j = n-1;
    while( j > 0 ){
        u = -1;
        for( i = 0; i < j; i++ ){
            if( vetor[i] > vetor[i+1] ){
                temp = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = temp;
                trocas++;
                u = i;
            }
            comparacoes++;
        }
        j = u; 
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Comparacoes: %ld\nTrocas: %ld\nTempo de CPU usada em seg: %lf\n", comparacoes, trocas, cpu_time_used);
    
}

void selection(int *v, int n){
     clock_t start, end;
     double cpu_time_used;
     start = clock();
     int i, j, min, aux;
     long int comparacoes = 0, trocas = 0;
    for (i = 0; i < n-1; i++){
        min = i;
        for (j = i+1; j < n; j++){
            comparacoes++;
            if(v[j] < v[min]){
                min = j;
            }
        }
        if(i != min){
            aux = v[i];
            v[i] = v[min];
            v[min] = aux;
            trocas++;
        }
        
    }
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     printf("\nTrocas: %ld\nComparacoes: %ld\nTempo de CPU usada em seg: %lf\n", trocas,comparacoes,  cpu_time_used);
}

void insertion(int *v, int n)
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();
	int i, j, atual;
    long int comparacoes = 1, trocas = 0;
	for (i = 0; i < n; i++)
	{
		atual = v[i];
		j = i - 1;

		while ((j >= 0) && comparacoes++ && (atual < v[j])){
			v[j + 1] = v[j];
			j--;
            trocas++;
		}
    
		v[j + 1] = atual;
        
	}
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTrocas: %ld\nComparacoes: %ld\nTempo de CPU usada em seg: %lf\n",trocas, comparacoes-1,  cpu_time_used);
}

void merge(int vetor[], int comeco, int meio, int fim, int *comp, int *trocas) {
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
            *trocas+=1;
        } else {
            vetAux[comAux] = vetor[com2];
            *trocas+=1;
            com2++;
        }
        comAux++;
        *comp+=1; 
    }

    while(com1 <= meio){  //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){    //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux-comeco];
    }
    
    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim, int *comp, int *trocas){
    
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(vetor, comeco, meio,comp,trocas);
        mergeSort(vetor, meio+1, fim,comp,trocas);
        merge(vetor, comeco, meio, fim, comp, trocas);
    }
}

void quicksort(int values[], int began, int end, int *trocas, int *comparacoes)
{
	int i, j, pivo, aux;
	i = began;
	j = end-1;
	pivo = values[(began + end) / 2];
	while(i <= j)
	{
		while(values[i] < pivo && i < end)
		{
			i++;
			*comparacoes+=1;
		}
		while(values[j] > pivo && j > began)
		{
			j--;
			*comparacoes+=1;
		}
		if(i <= j)
		{
			aux = values[i];
			values[i] = values[j];
			values[j] = aux;
			i++;
			j--;
			*trocas+=1;
		}
	}
	if(j > began)
		quicksort(values, began, j+1,trocas,comparacoes);
	if(i < end)
		quicksort(values, i, end,trocas,comparacoes);
}

void shell(int *v, int n){
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int i, g, m,j, trocas = 0, comparacoes = 0;

    for(g = n/2; g >= 1; g /= 2){
        for(i = 0; i < n-g; i++){
            m = v[i+g];
            j=i;

            while(j>=0 && v[j]>m){
                v[j+g] = v[j];
                j-=g;
                trocas++;
            }
            v[j+g]=m;
            comparacoes++;
        }
        
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTrocas: %d\nComparacoes: %d\nTempo de CPU usada em seg: %lf\n", trocas,comparacoes,  cpu_time_used);
}

void heap (int a[], int n){
  clock_t start, end;
  double cpu_time_used;
  start = clock ();

  int i = n / 2, pai, filho, t;
  int trocas = 0, comparacoes = 0;

    while (1){
      if (i > 0){
	    i--;
	    t = a[i];
	  }
      else{
	    n--;
	    if (n <= 0){
	        end = clock ();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf ("Comparacoes: %d\nTrocas: %d\nTempo de CPU usada em seg: %lf\n",comparacoes, trocas, cpu_time_used);
	        return;
	    }
	    t = a[n];
	    a[n] = a[0];
	    trocas++;
	  }
      pai = i;
      filho = i * 2 + 1;
      while (filho < n)	{
	    if ((filho + 1 < n) && (a[filho + 1] > a[filho]))
	        filho++;
            comparacoes++;
	    if (a[filho] > t) {
	      a[pai] = a[filho];
	      pai = filho;
	      filho = pai * 2 + 1;
	      trocas++;
          comparacoes++;
	    }else  break;
	   }
      a[pai] = t;
    }
}

int main(int argc, char **argv){
    int opcao;
    int bflag = 0, gflag = 0, sflag = 0, iflag = 0, mflag = 0, hflag = 0, qflag = 0, zflag = 0;
    int rflag = 0, aflag = 0, dflag = 0, pflag = 0;
    char *K;
    while ((opcao = getopt(argc, argv, "bgsimhqzpk:rad")) != -1){
        switch(opcao){
            // Usuário passou a opção -b, bubble:
			case 'b':
				bflag = 1;
				break;
            case 'g':
                gflag = 1;
                break;
			// Usuário passou a opção -s, selection:
			case 's':
                sflag = 1; // se houver 1 -s então é selection
                break;
            // Usuário passou a opção -i, insertion:
			case 'i':
				iflag = 1;
				break;
            // Usuário passou a opção -m, merge:
			case 'm':
				mflag = 1;
				break;
            // Usuário passou a opção -h, heap:
			case 'h':
				hflag = 1;
				break;
            // Usuário passou a opção -q, quick:
			case 'q':
				qflag = 1;
				break;
            // Usuário passou a opção -z, shell:
            case 'z':
				zflag = 1;
				break;
            // Seta o expoente do tamanho do vetor
            case 'k':
                K = optarg;
				break;
            // Criará vetores randomicos
            case 'r':
                rflag = 1;
                break;
            // Criará vetores crescentes
            case 'a':
                aflag = 1;
                break;
            // Criará vetores decrescentes
            case 'd':
                dflag = 1;
                break;
            // Criará vetores parcialmente ordenado
            case 'p':
                pflag = 1;
                break;
        }
    }
    
    int *v = (int *) malloc(sizeof(int) * pow(10,atoi(K)));
    srand(time(NULL));

    if(rflag){
        for(int i=0; i<pow(10,atoi(K)); i++) v[i] = rand() % 10000;
    }
    else if(aflag){
        int j = 1;
        for(int i=0; i<pow(10,atoi(K)); i++,j++) v[i] = j;
    }
    else if(dflag){
        int j = 1;
        for(int i=pow(10,atoi(K)); i>0; i--) v[i] = j++;
    }
    else if(pflag){
        int j = 1;
        for(int i=0; i<pow(10,atoi(K))/10; i++) v[i] = j++;
        for(int i=pow(10,atoi(K))/10; i<pow(10,atoi(K)); i++) v[i] = rand() % 10000;
    }
    if(bflag){
        printf("Bubble: \n");
        bubble(v, pow(10,atoi(K)));
        //for(int i = 0; i < pow(10,atoi(K)); i++) printf("%d \n", v[i]);
        printf("\n\n");
    }
    if(gflag){
        printf("Bubble com Sentinela: \n");
        bubbleSentinela(v, pow(10,atoi(K)));
        //for(int i = 0; i < pow(10,atoi(K)); i++) printf("%d \n", v[i]);
        printf("\n\n");
    }
    if(sflag){
        printf("Selection: ");
        selection(v, pow(10,atoi(K)));
        //for(int i = 0; i < pow(10,atoi(K)); i++) printf("%d ", v[i]);
        printf("\n\n");
    }
    if(iflag){
        printf("Insertion: ");
        insertion(v, pow(10,atoi(K)));
        //for(int i = 0; i < pow(10,atoi(K)); i++) printf("%d ", v[i]);
        printf("\n\n");
    }
    //Nos algoritmos recursivos o ultimo print é o que importa
    if(mflag){
		int comp=0, trocas=0;
        printf("Merge: ");
		clock_t start, end;
    	double cpu_time_used;
    	start = clock();
	    mergeSort(v,0,pow(10,atoi(K)),&comp,&trocas);
	    end = clock();
    	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    	printf("\nTrocas: %d\nComparacoes: %d\nTempo de CPU usada em seg: %lf\n",trocas, comp,  cpu_time_used);
        //for(int i = 0; i < pow(10,atoi(K)); i++) printf("%d ", v[i]);
        printf("\n\n");
    }
    if(hflag){
        printf("Heap: \n");
        heap(v, pow(10,atoi(K)));
        //for(int i = 0; i < pow(10,atoi(K)); i++) printf("%d ", v[i]);
        printf("\n\n");
    }
    if(qflag){
        int trocas1 = 0, comparacoes = 0;
        printf("Quick: ");
        clock_t start, end;
    	double cpu_time_used;
    	start = clock();
    	quicksort(v, 0, pow(10,atoi(K)), &trocas1, &comparacoes);
    	end = clock();
    	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\nTempo de CPU usada em seg: %lf\nComparacoes = %d\nTrocas = %d\n",cpu_time_used,comparacoes,trocas1);
        //for(int i = 0; i < pow(10,atoi(K)); i++) printf("%d ", v[i]);
        printf("\n\n");
    }
    if(zflag){
        printf("Shell: ");
        shell(v, pow(10,atoi(K)));
        //for(int i = 0; i < pow(10,atoi(K)); i++) printf("%d ", v[i]);
        printf("\n\n");
    }
    free(v);
}
