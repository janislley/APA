#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

struct bucket_s{
	unsigned int qtd_num;
	std::vector<std::string> words;
}typedef bucket_s;

struct bucket_n{
	unsigned int qtd_num;
	std::vector<long int> numbers;
}typedef bucket_n;

inline unsigned long int map(const long int x, const long int in_min, const long int in_max, const long int out_min, const long int out_max)
{
	return (unsigned long int)((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

inline unsigned int map(char c){
	if(c >= 'a'){
		c -= 'a';
		return c;
	}
	else{
		return c - 'A';
	}
}

inline void swap(long int *valueR, long int *valueL)
{
    long int temp = *valueR;
    *valueR = *valueL;
    *valueL = temp;
}

inline long int getMin(std::vector<long int>& values, const unsigned int size)
{
	long int min = values[0];
	for(unsigned int i = 1; i < size; i++)
		if(values[i] < min)
			min = values[i];
	return min;
}

// A utility function to get maximum value in values[]
inline long int getMax(std::vector<long int>& values, const unsigned int size)
{
    long int mx = values[0];
    for (unsigned int i = 1; i < size; i++)
        if (values[i] > mx)
            mx = values[i];
    return mx;
}

inline unsigned int getMax(std::vector<std::string>&values, const unsigned int size){
	unsigned int max = 0;
	for (unsigned int i = 0; i < size; i++){
		if(values[i].length() > max){
			max = values[i].length();
		}	
	}
	return max;
}

void heapify(std::vector<long int>& values,unsigned int size, unsigned int i)
{
    unsigned long int largest = i;  // Initialize largest as root
    unsigned long int l = 2*i + 1;  // left = 2*i + 1
    unsigned long int r = 2*i + 2;  // right = 2*i + 2
 
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
        swap(&values[i], &values[largest]); // troca a posicao dos elementos
 
        // Função heapify recursiva para as sub-arvores
        heapify(values, size, largest);
    }
}

// Função de implementação do algoritmo heap sort
void Heap_Sort(std::vector<long int>& values, unsigned int size)
{
    // Carrega o heap (rearranja o array)
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(values, size, i);
 
	// Um por um extrai um elemento do heap
    for (int i = size - 1; i >= 0; i--)
    {
		// Move a raiz atual para o
        swap(&values[0], &values[i]); 
		// chamada o max heapify sobre o heapify reduzido
        heapify(values, i, 0);
    }
} 
 

void countSort(std::vector<long int>& values, int size, int exp)
{
    long int output[size]; // output array
    int i;
    long int count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < size; i++)
        count[ (values[i]/exp)%10 ]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = size - 1; i >= 0; i--)
    {
        output[count[ (values[i]/exp)%10 ] - 1] = values[i];
        count[ (values[i]/exp)%10 ]--;
    } 
    // Copy the output array to values[], so that values[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < size; i++){
		values[i] = output[i];
	}
}

void countSort(std::vector<std::string>& values, int size, int exp)
{
    std::vector<std::string> output(size); // output array
    int i;
    int count[26] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < size; i++){
        try{
	        //std::cout << "I: " << i << " : " << values[i] << std::endl;
        	//std::cout << values[i].at(exp) <<std::endl;
        	count[map(values[i].at(exp))]++;
        }
        catch(const std::out_of_range& oor){
        	//std::cout << "Exception I: " << i << " : " << values[i] << std::endl;
        	count[0]++;
        }
	}	
	
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    
    for (i = 1; i < 26; i++){
        count[i] += count[i - 1];
	}
	
    // Build the output array
    for (i = size - 1; i >= 0; i--){
    	try{
        	output[count[map(values[i].at(exp))] -1 ] = values[i];
        	count[map(values[i].at(exp))]--;
        }
        catch(const std::out_of_range& oor){
        	//std::cout << "Exception I: " << i << " : " << values[i] << std::endl;
        	output[count[0] -1 ] = values[i];
        	count[0]--;
        }
        
    }
    // Copy the output array to values[], so that values[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < size; i++){
		values[i] = output[i];
	}
}

void Radix_Sort(std::vector<std::string>& values, unsigned int size)
{

	//unsigned int x = 0;
	//unsigned int n_size = 0;
	unsigned int max = getMax(values, size);
    // Find the maximum number to know number of digits
    //printf("Max: %d\n", max);
	for (unsigned int exp = max; exp > 0; exp--){
		countSort(values, size, exp);
	}
}


void Radix_Sort(std::vector<long int>& values, unsigned int size)
{

	unsigned long int x = 0;
	unsigned long int n_size = 0;
	
    // Find the maximum number to know number of digits

    long int min = getMin(values, size);
	long int max = getMax(values, size);
	std::vector<long int> n_values;
	
	if(min < 0)
	{
		
		while (x != size)
		{
			if (values[x] < 0)
			{
				n_values.push_back(-values[x]);					
				values.erase(values.begin()+x);
				x--;				
				size--;
				n_size++;
			}
			x++; 
		}

		// Vector with negatives numbers
		long int n_max = getMax(n_values, n_size);
		
		// Sort negative numbers
		for (int exp = 1; n_max/exp > 0; exp *= 10)
        	countSort(n_values, n_size, exp);

		// Sort positives numbers
		for (int exp = 1; max/exp > 0; exp *= 10)
        	countSort(values, size, exp);
		

		// Put negatives and positives together
		for (unsigned int i = 0 ; i < n_size; i++){
			values.insert(values.begin(), -n_values[i]);
			size++;
		}
 	}
	else{
	
		for (int exp = 1; max/exp > 0; exp *= 10){
        	countSort(values, size, exp);
        }
	}
}
 

void Bucket_Sort (std::vector<std::string> &values, int size)
{
	
    // 1) Create n empty buckets
	unsigned int bucket_qtde = 26;
    std::vector<bucket_s> buckets(bucket_qtde);
	//int in_min = getMin(values, size);
	//int in_max = getMax(values, size);

    // 2) Put array elements in different buckets
    for (int i = 0; i < size; i++)
    {
		unsigned int index = map(values[i].at(0));
		buckets[index].words.push_back(values[i]);
		buckets[index].qtd_num++;
    }
    // 3) Sort individual buckets
    for (unsigned int i = 0; i < bucket_qtde; i++){
			Radix_Sort(buckets[i].words, buckets[i].qtd_num);		
	}
	
	for (unsigned int i = 0; i < bucket_qtde; i++){
		for (unsigned int j = 0; j < buckets[i].qtd_num; j++){
			std::cout << "S: "<< buckets[i].words[j] << std::endl;
    	}
    }
    
	
}

void Bucket_Sort (std::vector<long int>& values, unsigned int size)
{
    // 1) Create n empty buckets
	unsigned int bucket_qtde = (int)(size/8);
    std::vector<bucket_n> buckets(bucket_qtde);
    long int in_min = getMin(values, size);
	long int in_max = getMax(values, size);
	
	
	/* NAO MEXA AQUI NAO MEXA AQUI */
    // 2) Put array elements in different buckets
    for (unsigned int i = 0; i < size; i++)
    {
		unsigned int bi = map(values[i], in_min, in_max, 0, bucket_qtde-1); // Index in bucket
		buckets[bi].numbers.push_back(values[i]);
		buckets[bi].qtd_num++;
    }
	 
    // 3) Sort individual buckets
    
    for (unsigned int i = 0; i < bucket_qtde; i++){
		if(buckets[i].qtd_num > 0){
			if(buckets[i].numbers[0] >= 100000 || buckets[i].numbers[0] <= -100000){
				Heap_Sort(buckets[i].numbers, buckets[i].qtd_num);
			}
			else {
				Radix_Sort(buckets[i].numbers, buckets[i].qtd_num);		
			}
		}	
	}
	for (unsigned int i = 0; i < bucket_qtde; i++){
    	for (unsigned int j = 0; j < buckets[i].qtd_num; j++){
    		std::cout <<  buckets[i].numbers[j] << std::endl;
    	}
    }	
}

int main(){
	unsigned int size = 0;
	long int value_n = 0;
	std::string value_s;
	
	bool check = false;
	
	std::vector<long int> n_values;
	std::vector<std::string> s_values;
	
	std::cin >> size;
	std::cin >> value_n;
	check = std::cin.fail();
	std::cin.clear();
	
	if(!check){
		n_values.push_back(value_n);
	}

	while(true){
		if (check){
			std::getline(std::cin, value_s);
			if (std::cin.eof()){
				break;
			}
			s_values.push_back(value_s);
		}
		else{
			if(std::cin >> value_n){
				n_values.push_back(value_n);
			}
			else{
				break;
			}
		}
		
	}

	if (check){ // string
		Bucket_Sort(s_values, size);
	
	}
	else{
		Bucket_Sort(n_values, size);
	}
		
	return 0;

}

