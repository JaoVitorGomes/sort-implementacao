# Relatório: Métodos de Ordenação

**Componentes:**
 - Nome: João Vitor Gomes da Silva, Matricula: 202035035
 

## Análise de desempenho:

A analise de desempenho foi feita a partir da adição de um comparador dentro das funções
de sort, onde contabilizou as comparações e a chamada do timer, sendo iniciada antes da
função inicializar e finalizada depois da função terminar a execução. A metodologia
utilizada foi a execução dos codigos mais parecido possivel com os pseudocodigo, para que 
dessa forma não perca eficiencia, como o objetivo foi ser o mais parecido com os pseudocodigo, não foi utilizada tecnicas para a melhoria do desempenho.


| SORTS | BubbleSort | MergeSort | QuickSort | HeapSort | ShellSort |
| --- |--- |--- |--- | --- | --- |
|TEMPO| 0.000298704 s | 0.000114401 s |  4.26e-05 s | 6.4901e-05 | 3.79e-05 |
|QTD COMPARAÇÕES| 4949 | 871 | 1076 | 625 | 762 |


Verificando a tabela, percebemos que o shellSort foi o mais rapido entre eles, cada codigo foi executado 10 vezes, uilizando o mesmo vetor, tendo o mesmo tamanho que os de testes


## Conclusões

Podemos concluir que como a quantidade de execução e variação de vetores não ordenado foi baixissima, não consseguimos concluir de forma correta a diferença entre os algoritmos de ordenação, entretanto podemos perceber que quanto utilizamos um vetor de 100 valores e executamos os algoritmos 10 vezes, o shellSort é superior quando falamos de menor tempo e o heapSort é superior quando falamos de quantidade de comparações realizada no codigo
