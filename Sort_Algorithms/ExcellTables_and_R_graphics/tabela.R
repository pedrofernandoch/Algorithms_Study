rm(list = ls())
# library
library(ggplot2)
library(tidyverse)
library(tidyr)
library(dplyr)
library(ggpubr)

dados_mergeSort <- read.csv("MergeSort.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")
dados_quickSort <- read.csv("QuickSort.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")
dados_bubbleSort <- read.csv("BubbleSort.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")
dados_bubble_sentinelaSort <- read.csv("Bubble_SentinelaSort.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")
dados_insertionSort <- read.csv("InsertionSort.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")
dados_heapSort <- read.csv("HeapSort.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")
dados_shellSort <- read.csv("ShellSort.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")
dados_selectionSort <- read.csv("SelectionSort.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")
dados_vencedor_troca <- read.csv("Vencedor_troca.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")
dados_vencedor_comp <- read.csv("Vencedor_comp.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")
dados_vencedor_tempo <- read.csv("Vencedor_tempo.csv",header = TRUE, sep = ";", dec = ",", fileEncoding = "UTF-8-BOM")


#Para melhor vizualização dos gráficos
dados_vencedor_troca$N_trocas <- log(dados_vencedor_troca$N_trocas)
dados_vencedor_comp$N_comp <- log(dados_vencedor_comp$N_comp)
dados_vencedor_tempo$Tempo_exec <- log(dados_vencedor_tempo$Tempo_exec)

#GRÁFICOS PARA TEMPO DE EXECUSSÃO

#Merge
G1_Merge <- ggplot(dados_mergeSort, aes(fill=Tipo_Vetor, x = Ordem, y= Tempo_exec))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Tempo de Execução em segundos")+
  ggtitle("Tempo de execução Merge-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(Tempo_exec,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Merge.png")

#Bubble
G1_Bubble <- ggplot(dados_bubbleSort, aes(fill=Tipo_Vetor, x = Ordem, y= Tempo_exec))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Tempo de Execução em segundos")+
  ggtitle("Tempo de execução Bubble-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(Tempo_exec,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Bubble.png")

#Bubble_Sentinela
G1_Bubble_Sentinela <- ggplot(dados_bubble_sentinelaSort, aes(fill=Tipo_Vetor, x = Ordem, y= Tempo_exec))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Tempo de Execução em segundos")+
  ggtitle("Tempo de execução Bubble_Sentinela-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(Tempo_exec,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Bubble_Sentinela.png")

#Shell
G1_Shell <- ggplot(dados_shellSort, aes(fill=Tipo_Vetor, x = Ordem, y= Tempo_exec))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Tempo de Execução em segundos")+
  ggtitle("Tempo de execução Shell-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(Tempo_exec,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Shell.png")

#Selection
G1_Selection <- ggplot(dados_selectionSort, aes(fill=Tipo_Vetor, x = Ordem, y= Tempo_exec))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Tempo de Execução em segundos")+
  ggtitle("Tempo de execução Selection-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(Tempo_exec,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Selection.png")

#Quick
G1_Quick <- ggplot(dados_quickSort, aes(fill=Tipo_Vetor, x = Ordem, y= Tempo_exec))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Tempo de Execução em segundos")+
  ggtitle("Tempo de execução Quick-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(Tempo_exec,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Quick.png")

#Insertion
G1_Insertion <- ggplot(dados_insertionSort, aes(fill=Tipo_Vetor, x = Ordem, y= Tempo_exec))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Tempo de Execução em segundos")+
  ggtitle("Tempo de execução Insertion-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(Tempo_exec,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Insertion.png")

#Heap
G1_Heap <- ggplot(dados_heapSort, aes(fill=Tipo_Vetor, x = Ordem, y= Tempo_exec))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Tempo de Execução em segundos")+
  ggtitle("Tempo de execução Heap-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(Tempo_exec,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Heap.png")

#GRÁFICOS PARA TROCAS 

#Merge
G2_Merge <- ggplot(dados_mergeSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_trocas/100))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de trocas * 0,01")+
  ggtitle("Número de trocas Merge-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_trocas,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Merge1.png")

#Bubble
G2_Bubble <- ggplot(dados_bubbleSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_trocas/10000000))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de trocas * 0,0000001")+
  ggtitle("Número de trocas Bubble-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_trocas,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Bubble1.png")

#Bubble_Sentinela
G2_Bubble_Sentinela <- ggplot(dados_bubble_sentinelaSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_trocas/10000000))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de trocas * 0,0000001")+
  ggtitle("Número de trocas Bubble_Sentinela-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_trocas,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Sentinela1.png")

#Shell
G2_Shell <- ggplot(dados_shellSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_trocas/1000))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de trocas * 0,001")+
  ggtitle("Número de trocas Shell-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_trocas,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Shell1.png")

#Selection
G2_Selection <- ggplot(dados_selectionSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_trocas/100))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de trocas * 0,01")+
  ggtitle("Número de trocas Selection-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_trocas,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Selection1.png")
  
#Quick
G2_Quick <- ggplot(dados_quickSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_trocas/100))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de trocas * 0,01")+
  ggtitle("Número de trocas Quick-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_trocas,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Quick1.png")

#Insertion
G2_Insertion <- ggplot(dados_insertionSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_trocas/10000000))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de trocas * 0,0000001")+
  ggtitle("Número de trocas Insertion-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_trocas,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Insertion1.png")

#Heap
G2_Heap <- ggplot(dados_heapSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_trocas/100))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de trocas * 0,01")+
  ggtitle("Número de trocas Heap-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_trocas,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_heap1.png")

#Gráfico PARA NÚMERO DE COMPARAÇÕES

#Merge
G3_Merge <- ggplot(dados_mergeSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_comp/100))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de comparações * 0,01 ")+
  ggtitle("Número de comparações Merge-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_comp,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_Merge2.png")

#Bubble
G3_Bubble <- ggplot(dados_bubbleSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_comp/10000000))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de comparações * 0,0000001 ")+
  ggtitle("Número de comparações Bubble-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_comp,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_bubble2.png")

#Bubble_Sentinela
G3_Bubble_Sentinela <- ggplot(dados_bubble_sentinelaSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_comp/10000000))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de comparações * 0,0000001 ")+
  ggtitle("Número de comparações Bubble_Sentinela-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_comp,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_sentinela2.png")

#Shell
G3_Shell <- ggplot(dados_shellSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_comp/100))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de comparações * 0,01 ")+
  ggtitle("Número de comparações Shell-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_comp,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_shell2.png")

#Selection
G3_Selenction <- ggplot(dados_selectionSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_comp/10000000))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de comparações * 0,0000001 ")+
  ggtitle("Número de comparações Selection-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_comp,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_selection2.png")

#Quick
G3_Quick <- ggplot(dados_quickSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_comp/100))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de comparações * 0,01 ")+
  ggtitle("Número de comparações Quick-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_comp,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_quick2.png")

#Insertion
G3_Insertion <- ggplot(dados_insertionSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_comp/10000000))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de comparações * 0,0000001 ")+
  ggtitle("Número de comparações Insertion-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_comp,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_insertion2.png")

#Heap
G3_Heap <- ggplot(dados_heapSort, aes(fill=Tipo_Vetor, x = Ordem, y=N_comp/1000))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Número de comparações * 0,001 ")+
  ggtitle("Número de comparações Heap-Sort")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")+
  geom_text(aes(label = round(N_comp,6)),position= position_dodge(width=0.9),vjust=-0.25, size = 2)
  ggsave("G1_heap2.png")

#VENCEDOR TEMPO DE EXECUÇÃO
G1_Exec <- ggplot(dados_vencedor_tempo, aes(fill=Tipo_Vetor, x = Algoritmos, y = Tempo_exec))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Log do Tempo de execução em segundos ")+
  ggtitle("Tempo de execução dos algoritmos")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")

#VENCEDOR NÚMERO DE TROCAS
G1_Trocas <- ggplot(dados_vencedor_troca, aes(fill=Tipo_Vetor, x = Algoritmos, y = N_trocas))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Log do número de Trocas")+
  ggtitle("Número de Trocas dos algoritmos")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")
  

#VENCEDOR NÚMERO DE COMPARAÇÕES
G1_Comp <- ggplot(dados_vencedor_comp, aes(fill=Tipo_Vetor, x = Algoritmos, y = N_comp))+
  geom_bar(position="dodge", stat="identity")+
  ylab("Log do número Comparações")+
  ggtitle("Número de comparações dos algoritmos")+
  theme_bw()+
  scale_fill_discrete(name = "Tipo Vetor")+
  scale_fill_brewer(palette = "Set1")
