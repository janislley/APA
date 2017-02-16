 -----  Trabalho 04 de Algoritmos de Ordenação -----
		(Ordenação Heuristica)

Aluno: Janislley Oliveira - 11221571
       Renno Diniz - 11218774

Disciplina: APA

Compilação: g++ -O3 sort.cpp -o sort

Forma de entrada e saida:

./sort < num.100000.1.in > out.txt

1 Problema

Desenvolver um algoritmo de ordenação utilizando uma heurística seletora capaz de escolher o melhor algoritmo mais adequado para cada entrada apresentada, sendo as instâncias de entrada: números e String.

2 Descrição da solução

A partir dos algoritmos de ordenação implementados:

Selection Sort
Insertion Sort
Quick Sort
Merge Sort
Heap Sort
Bucket Sort
Counting Sort
Hadix Sort

Iremos implementar um algoritmo geral de ordenação que determina a forma de ordenação dos dados de acordo com as instâncias de entrada. Para isso, será considerado a complexidade da função de ordenação em termos de tempo de execução do algoritmo determinado pelas instruções executadas e espaço de memória utilizado. 


2.1 Valores numéricos

Para as instâncias numéricas, percebemos que a quantidade de números é um fator crítico para a ordenação dos dados. À medida que o volume de dados aumenta, o processo de ordenação se torna lento. Com isso, se torna viável utilizar o algoritmo de Bucket Sort para uma pré-ordenação. Para a ordenação nos buckets, a escolha será feita dependendo da média da quantidade de algarismos nos números desse bucket. Para o caso com poucos algarismos, decidimos utilizar o Hadix. Para valores com demasiados algarismos, o Hadix se torna inviável, viabilizando o uso algoritmos de comparação, neste caso o Heap Sort. A ordenação pelo Bucket Sort tenderá para um tempo quadrático quando o tamanho das instâncias crescerem exponencialmente. 
A heurística que será usada nesse projeto consiste em analisar a quantidade de algarismos das instâncias de entrada à serem ordenadas. À medida que for maior, será usado outro algoritmo para prosseguir com a ordenação. Segue então a lógica do procedimento:


Bucket + Hadix sort: Será usado para instâncias com poucos algarismos, no máximo até 5. 
Bucket + Heap sort: Será usado quando as instâncias tem muitos algarismos. 


2.2 Strings

Tendo em vista que a língua portuguesa tem em média 4.64 letras por palavra, decidimos utilizar para ordenação de dados do tipo string o bucket Sort composto com hadix sort. Criaremos um total de 25 buckets, um para cada letra do alfabeto (A - Z) e a ordenação desses buckets, será feita utilizando o Hadix Sort. Em mais detalhes, será feito a separação das palavras pela primeira letra do alfabeto ordenando-as em seus respectivos buckets. Em seguida, cada palavra será ordenada pelas suas próximas letras através do Hadix Sort. Para isto, o Hadix irá necessitar de um vetor de apenas 25 posições para cada letra das palavras. 

	
3. Referências

[1] https://www.mat.uc.pt/~pedro/lectivos/CodigosCriptografia1011/interTIC07pqap.pdf
[2] http://www.inf.ufrgs.br/~prestes/Courses/Complexity/aula1.pdf

