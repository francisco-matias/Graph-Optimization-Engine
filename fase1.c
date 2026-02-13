#include "Proj.h"

/*******************************************************************************
 * binary_search ()
 *
 * Arguments: sorted_array - A sorted array in which we want to find the word
 *            word - The word we want to find
 *            result - number of elements in the vector with the size of the word  
 * 
 * Returns: The position of the word in the sorted array.
 *
 * Description: Searchs for the word we want to find.
 *****************************************************************************/
int binary_search(char** sorted_array, char* word, int result)
{
    //Implementação de um algoritmo de procura para vetores ordenados. 
    int begin, mid, end;
    
    begin = 0;
    end = result - 1;

    while(begin<=end)
    {
        mid = (begin + end) / 2;
        //Se tivermos com sorte fica O(1).
        if (strcmp(word,sorted_array[mid])==0)
        {
            //printf("key found at the position %d\n",mid+1);
            return mid;
        }
        else if(strcmp(word,sorted_array[mid])>0) 
            begin=mid+1;
        else
            end=mid-1;
    }
    
    return -1;//N ta no dicionário!!
}

/*******************************************************************************
 * less ()
 *
 * Arguments: a - The first string to check.
 *            b - The second string to check.
 * 
 * Returns: 1 if the string "a" is less than the string "b".
 *
 * Description: Verifies if the string "a" is less than the string "b" 
 *****************************************************************************/
int less(char *a, char *b)
{   
    register int k;

    if(strlen(a) == strlen(b))
    {
        if(strcmp(a,b) == 0){
            return 0;
        }
        else{
            for(k = 0; a[k] != '\0' && b[k] != '\0'; k++)
            {
                if(a[k] != b[k] && a[k] < b[k])
                {
                    return 1;
                }
                else if(a[k] > b[k]){
                    return 0;
                }
            }
        }
    }
    return 0;
}

/*******************************************************************************
 * exchange ()
 *
 * Arguments: a - 1st object we want to exchange
 *            b - 2nd oject we want to exchange
 * 
 * Returns: (void)
 *
 * Description: switch items
 *****************************************************************************/
void exchange(char *a, char *b)
{

    char aux[strlen(a)+1];
    
    strcpy(aux, a);
    strcpy(a, b);
    strcpy(b, aux);
}

/*****************************************************************************
 * partition ()
 *
 * Arguments: 
 *            array - table of items to sort
 *            left, right - limits on table to consider
 *            less - item comparison function
 * 
 * Returns: (void)
 *
 * Description: Used to sort the array.
 *****************************************************************************/
int partition_function(char **array, int left, int right){
    int i=0, j=0;
    char *v = array[right];

    i = left - 1; j = right; 
    for (;;)
    {
        //Enquanto estiver a retornar maior que 0 continuamos, quando for 0 pára!   
        while (less(array[++i], v)) ;
        while (less(v, array[--j]))
        {   
            if (j == left) break;
        }
        if (i >= j)
        {
            break;
        }
        if(strcmp(array[i], array[j]) != 0){
            exchange(array[i], array[j]);
        }
    }
    
    if(strcmp(array[i], array[right]) != 0){
        exchange(array[i], array[right]);
    }

    return i;
}

/*******************************************************************************
 * Quick_Sort ()
 *
 * Arguments: array - A vector of strings that we want to sort.
 *            left - The left limit of the array.
 *            right - The right limit of the array. 
 * 
 * Returns: (void)
 *
 * Description: Sorts an array of strings.
 *****************************************************************************/
void Quick_Sort(char **array, int left, int right){
    
    int i=0; 
    
    if (right <= left) return;
    i = partition_function(array, left, right);

    Quick_Sort(array, left, i-1);
    Quick_Sort(array, i+1, right);

}

/*******************************************************************************
 * mode1_2 ()
 *
 * Arguments: tabela - A table where we keep our words organized.
 *            word1 - The 1st word of the problem.
 *            word2 - The 2nd word of the problem.
 *            poition - A vector with 2 positions where we keep the ids of the two words.    
 *            num_words - Number of elements in the vector with the size of the word  
 * 
 * Returns: (void).
 *
 * Description: Used in mode1 and mode 2 to verify conditions.
 *****************************************************************************/
void mode1_2(char ***tabela, char *word1, char *word2, int *position, int *num_words)
{   
    int tamanho = strlen(word1);   

    position[0] = binary_search(tabela[tamanho-1], word1, num_words[tamanho-1]);
    position[1] = binary_search(tabela[tamanho-1], word2, num_words[tamanho-1]);

}

/*******************************************************************************
 * free_function ()
 *
 * Arguments: array - A vector of strings that we want to free.
 *            length - Number of words in the dictionary.
 * 
 * Returns: (void).
 *
 * Description: frees the whole array.
 *****************************************************************************/
void free_function(char **array, int length){

    int i;

    for(i=0; i<length; i++){ //Por causa do '\0'...
        free(array[i]);
    }

    free(array);
}

/*******************************************************************************
 * free_table ()
 *
 * Arguments: tabela - To free our table.
 *            max_length - The size of the biggest word in the dictionary.
 *            num_words - The number of words in the array with the same size of our word.  
 * 
 * Returns: (void).
 *
 * Description: frees the whole table.
 *****************************************************************************/
void free_table(char ***tabela, int max_length, int *num_words){

    register int i,j;

    for(i=0; i<max_length; i++){

        for(j=0; j<num_words[i]; j++){
            
            free(tabela[i][j]);
        }

        free(tabela[i]);
    }
    free(tabela);
}

/*******************************************************************************
 * fase1 ()
 *
 * Arguments: str1 - The first parameter in the command line.
 *            str2 - The second parameter in the command line.
 * 
 * Returns: (void).
 *
 * Description: Performs the main funcion in phase 1.
 *****************************************************************************/
void fase1(char str1[], char str2[])
{
    FILE *fptr1, *fptr2, *fp_Out;
    char *filename;
    int namesize1=strlen(str1), namesize2=strlen(str2);
    int j;

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

    //Colocar a respetiva extensão.
    filename[namesize2]='s';
    filename[namesize2-1]='t';
    filename[namesize2-2]='a';
    filename[namesize2-3]='t'; 
    filename[namesize2-4]='s'; 

    char word_test[100], word_test2[100];
    char word1[100], word2[100];
    int command = 0;     
    int count_words = 0, pos=-1;
    char **array_of_words;
    int *num_words, *num_restante;
    int position_word[2], *flag_word; 
    int i;
    int max_length=0;
    char ***tabela;

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

    while(fscanf(fptr1, "%s", word_test) != EOF)
    {
        // numero de palavras que existe no file dict
        count_words++;
        // Descobrir o a palavra com o máximo de caractéres
        if(strlen(word_test) > max_length){
            max_length = strlen(word_test);
        }
    }

    //If the dictionary is empty the program has already the
    if(max_length == 0){

        while(fscanf(fptr2, "%s %s %d", word1, word2, &command) != EOF){

            if(strlen(word1) != strlen(word2))
            {
                fprintf(fp_Out, "%s %s %d\n\n", word1, word2, command);
                //Passamos para o próximo problema...
                continue;
            }

            else if(command == 2 || command == 1){
                fprintf(fp_Out, "%s %s %d\n\n", word1, word2, command);
            }
            else{
                //Se o comando não for nem 1 nem 2, tbm não queremos...
                fprintf(fp_Out, "%s %s %d\n\n", word1, word2, command); 
            }

        }
        free(filename);
        fclose(fptr1);
        fclose(fptr2);
        fclose(fp_Out);
        exit(0);
    }
    
    flag_word = (int*)malloc((max_length) * sizeof(int));
    
    fclose(fptr1);

    if ((fptr1 = fopen(str1, "r")) == NULL)
    {
        free(filename);
        exit(0);
    }

    array_of_words = (char**)malloc(count_words * sizeof(char*)); //Memória alocada

    if (array_of_words==NULL)
    {
        free(filename);
        free(flag_word);
        fclose(fp_Out);
        fclose(fptr1);
        fclose(fptr2);
        exit(0);
    }

    for(int k=0; k<count_words; k++){

        array_of_words[k] = (char*)malloc((max_length+1) * sizeof(char));  //Por causa do '\0'.

    }

    num_words = (int*)malloc((max_length)* sizeof(int));

    for(i=0; i<max_length; i++){ 
        flag_word[i] = 0;
        num_words[i] = 0;
    }

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

    //A vector needed to calculate the position of the word in the table.
    num_restante = (int*)calloc((max_length), sizeof(int));

    for(i=0; i<max_length; i++){
        num_restante[i] = num_words[i];
    }

    //We put all words presented in the dictionary in the table.
    for(i=0; i<count_words; i++){

        strcpy(tabela[strlen(array_of_words[i]) - 1][num_words[strlen(array_of_words[i]) - 1]-num_restante[strlen(array_of_words[i]) - 1]], array_of_words[i]);

        //The next word will have a different position, so we have to decrement.
        num_restante[strlen(array_of_words[i]) - 1]--;
    }

    while(fscanf(fptr2, "%s %s %d", word1, word2, &command) != EOF){
        
                                /*Exceptions*/

        //If the word has bigger than the words presented in the dictionary, the program has already the solution and move on.
        if(strlen(word1) > max_length)
        {
            fprintf(fp_Out, "%s %s %d\n\n", word1, word2, command);
            continue;
        }

        //If the words doesn't have the same size, the program has already the solution and move on.
        if(strlen(word1) != strlen(word2))
        {
            fprintf(fp_Out, "%s %s %d\n\n", word1, word2, command);
            //Passamos para o próximo problema...
            continue;
        }   

        //If the commands are either 1 or 2 and there is no words in the array, the program has already the solution and move on.
        if(num_words[strlen(word1) - 1] == 0 && (command ==1 || command == 2)){

            fprintf(fp_Out, "%s %s %d\n\n", word1, word2, command);
            continue;
        } 
        
                                    /* End of exceptions*/

        //A flag used to quick sort only one time every array of a specified word.
        if(flag_word[strlen(word1)-1] == 0)
        {
            Quick_Sort(tabela[strlen(word1) - 1], 0, num_words[strlen(word1) - 1] - 1);
            
            flag_word[strlen(word1)-1] = 1;
        }

        //Find the index for both words to check if they are in the dictionary.
        mode1_2(tabela, word1, word2, position_word, num_words);

                        
                        /*Answering the problems of the 1st pahse*/

        if(command == 1){
            if(position_word[0] == -1 || position_word[1] == -1)
                fprintf(fp_Out, "%s %s %d\n\n", word1, word2, command);
            else
                fprintf(fp_Out, "%s %d\n\n", word1, num_words[strlen(word1)-1]);    
        }  
        else if(command == 2){

            if(position_word[0] == -1 || position_word[1] == -1)
                fprintf(fp_Out, "%s %s %d\n\n", word1, word2, command); 
            else{
                fprintf(fp_Out, "%s %d\n", word1, position_word[0]);
                fprintf(fp_Out, "%s %d\n\n", word2, position_word[1]);
            }
        }
        else{
            //Se o comando não for nem 1 nem 2, tbm não queremos...
            fprintf(fp_Out, "%s %s %d\n\n", word1, word2, command); 
        }
    } 

    free_table(tabela, max_length, num_words); 
    free_function(array_of_words, count_words);
    free(flag_word);
    free(num_restante);
    free(num_words);
    fclose(fp_Out);
    fclose(fptr1);
    fclose(fptr2);
    free(filename);
}
