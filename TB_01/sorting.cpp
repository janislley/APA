/**
 * Date: 26/01/2017
 * @author Janislley Oliveira
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

//V_Size é o tamanho do vetor de valores para ser carregado na memoria
int V_Size;

// Declaração do ponteiro para o array de valores
int *values;

// Funções auxiliares e principais de ordenação
void swap(int *valueR, int *valueL);
void merge(int values[], int l, int m, int r);
int partition (int values[], int low, int high);
void heapify(int values[], int size, int i);
void Selection_Sort(int values[], int size);
void Insertion_Sort(int values[], int size);
void Merge_Sort(int values[], int l, int r);
void Quick_Sort(int values[], int low, int high);
void Heap_Sort(int values[], int size);

int main(int argc, char *argv[])
{
	int i, input, size;

    V_Size = 100; //Inicialização padrão
	i = 0;
	size = 0;

	//Alocação de memoria 
    values = (int*) malloc (V_Size * sizeof(int));

	// Técnica utilizada para capturar a sequencia de páginas da entrada 
	while(true)
	{
		input = scanf("%d", &values[i]); // Insere os valores a serem ordenados no array 

		// Condição de parada - Faz a leitura até o fim do arquivo 
		if (input == EOF)
                {
                        break;
                }
		i++;
		size = i; //determina o tamanho do array de valores 
	}

	//printf("%d", size);

	// Seleciona a opção escolhida do usuario
    if(!strcmp(argv[1], "1"))
    	Selection_Sort(values, size);
    if(!strcmp(argv[1], "2"))
		Insertion_Sort(values, size);
    if(!strcmp(argv[1], "3"))
		Merge_Sort(values, 0, size-1);
    if(!strcmp(argv[1], "4"))
		Quick_Sort(values, 0, size-1);
    if(!strcmp(argv[1], "5"))
		Heap_Sort(values, size);

	int j;

	//Print dos valores ordenados no arquivo de saida
    for (j = 0; j < size; j++)
       	printf("%d \n", values[j]);
    printf("\n");

	return 0;
}
 
// Troca de posição os valores no array para ordena-los
void swap(int *valueR, int *valueL)
{
    int temp = *valueR;
    *valueR = *valueL;
    *valueL = temp;
}

// Mistura dois subarrays de values[].
// Primeiro subarray é values[l..m]
// Segundo subarray é values[m+1..r]
void merge(int values[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* Cria um array temporario */
    int L[n1], R[n2];
 
    /* Copia os valores dos do array temporarrio para putros L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = values[l + i];
    for (j = 0; j < n2; j++)
        R[j] = values[m + 1+ j];
 
    /* Mistura o array temporraio com o array values[l..r]*/
    i = 0; // identificador para o primeiro subarray
    j = 0; // identificador para o segundo subarray
    k = l; // identificador para o subarray misturado
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            values[k] = L[i];
            i++;
        }
        else
        {
            values[k] = R[j];
            j++;
        }
        k++;
    }
 
	// Copia os elementos restantes de L[], se houver
    while (i < n1)
    {
        values[k] = L[i];
        i++;
        k++;
    }
 
	// Copia os elementos restantes de R[], se houver
    while (j < n2)
    {
        values[k] = R[j];
        j++;
        k++;
    }
}

int partition (int values[], int low, int high)
{
    int pivot = values[high];    // pivot
    int i = (low - 1); // indice do elemento menor
 
    for (int j = low; j <= high- 1; j++)
    {
	// Se o elemento atual for menor que
	// igual ao pivot
        if (values[j] <= pivot)
        {
            i++;    // incrementa o indice do elemento menor
            swap(&values[i], &values[j]);
        }
    }
    swap(&values[i + 1], &values[high]);
    return (i + 1);
}

// A função heapify tem como entrada um array e um indice i. Quando heapify eh chamada, ela assume que 
// as sub-arvores já satisfazem a propriedade de Heap, mas values[i] pode ser menor que seus filhos. 
// A função de heapify eh tornar a arvore com raiz em i um Heap.
void heapify(int values[], int size, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2
 
	// Seleciona o maior entre pai, filho esquerdo e filho direito
    // Se o filho da esquerda for maior que o pai
    if (l < size && values[l] > values[largest])
        largest = l;
 
    // Se o filho da direita for maior que o pai
    if (r < size && values[r] > values[largest])
        largest = r;
 
    // Se o maior não for o pai
    if (largest != i)
    {
        swap(values[i], values[largest]); // troca a posicao dos elementos
 
        // Função heapify recursiva para as sub-arvores
        heapify(values, size, largest);
    }
}
 
void Selection_Sort(int values[], int size)
{
    int i, j, min_idx;
 
	// Um por um eh movimento do subarray não ordenado
    for (i = 0; i < size-1; i++)
    {
		// Localiza o elemento mínimo no array não ordenado
        min_idx = i;
        for (j = i + 1; j < size; j++)
          if (values[j] < values[min_idx])
            min_idx = j;
 
		// Troque o elemento mínimo encontrado com o primeiro elemento
        swap(&values[min_idx], &values[i]);
    }
}

/* Função de ordenação usando o algoritmo insertion sort*/
void Insertion_Sort(int values[], int size)
{
   int i, key, j;
   for (i = 1; i < size; i++)
   {
       key = values[i];
       j = i-1;
 
		/* Mover elementos de values[0..i-1], que são
           maior que a key, para uma posição à frente
           da sua posição atual */
       while (j >= 0 && values[j] > key)
       {
           values[j+1] = values[j];
           j = j-1;
       }
       values[j+1] = key;
   }
}

/* L é para índice esquerdo e r é índice direito da
    Sub-array de valores a ser ordenado */
void Merge_Sort(int values[], int l, int r)
{
    if (l < r)
    {
	// Igual a (l + r) / 2, mas evita o estouro para
	// l grande e h
        int m = l+(r-l)/2;
 
		// Oodena primeira e segunda metades
        Merge_Sort(values, l, m);
        Merge_Sort(values, m+1, r);
 
        merge(values, l, m, r);
    }
}


/* A função principal que implementa o algoritmo QuickSort
   Values[] -> Array a ser ordenado,
   Low -> Índice inicial,
   high -> Índice final */
void Quick_Sort(int values[], int low, int high)
{
    if (low < high)
    {
        // Pi eh o índice de particionamento, values[p] é odenado para o lugar correto
        int pi = partition(values, low, high);
 
	// Separar os elementos antes
	// e após a partição
        Quick_Sort(values, low, pi - 1);
        Quick_Sort(values, pi + 1, high);
    }
}
 
// Função de implementação do algoritmo heap sort
void Heap_Sort(int values[], int size)
{
    // Carrega o heap (rearranja o array)
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(values, size, i);
 
	// Um por um extrai um elemento do heap
    for (int i = size - 1; i >= 0; i--)
    {
		// Move a raiz atual para o
        swap(values[0], values[i]);
 
		// chamada o max heapify sobre o heapify reduzido
        heapify(values, i, 0);
    }
}

void Heap_Sort()
{
}
/*
void PrintUsage(char* option)
{
    	std::cout << "----------------------------------------------------\n"
        << "Selection_Sort:\t" << option << " 1 <arquivo_entrada> <arquivo_saida>\n"
        << "Insertion_Sort:\t" << option << " 2 <arquivo_entrada> <arquivo_saida>\n"
        << "Merge_Sort:\t" << option << " 3 <arquivo_entrada> <arquivo_saida>\n"
        << "Quick_Sort:\t" << option << " 4 <arquivo_entrada> <arquivo_saida>\n"
        << "Heap_Sort:\t" << option << " 5 <arquivo_entrada> <arquivo_saida>\n"
	<< "----------------------------------------------------\n";
}
*/
