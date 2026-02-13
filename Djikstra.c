#include "Proj.h"

//Macros
#define P (wt[v] + t->weight)
#define INFINITY INT_MAX
#define exch(a, b) { int t = a; a = b; b = t; }

/*****************************************************************************
 * Djikstra ()
 *
 * Arguments: 
 *            G - A graph
 *            left, right - limits on table to consider
 *            less - item comparison function
 *            start - The id of the 1st word (begin of the path)  
 *            mutations_allowed - The mutations of the problem 
 * 
 * Returns: (void)
 *
 * Description: Used to find the shortest path on a given problem.
 *****************************************************************************/
void Djikstra(Graph *G, int *wt, int *st, int start, int mutations_allowed)
{
    int v, w;
    Node *t = NULL;
    heap *acervo = NULL;

    acervo = PQinit(G->numVertices);
    for (v = 0; v < G->numVertices; v++)
    {
        st[v] = -2;
        wt[v] = INFINITY; //distancias
    }
    wt[start] = 0;
    st[start] = -1;
    acervo = PQinsert(acervo, wt, start); 

    while (!PQempty(acervo))
    {
        v = PQdelmin(acervo, wt); //Da Pop do vertice com maior prioridade

        for (t = G->adjLists[v]; t != NULL; t = t->next)
        {
            if(t->weight <= (mutations_allowed*mutations_allowed)){

                w = t->vertex; //vértices da lista de adjacência de v
                if (wt[w] == INFINITY)//vértice ainda não visto
                {  
                    wt[w] = P;
                    st[w] = v;
                    acervo = PQinsert(acervo, wt, w);
                }
                else //vértice que já foi visto, logo está no acervo
                {
                    if (wt[w] > P)
                    {
                        wt[w] = P;
                        st[w] = v;
                        acervo = queue_upd(acervo, wt, w);
                    }
                }
            }
            
        }
    }
    free(acervo->queue);
    free(acervo);
}

                    /* Funções para construir o Djikstra!*/

/*****************************************************************************
 * PQinit ()
 *
 * Arguments: size - The size of the heap.
 * 
 * Returns: The heap.
 *
 * Description: Used to find the shortest path on a given problem.
 *****************************************************************************/
heap *PQinit(int size)
{
    heap *aux = NULL;
    aux = (heap *)malloc(sizeof(heap));

    aux->queue = (int *)malloc(size * sizeof(int));
    aux->size = size;
    aux->free = 0;

    return aux;
}

/*****************************************************************************
 * PQinit ()
 *
 * Arguments: acervo - The heap.
 *            wt - An array with the weights.
 *            w - The weigth we want to compare with.    
 * 
 * Returns: The heap.
 *
 * Description: Updates the queue of the heap.
 *****************************************************************************/
heap *queue_upd(heap *acervo, int *wt, int w)
{
    int i = 0; 
    for (i = 0; i < acervo->free; i++)
    {   
        if (acervo->queue[i] == w)
        {   
            // printf("Encontrei logo vou dar fixup\n");
            acervo = FixUp(acervo, wt, i);
            return acervo;
        }
    }
    return acervo;
}

/*****************************************************************************
 * PQempty ()
 *
 * Arguments: acervo - The heap.
 * 
 * Returns: The heap.
 *
 * Description: Checks if the heap is empty.
 *****************************************************************************/
int PQempty(heap *acervo)
{
    return ((acervo->free == 0) ? 1 : 0);
}

/*****************************************************************************
 * PQinsert ()
 *
 * Arguments: acervo - The heap.
 *            wt - An array with the weights.
 *            index - The actual index.
 * 
 * Returns: The heap.
 *
 * Description: Inserts an index to the heap.
 *****************************************************************************/
heap *PQinsert(heap *acervo, int *wt, int index)
{
    //insere novo elemento no fim do acervo
    if ((acervo->free + 1) < acervo->size)
    { 
        acervo->queue[acervo->free] = index;
        //reordena o acervo com FixUp 
        acervo = FixUp(acervo, wt, acervo->free);
        acervo->free++;
    }
    return acervo;
}

/*****************************************************************************
 * PQdelmin ()
 *
 * Arguments: acervo - The heap.
 *            wt - An array with the weights.
 * 
 * Returns: the number of the queue.
 *
 * Description: Inserts an index to the heap.
 *****************************************************************************/
int PQdelmin(heap *acervo, int *wt)
{
    exch(acervo->queue[0], acervo->queue[(acervo->free) - 1]);
    acervo = FixDown(acervo, wt, 0, acervo->free-1);

    return acervo->queue[--(acervo->free)];
}

/*****************************************************************************
 * FixUp ()
 *
 * Arguments: acervo - The heap.
 *            wt - An array with the weights.
 *            Idx - An index to the heap.  
 * 
 * Returns: The heap.
 *
 * Description: Fix up the Idx in the queue.
 *****************************************************************************/
heap *FixUp(heap *acervo, int *wt, int Idx)
{   
    while (Idx > 0 && (wt[acervo->queue[(Idx - 1) / 2]] > wt[acervo->queue[Idx]]))
    {   
        exch(acervo->queue[Idx], acervo->queue[(Idx - 1) / 2]);
        Idx = (Idx - 1) / 2;
    }
    return acervo;
}

/*****************************************************************************
 * FixDown ()
 *
 * Arguments: acervo - The heap.
 *            wt - An array with the weights.
 *            Idx - An index to the heap. 
 *            N - The number of vertices   
 * 
 * Returns: The heap.
 *
 * Description: Fix down the Idx in the queue.
 *****************************************************************************/
heap *FixDown(heap *acervo,int *wt, int Idx, int N)
{
    int Child;

    while (2 * Idx < N - 1)
    {   
        Child = 2 * Idx + 1;

        if (Child < (N - 1) && !check_high_prio(wt[acervo->queue[Child]], wt[acervo->queue[Child + 1]]))
            Child++;
        if (check_high_prio(wt[acervo->queue[Idx]], wt[acervo->queue[Child]]))
            break; 

        exch(acervo->queue[Idx], acervo->queue[Child]);
        Idx = Child;
    }
    return acervo;
}

/*****************************************************************************
 * check_high_prio ()
 *
 * Arguments: a - An index.
 *            b - An index.  
 * 
 * Returns: If a is lower than the b return true, otherwise return 0.
 *
 * Description: checks if a is bigger than the b.
 *****************************************************************************/
int check_high_prio(int a, int b)
{
    if(a < b)
        return 1;
    else
        return 0;
}