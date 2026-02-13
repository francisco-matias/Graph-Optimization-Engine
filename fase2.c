#include "Proj.h"

/*******************************************************************************
 * createNode ()
 *
 * Arguments: word - The number of vertices.
 *            weitght - The weight.
 *            word - the word.  
 * 
 * Returns: The new node in this list.
 *
 * Description: Creates a new node to the list with the 3 parameters listed 
 *              above.
 *****************************************************************************/
Node* createNode(int v, int weight, char* word)
{

    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = weight*weight;
    newNode->word = word;
    newNode->next = NULL;

    return newNode;
}

/*******************************************************************************
 * createAgraph ()
 *
 * Arguments: vertices - The number of vertices.
 * 
 * Returns: The graph.
 *
 * Description: Creates the adjacency lists, our graph.
 *****************************************************************************/
Graph* createAGraph(int vertices)
{
    register int i;

    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));

    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

/*******************************************************************************
 * addVertex ()
 *
 * Arguments: graph - Our graph.
 *            s - The index of the 1st word.      
 *            d - The index of the 2nd word.
 *            word1 - The 1st word.
 *            word2 - The 2nd word.  
 * 
 * Returns: (void).
 *
 * Description: Creates the main vertex (The 1st vertex of each adjacency list).
 *****************************************************************************/
void addVertex(Graph* graph, int s, int d, char* word1, char* word2){

    int weight;
    if(graph->adjLists[s] == NULL){
        weight = 0;
        Node* new_pricipal_Node1 = createNode(s, weight, word1);
        graph->adjLists[s] = new_pricipal_Node1;
    }

    if(graph->adjLists[d] == NULL){

        weight = 0;
        Node* new_pricipal_Node2 = createNode(d, weight, word2);
        graph->adjLists[d] = new_pricipal_Node2;
    }

}

/*******************************************************************************
 * addEdge_s_d ()
 *
 * Arguments: graph - Our graph.
 *            s - The index of the 1st word.      
 *            d - The index of the 2nd word.
 *            differences - The weight.  
 *            word2 - The 2nd word.  
 * 
 * Returns: (void).
 *
 * Description: Creates an edge between s and d word.
 *****************************************************************************/
void addEdge_s_d(Graph* graph, int s,int d, int differences, char* word2)
{
    Node* aux1 = graph->adjLists[s];
    Node* aux2 = aux1->next;

    Node* newNode = createNode(d, differences, word2);
    aux1->next = newNode;
    newNode->next = aux2;

}

/*******************************************************************************
 * addEdge_d_s ()
 *
 * Arguments: graph - Our graph.
 *            s - The index of the 1st word.      
 *            d - The index of the 2nd word.
 *            differences - The weight.  
 *            word1 - The 1st word.  
 * 
 * Returns: (void).
 *
 * Description: Creates an edge between d and s word.
 *****************************************************************************/
void addEdge_d_s(Graph* graph, int s, int d, int differences, char* word1)
{

    Node* aux2 = graph->adjLists[d];
    Node* aux3 = aux2->next;

    Node* newNode2 = createNode(s, differences, word1);
    aux2->next = newNode2;
    newNode2->next = aux3;

}

//Just to check if the graphs are correct.
void print_graphs(Graph** graph_array, int max_length, int* max_mutations){

    Node* aux = NULL;

    for(register int i=0; i<max_length; i++){

        if(max_mutations[i] != 0){

            for(register int j=0; j<graph_array[i]->numVertices; j++){
                
                if(graph_array[i]->adjLists[j] != NULL){

                    aux = graph_array[i]->adjLists[j];
                    if(aux != NULL){

                        while(aux != NULL){
                            
                            aux = aux->next;
                        }
                    }
                }
            }
        }
    }
}

/*******************************************************************************
 * graph_building ()
 *
 * Arguments: tabela - Our table (Where we have all the words allocated)
 *            max_mutations - An array with the maximum mutations that 
 *                            we find for each size of a word.  
 *            max_length - The biggest word in the dictionary.
 *            graph_array - The array of graphs.      
 *            num_words - An array with the number of words of each size.  
 * 
 * Returns: an array of graphs.
 *
 * Description: Creates all the graphs needed in the project.
 *****************************************************************************/
Graph** graph_building(char*** tabela, int* max_mutations, int max_length, Graph** graph_array, int* num_words){
    
    int num_de_mudancas = 0;
    register int i,j,k,z;

    for(i=0; i<max_length; i++)
    {    

        if(max_mutations[i] != 0 && num_words[i]!=0)
        {   
            graph_array[i] = createAGraph(num_words[i]);

            for(j=0; j<num_words[i]-1; j++)
            {
                for(z=j; z<num_words[i]; z++)
                {
                    for(k=0; k<=i; k++)
                    {   
                        if(tabela[i][j][k] != tabela[i][z][k]){
                            
                            num_de_mudancas++;
                        }
                        if(num_de_mudancas > max_mutations[i]){
                            break;
                        }

                    }

                    if(num_de_mudancas <= max_mutations[i] && num_de_mudancas!=0){
                        
                        //printf("Vou adiconar vertice!\n");
                        addVertex(graph_array[i], j, z, tabela[i][j], tabela[i][z]);

                        // printf("Vou adicionar aresta\n");
                        addEdge_s_d(graph_array[i], j, z, num_de_mudancas, tabela[i][z]);
                        addEdge_d_s(graph_array[i], j, z, num_de_mudancas, tabela[i][j]);
                    }
                    num_de_mudancas=0;
        
                }
            }
        }
    }

    return graph_array;
}

/*******************************************************************************
 * recursive_print ()
 *
 * Arguments: vecotr_right_path - The vector where the ids will be in the right order
 *            st - An array of ids, used in djikstra
 *            last_index - The id of the destiny of the path.
 *            flag_path - Check if exists a path.
 *            i - An index.   
 * 
 * Returns: an array with a path.
 *
 * Description: Creates an array with the right path.
 *****************************************************************************/
int recursive_print(int *vector_rigth_path, int *st, int last_index, int flag_path, int i){

    if(st[last_index] != -2)
    {
        if(st[last_index] != -1)
        {
            if(i==0){
                vector_rigth_path[i] = last_index;
                vector_rigth_path[i+1] = st[last_index];
            }
            else{
                vector_rigth_path[i+1] = st[last_index];
            }

            i++;
            recursive_print(vector_rigth_path, st, st[last_index], 0, i);
        }
    }
    else if(st[last_index] == -2){
        return 1;
    }

    return 0;
}

/*******************************************************************************
 * recursive_count_vertices ()
 *
 * Arguments: st - An array with the indexs.
 *            last_index - The index of the end of the path.
 *            flag_path - Check if exists a path.      
 *            counter - The number of vertexs.  
 * 
 * Returns: the number of vertexs.
 *
 * Description: Counts the number of vertexs of a given problem.
 *****************************************************************************/
int recursive_count_vertices(int *st, int last_index, int flag_path, int counter){

    if(st[last_index] != -2)
    {
        if(st[last_index] != -1)
        {   
            counter++;
            counter = recursive_count_vertices(st, st[last_index], 0, counter);
        }
    }
    else if(st[last_index] == -2){
        return -1;
    }

    return counter;
}

/*******************************************************************************
 * free_graph ()
 *
 * Arguments: graph - A graph.
 * 
 * Returns: (void).
 *
 * Description: frees all the memory allocated in the graph.
 *****************************************************************************/
void free_graph(Graph* graph)
{
    int i;

    for (i = 0; i < graph->numVertices; i++) 
    {
        freeLinkedList(graph->adjLists[i]);
    }
    free(graph->adjLists);
    free(graph);
}

/*******************************************************************************
 * freeLinkedList ()
 *
 * Arguments: first - The first word to free.
 * 
 * Returns: (void).
 *
 * Description: frees the memory allocated in the adjacency lists.
 *****************************************************************************/
void freeLinkedList(Node* first)
{
    Node *aux,*next;
    for (aux = first; aux != NULL; aux = next)
    {
        next = aux->next;
        free(aux);
    }
}

/*******************************************************************************
 * fase2 ()
 *
 * Arguments: str1 - The first parameter in the command line.
 *            str2 - The second parameter in the command line.
 * 
 * Returns: (void).
 *
 * Description: Performs the main funcion in phase 2.
 *****************************************************************************/
void fase2(char str1[], char str2[])
{

    FILE *fptr1, *fptr2, *fp_Out;
    Graph **graph_array = NULL;
    
    int num_de_mudancas=0;
    register int k;
    int flag_path;
    char *filename;
    int first_line;
    int namesize1=strlen(str1), namesize2=strlen(str2);
    register int i, j;
    int count_words = 0, pos=-1, max_length = 0;
    int **st = NULL, **wt = NULL;
    int *num_words, *num_restante, *num_problems, *max_mutations;
    int *flag_graph;
    char word_test[100], word_test2[100];
    int mutations = 0;
    char word1[100], word2[100];
    char **array_of_words;
    char ***tabela;
    int position_word[2];
    int *vector_right_path = NULL;
    int count_vertices_right_path = 1; 

    // Verifica a validade do primeiro ficheiro.
    if (str1[namesize1-1]!='t' || str1[namesize1-2]!='c' || str1[namesize1-3]!='i' || str1[namesize1-4]!='d' || str1[namesize1-5]!='.'){       
        exit(0);
    }

    // Verifica a validade do segundo ficheiro.
    if (str2[namesize2-1]!='s' || str2[namesize2-2]!='l' || str2[namesize2-3]!='a' || str2[namesize2-4]!='p' ||str2[namesize2-5]!='.'){      
        exit(0);
    }

    /* Aloca memória para o nome do ficheiro de saída, ou seja, temos de passar de ".pals" para ".stats".
      "namesize + 2" para alocar a memória de mais uma letra e o '\0'.*/
    filename = (char*) malloc(sizeof(char)*(namesize2+2));
    if (filename==NULL){
        exit(0);
    }
    
    //inicialização do nome do ficheiro.
    for (j = 0; j < (namesize2+2); j++)
    {
        filename[j]='\0';
    }

    //Passar o nome do ficheiro de entrada para o ficheiro de saída.
    strcpy(filename,str2);

    //Colocar a respetiva extensão da fase final.
    filename[namesize2]='s';
    filename[namesize2-1]='h';
    filename[namesize2-2]='t';
    filename[namesize2-3]='a'; 
    filename[namesize2-4]='p'; 

    if ((fptr1 = fopen(str1, "r")) == NULL)
    {
        free(filename);
        exit(0);
    }

    if ((fptr2 = fopen(str2, "r")) == NULL)
    {
        free(filename);
        fclose(fptr1);
        exit(0);
    }

    if ((fp_Out = fopen(filename, "w")) == NULL)
    {
        free(filename);
        fclose(fptr1);
        fclose(fptr2);
        exit(0);
    }

    free(filename);

    while(fscanf(fptr1, "%s", word_test) != EOF)
    {
        // numero de palavras que existe no file dict
        count_words++;
        // Descobrir o a palavra com o máximo de caractéres
        if(strlen(word_test) > max_length){
            max_length = strlen(word_test);
        }
    }

    //If the dictionary is empty.
    if(max_length == 0){

        while(fscanf(fptr2, "%s %s %d", word1, word2, &mutations) != EOF)
        {
            fprintf(fp_Out, "%s %d\n", word1, -1);
            fprintf(fp_Out, "%s\n\n", word2);
        }

        free(filename);
        fclose(fptr1);
        fclose(fptr2);
        fclose(fp_Out);
        exit(0);
    }

    fclose(fptr1);

    if ((fptr1 = fopen(str1, "r")) == NULL)
    {
        free(filename);
        fclose(fptr2);
        fclose(fp_Out);
        exit(0);
    }

    array_of_words = (char**)malloc(count_words * sizeof(char*));
   
    //Caso esteja mal alocado não vale a pena continuar, (n sei se n temos de dar free de outra forma...)
    if (array_of_words==NULL)
    {
        free(filename);
        fclose(fp_Out);
        fclose(fptr1);
        fclose(fptr2);
        exit(0);
    }

    for(k=0; k<count_words; k++){

        array_of_words[k] = (char*)malloc((max_length+1) * sizeof(char));  //Por causa do '\0'.

    }

    num_words = (int*)calloc((max_length), sizeof(int));

    while(fscanf(fptr1, "%s", word_test2) != EOF)
    {
        num_words[strlen(word_test2)-1] ++;
        pos++;
        strcpy(array_of_words[pos], word_test2);

    }      

    //Allocates the table.
    tabela = (char***)malloc((max_length) * sizeof(char**));

    for(i=0; i<max_length; i++){

        tabela[i] = (char**)malloc((num_words[i]) * sizeof(char*));

        for(j=0; j<num_words[i]; j++){

            tabela[i][j] = (char*)malloc((i+2) * sizeof(char)); //Por causa do /0
        }

    }

    num_restante = (int*)calloc((max_length), sizeof(int));

    for(i=0; i<max_length; i++){
        num_restante[i] = num_words[i];
    }

    for(i=0; i<count_words; i++){

        strcpy(tabela[strlen(array_of_words[i]) - 1][num_words[strlen(array_of_words[i]) - 1]-num_restante[strlen(array_of_words[i]) - 1]], array_of_words[i]);

        num_restante[strlen(array_of_words[i]) - 1]--;
    }

    free_function(array_of_words, count_words);

    max_mutations = (int*)calloc(max_length, sizeof(int));
    num_problems = (int*)calloc(max_length, sizeof(int));
    flag_graph = (int*)calloc(max_length, sizeof(int));

    for(i=0; i<max_length; i++){

        if(num_words[i] != 0){

            Quick_Sort(tabela[i], 0, num_words[i]-1);
        }
    }

    while (fscanf(fptr2, "%s %s %d", word1, word2, &mutations) != EOF){

        /* Checks the max_mutations and the number of problems to just do the graphs that we want*/

        num_de_mudancas = 0;

        if(mutations <= 0){
            continue;
        }

        if(strlen(word1) != strlen(word2))
            continue;

        if(strlen(word1) > max_length)
        {
            continue;
        }
        if(strcmp(word1, word2) == 0){

            continue;
        }
        if(num_words[strlen(word1) - 1] == 0){

            continue;
        } 
        mode1_2(tabela, word1, word2, position_word, num_words);
        
        if(position_word[0] == -1 || position_word[1] == -1){
            continue;
        }

        for(k=0; k<=strlen(word1); k++)
        {   
            if(word1[k] != word2[k]){
                
                num_de_mudancas++;
            }
            if(num_de_mudancas > 1){
                break;
            }
        }
        
        if(strlen(word1) == strlen(word2) && mutations<strlen(word1)){

            if(num_de_mudancas == 1 && mutations >= 1){
                
                num_problems[strlen(word1)-1] ++;
                max_mutations[strlen(word1)-1] = 1;
                continue;
            }
            if(max_mutations[strlen(word1)-1] == 0){
                
                num_problems[strlen(word1)-1] ++;
                max_mutations[strlen(word1)-1] = mutations;
                continue;
            }
            else if(max_mutations[strlen(word1)-1] < mutations){
               
                num_problems[strlen(word1)-1] ++;
                max_mutations[strlen(word1)-1] = mutations;
                continue;
            }
            else if(max_mutations[strlen(word1)-1] == strlen(word1)){
                
                num_problems[strlen(word1)-1] ++;
                max_mutations[strlen(word1)-1] = mutations;
                continue;
            }
        }
        else if( max_mutations[strlen(word1)-1] == 0){

            if(num_de_mudancas == 1 && mutations >= 1){
                
                num_problems[strlen(word1)-1] ++;
                max_mutations[strlen(word1)-1] = 1;
                continue;
            }
            else{
                num_problems[strlen(word1)-1]++;
                max_mutations[strlen(word1)-1] = strlen(word1);
                continue;
            }
        }

        num_problems[strlen(word1)-1]++;
    }

    graph_array = (Graph **)malloc((max_length) * sizeof(Graph*));
    st = (int**)malloc((max_length) * sizeof(int*));
    wt = (int**)malloc((max_length) * sizeof(int*));
    
    fclose(fptr2);


    if ((fptr2 = fopen(str2, "r")) == NULL)
    {
        free(filename);
        free(num_words);
        free(num_restante);
        free(max_mutations);
        free(num_problems);
        free(flag_graph);
        free_function(array_of_words, count_words);
        free_table(tabela, max_length, num_words);
        fclose(fptr1);
        exit(0);
    }

    // Where we built our graphs. 
    graph_building(tabela, max_mutations, max_length, graph_array, num_words);

    free(max_mutations);

    while (fscanf(fptr2, "%s %s %d", word1, word2, &mutations) != EOF)
    {
        num_de_mudancas = 0;
        count_vertices_right_path = 1;

                                        /*Exceptions*/

        //If the words doesn't have the same size, the program has already the solution and move on.
        if(strlen(word1) != strlen(word2))
        {
            fprintf(fp_Out, "%s %d\n", word1, -1);
            fprintf(fp_Out, "%s\n\n", word2);
            continue;
        }

        //If the word has bigger than the words presented in the dictionary, the program has already the solution and move on.
        if(strlen(word1) > max_length)
        {
            fprintf(fp_Out, "%s %d\n", word1, -1);
            fprintf(fp_Out, "%s\n\n", word2);
            continue;
        }

        //If the mutations are lower or equal at this point, the program has already the solution and move on.
        if(mutations < 0)
        {
            fprintf(fp_Out, "%s %d\n", word1, -1);
            fprintf(fp_Out, "%s\n\n", word2);
            continue;
        }

        //Find the index for both words to check if they are in the dictionary.
        mode1_2(tabela, word1, word2, position_word, num_words);

        //If one of the two words is not presented in the dictionary, the program has already the solution and move on.
        if(position_word[0] == -1 || position_word[1] == -1){

            fprintf(fp_Out, "%s %d\n", word1, -1);
            fprintf(fp_Out, "%s\n\n", word2);
            continue;
        }

        //If the words are equal, the program has already the solution and move on.
        if(strcmp(word1, word2) == 0){

            if(mutations >= 0){

                fprintf(fp_Out, "%s %d\n", word1, 0);
                fprintf(fp_Out, "%s\n\n", word2);
                continue;
            }
            else{
                fprintf(fp_Out, "%s %d\n", word1, -1);
                fprintf(fp_Out, "%s\n\n", word2);
                continue;
            }
        }

        //If the number of words of the word that we are checking in this problem are empty, the program has already the solution and move on.
        if(num_words[strlen(word1) - 1] == 0){

            fprintf(fp_Out, "%s %d\n", word1, -1);
            fprintf(fp_Out, "%s\n\n", word2);
            continue;
        } 

        for(k=0; k<strlen(word1); k++)
        {   
            if(word1[k] != word2[k]){
                
                num_de_mudancas++;
            }
            if(num_de_mudancas > 1){
                break;
            }
        }

        //If between two words the difference is one, the program has already the solution and move on.
        if(num_de_mudancas == 1){

            fprintf(fp_Out, "%s %d\n", word1, 1);
            fprintf(fp_Out, "%s\n\n", word2);
        }
        
                                     /* End of exceptions*/

        //A flag used to allocate memory for the vectors st and wt just one time for each size of a word, used in the djikstra
        if(flag_graph[strlen(word1) - 1] == 0)
        {
            st[strlen(word1) - 1] = (int *) malloc((graph_array[strlen(word1)-1]->numVertices) * sizeof(int*));
            if (st[strlen(word1) - 1] == NULL)
            {
                free(num_words);
                free(num_restante);
                free(num_problems);
                free_table(tabela, max_length, num_words);
                fclose(fptr1);
                fclose(fptr2);
                fclose(fp_Out);
                exit(0);
            }

            wt[strlen(word1) - 1] = (int *) malloc((graph_array[strlen(word1)-1]->numVertices) * sizeof(int));
            if (wt[strlen(word1) - 1] == NULL)
            {
                free(num_words);
                free(num_restante);
                free(num_problems);
                free_table(tabela, max_length, num_words);
                fclose(fptr1);
                fclose(fptr2);
                fclose(fp_Out);
                exit(0);
            }

            flag_graph[strlen(word1) - 1] = 1;
        }

        
        //print_graphs(graph_array, max_length, max_mutations);

        if(num_de_mudancas != 1){

            //Djikstra
            Djikstra(graph_array[strlen(word1) - 1], wt[strlen(word1) - 1], st[strlen(word1) - 1], position_word[0], mutations);

            //We store the number of vertices of each path here.
            count_vertices_right_path = recursive_count_vertices(st[strlen(word1)-1], position_word[1], 0, count_vertices_right_path);
            if(count_vertices_right_path != -1)
            {
                vector_right_path = (int*)calloc(count_vertices_right_path,sizeof(int));

                i=0;
                flag_path = recursive_print(vector_right_path, st[strlen(word1)-1], position_word[1], 0, i);

                //If we found the path.
                if(flag_path != 1)
                {
                                        /*Answering the problems of the 1st pahse*/

                    first_line = 0;
                    for(i = (count_vertices_right_path-1); i >= 0; i--){

                        if(first_line == 0)
                        {
                            //The 1st line of the path.
                            fprintf(fp_Out, "%s %d\n", graph_array[strlen(word1)-1]->adjLists[vector_right_path[i]]->word, wt[strlen(word1)-1][position_word[1]]);
                            
                            first_line = 1;
                        }
                        else{
                            //The other lines.
                            fprintf(fp_Out, "%s\n", graph_array[strlen(word1)-1]->adjLists[vector_right_path[i]]->word);
                        }

                    }
                    fprintf(fp_Out, "\n");
                }
            }
            else{ //there is no path
                fprintf(fp_Out, "%s %d\n", word1, -1);
                fprintf(fp_Out, "%s\n\n", word2);
            }
        }
        
        //If this conditions is true, it means that the graphs and the vectors st,wt are no longer needed and we can now free them.
        num_problems[strlen(word1) - 1] --;

        //If there are no more problems of a certain size, we can free some things.
        if(num_problems[strlen(word1) - 1] == 0)
        {
            free(st[strlen(word1) - 1]);
            free(wt[strlen(word1) - 1]);
            free_graph(graph_array[strlen(word1) - 1]); 
        }
        if(count_vertices_right_path != -1 && num_de_mudancas != 1){

            free(vector_right_path);
        }
    }   

                                /*Freeing the memory*/

    free_table(tabela, max_length, num_words);
    free(num_restante);
    free(num_problems);
    free(flag_graph);
    free(num_words);
    free(st);
    free(wt);
    free(graph_array);
    fclose(fptr1);
    fclose(fptr2);
    fclose(fp_Out);

}       
