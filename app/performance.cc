
#include "siga.h"
#include "sort.h"
#include "perf.h"
#include "tools.h"
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

struct {
  bool operator() (Siga::Estudante &a, Siga::Estudante &b) const
  { 
    return std::strcmp(a.ObterNome(), b.ObterNome()) < 0;
  }
} LessThanName;

int main(int argc, const char* argv[])
{

    Siga::Siga siga;
    siga.InitDatabase("estudantes");
    std::vector<Siga::Estudante> data;
    std::vector<int> idx = Siga::Tools::get_random_int_vector(TEST_VECTOR_SIZE, siga.ObterNumeroEstudantes());


    siga.ExtraiaEstudantes(idx, data);

    std::vector<Siga::Estudante> aux = data;
    // Copia os dados para um vetor de dados

    Perf::PerformanceTimer timer;
    Perf::Performance valueTimer;
    int valor = 0;

    data = aux;
    valueTimer.get_timer().start();
    valor = Sort::BasicSort(data, LessThanName);
    valueTimer.get_timer().stop();
    cout << "timer: " << valueTimer.get_timer().elapsed_time() <<" -- "<< valor<< endl;

    data = aux;
    valueTimer.get_timer().start();
    valor = Sort::MergeSort(data,LessThanName);
    valueTimer.get_timer().stop();
    cout << "timer: " << valueTimer.get_timer().elapsed_time()<<" -- "<< valor << endl;

    data = aux;
    valueTimer.get_timer().start();
    valor = Sort::QuickSort(data,LessThanName);
    valueTimer.get_timer().stop();
    cout << "timer: " << valueTimer.get_timer().elapsed_time()<<" -- "<< valor << endl;

    data = aux;
    valueTimer.get_timer().start();
    valor = Sort::HeapSort(data,LessThanName);
    valueTimer.get_timer().stop();
    cout << "timer: " << valueTimer.get_timer().elapsed_time()<<" -- "<< valor << endl;

    data = aux;
    valueTimer.get_timer().start();
    valor = Sort::MySort(data,LessThanName);
    valueTimer.get_timer().stop();
    cout << "timer: " << valueTimer.get_timer().elapsed_time()<<" -- "<< valor << endl;

    // TODO: Implementar teste de performance considerando aleatórios
    // Chame as rotinas de ordenação: 
    //  BasicSort, MergeSort, QuickSort, HeapSort, MySort
    // e meça tempo de execução, número de comparações e trocas.
    // Use diferentes tamanhos de vetores para testar.
    // Verifique o depemepenho usando 
    //    (1) vetores de inteiros de diferentes tamanhos
    //    (2) vetores de estudantes de diferentes tamanhos
    // Observe que a base de dados tem tamanho máximo de 5000 estudantes.
    // Analise o desempenho considerando as seguintes configurações de entrada:
    //    (1) dados com distribuição aleatória. (caso médio)
    //    (2) dados com ordenação descendente (pior caso)

    //OBS.: Na implementação dos métodos de ordenação, busque por implementações eficientes.
    //      Indique os resultados obtidos no arquivo REPORT.m


    
    return 0;

}

