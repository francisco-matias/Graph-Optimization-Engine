#ifndef Proj_INCLUDED
#define Proj_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/*
 *Ficheiros:
 *
 * main.c -> onde se encontra o main.
 * 
 * fase1.c -> todas as funções relativas a funcionalidades da primeira fase.
 * 
 * fase2.c -> todas as funções relativas a funcionalidades da segunda fase.
 * 
 * Djikstra.c ->todas as funções relativas a funcionalidades do algoritmo Djikstra.
 * 
 * grafo.c -> todas as funções relativas a gestão de um grafo implementado usando uma lista de adjacencisa utilizado na segunda fase.
 * 
 */


                                /*Functions used in first phase:*/


void fase1(char str1[], char str2[]);


int binary_search(char** sorted_array, char* word, int result);

int less(char *a, char *b);

void exchange(char *a, char *b);

int partition_function(char **array, int left, int right);

void Quick_Sort(char **array, int left, int right);

void mode1_2(char ***tabela, char *word1, char *word2, int *position, int *num_words);

void fase1(char str1[], char str2[]);

void free_function(char **array, int length);

void free_table(char ***tabela, int max_length, int *num_words);

                            
                            /*structures & Functions used in phase 2:*/

typedef struct heap
{
    int free;
    int size;
    int *queue;
}heap;


typedef struct node{
    int vertex; 
    int weight;
    char* word;   //meti este parâmetro pois vai ser preciso printar as palavras que fazem parte do caminho
    struct node* next;
}Node;

typedef struct graph{
    int numVertices;
    struct node** adjLists;
}Graph;

void Djikstra(Graph *G, int *wt, int *st, int start, int mutations_allowed); //Djikstra

void fase2(char str1[], char str2[]);

Node* createNode(int v, int weight, char* word);

Graph* createAGraph(int vertices);

int recursive_print(int *vector_rigth_path, int *st, int last_index, int flag_path, int i);

int recursive_count_vertices(int *st, int last_index,int flag_path, int counter);

void freeLinkedList(Node* first);

void free_graph(Graph* graph);

void addEdge_s_d(Graph* graph, int s, int d, int differences, char* word2);

void addEdge_d_s(Graph* graph, int s, int d, int differences, char* word1);

Graph** graph_building(char*** tabela, int* max_mutations, int max_length, Graph** graph_array, int* num_words);

heap *PQinit(int Size);

heap *queue_upd(heap *acervo, int *wt, int w);

int PQempty(heap *acervo);

heap *PQinsert(heap *acervo, int *wt, int index);

int PQdelmin(heap *acervo, int *wt);

heap *FixUp(heap *acervo, int *wt, int Idx);

heap *FixDown(heap *acervo,int *wt, int Idx, int N);

int check_high_prio(int a, int b);

#endif