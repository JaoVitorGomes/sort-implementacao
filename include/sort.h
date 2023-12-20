#ifndef SORT_H
#define SORT_H

#include <vector>
#include "perf.h"

namespace Sort 
{


    // TODO: Implemente do algoritmos de ordenação basicos O(n^2)
    // Escolha uns dos métodos abaixo para implementar
    //   - BubbleSort
    //  - SelectionSort
    //  - InsertionSort
    template<typename T, class Compare >
    int BasicSort(std::vector<T> &v, Compare cmp)
    {
    //metodo escolhido: bubbleSort
    Perf::Performance valueTimer;

    T aux; 
   for(int i = v.size()-2; i > 0; i--){
        for(int j = 0; j <= i ; j++){
            valueTimer.get_counter().increment_comparisons();
            if(cmp(v[j+1],v[j]) == 1){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
   }
   return valueTimer.get_counter().get_comparisons();

    }


    template<typename T, class Compare >
    void mergeSortMerge(std::vector<T> &v, int p, int q, int r,Compare cmp,Perf::Performance &valueCouter){
        int i = p;
        int j = q;
        int k = 0;
        T aux[r];

        while((i < q) && (j < r)){

            if(cmp(v[i],v[j]) == 1){
                aux[k] = v[i];
                i++;
            }else{
                aux[k] = v[j];
                j++;
            }
            k++;
            valueCouter.get_counter().increment_comparisons();   
        }

        while(i < q){
            aux[k] = v[i];
            i++;
            k++;
            valueCouter.get_counter().increment_comparisons();   
        }

        while (j < (r)){
            aux[k] = v[j];
            j++;
            k++;
            valueCouter.get_counter().increment_comparisons();   
        }

        for(int l = p; l < r;l++){
            v[l] = aux[l-p];
        }
    }


    template<typename T, class Compare >
     void mergeSortAlgorithm(std::vector<T> &v,int p,int r,Compare cmp,Perf::Performance &valueCouter){
        int q;

        valueCouter.get_counter().increment_comparisons();    
    
        if(p < (r-1)){
            q =(p + r)/2;
             mergeSortAlgorithm(v,p,q,cmp,valueCouter);
             mergeSortAlgorithm(v,q,r,cmp,valueCouter);
             mergeSortMerge(v,p,q,r, cmp,valueCouter);
        }

    }

    // TODO: Implemente algoritmo de ordenação MergeSort
    template<typename T, class Compare >
    int MergeSort(std::vector<T> &v, Compare cmp)
    {
        Perf::Performance valueCouter;

        int p = 0;
        int r = v.size();
        mergeSortAlgorithm(v,p,r,cmp,valueCouter);

        return valueCouter.get_counter().get_comparisons();
    }



    template<typename T, class Compare >
    int QuickSortPartition(std::vector<T> &v,int lo, int hi, Compare cmp,Perf::Performance &valueCouter)
    {
        T pivo = v[(int)(((hi-lo)/2)+lo)];
        T aux;
        int i = lo -1;
        int j = hi +1;

        while(true){

            do{
                i= i+ 1;
                valueCouter.get_counter().increment_comparisons();  
            }while(cmp(v[i],pivo) == 1);

            do{
                j= j-1;
                valueCouter.get_counter().increment_comparisons();  
            }while(cmp(pivo,v[j])== 1);

            if(i>=j){
                valueCouter.get_counter().increment_comparisons();  
                return j;
            }
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }

    template<typename T, class Compare >
    void QuickSortAlgorithm(std::vector<T> &v,int lo, int hi, Compare cmp,Perf::Performance &valueCouter)
    {
        int p;
        if((lo >=0) && (hi>=0) && (lo < hi)){
            p = QuickSortPartition(v,lo,hi,cmp,valueCouter);
            QuickSortAlgorithm(v,lo,p,cmp,valueCouter);
            QuickSortAlgorithm(v,p+1,hi,cmp,valueCouter);
        }
    }

    // TODO: Implemente algoritmo de ordenação QuickSort
    template<typename T, class Compare >
    int QuickSort(std::vector<T> &v, Compare cmp)
    {

    Perf::Performance valueCouter;
    int lo = 0;
    int hi = v.size()-1;
    QuickSortAlgorithm(v,lo,hi,cmp,valueCouter);

    return valueCouter.get_counter().get_comparisons();
    }




    template<typename T, class Compare >
    void HeapSortMaxHeapify(std::vector<T> &v,int i, int n ,Compare cmp,Perf::Performance &valueCouter)
    {
        T aux;

        int pai = i;
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        

        if((esq <= n) && (cmp(v[pai],v[esq]) == 1)){
            pai = esq;
            
        }

        if((dir <= n) && (cmp(v[pai],v[dir]) == 1)){
            pai = dir;
        }

        if(pai != i){

            aux = v[pai];
            v[pai] = v[i];
            v[i] = aux;

            HeapSortMaxHeapify(v,pai,n,cmp,valueCouter);
        }
 
    valueCouter.get_counter().increment_comparisons();  
    }

    template<typename T, class Compare >
    void HeapSortMaxHeap(std::vector<T> &v, int n,Compare cmp,Perf::Performance &valueCouter)
    {
        for(int i = n/2-1 ;i >= 0;i--){
            HeapSortMaxHeapify(v,i,n-1, cmp,valueCouter);
        }
    }
    


    //  TODO: Implemente algoritmo de ordenação HeapSort
    template<typename T, class Compare >
    int HeapSort(std::vector<T> &v, Compare cmp)
    {
        Perf::Performance valueCouter;
        int n = v.size();
        T aux;
        HeapSortMaxHeap(v,n, cmp,valueCouter);

        for(int i = n-1; i > 0; i--){
            aux = v[0];
            v[0] = v[i];
            v[i] = aux;

            HeapSortMaxHeapify(v,0,i-1,cmp,valueCouter);
        }

    return valueCouter.get_counter().get_comparisons();
    }

template<typename T, class Compare >
    void ShellSort(std::vector<T> &v,int n,int gaps, Compare cmp,Perf::Performance &valueCouter)
    {
        T aux;
        int j;
        if(gaps > 1){
            gaps = gaps/3;

            for(int i = gaps; i < n; i++) {
                aux = v[i];
                j = i - gaps;
                while ((j >= 0) && (cmp(aux,v[j]) == 1)) {
                    v [j + gaps] = v[j];
                    j -= gaps;
                    valueCouter.get_counter().increment_comparisons();  
                }
                v [j + gaps] = aux;
                valueCouter.get_counter().increment_comparisons();  
            }
            ShellSort(v,n,gaps,cmp,valueCouter);
        }
   
    }

    // TODO: Pesquise por algoritmos de ordenação eficientes não vistos em sala de aula.
    //       Implemente um deles.
    template<typename T, class Compare >
    int MySort(std::vector<T> &v, Compare cmp)
    {
        //shell sort
        Perf::Performance valueCouter;
        int n = v.size();
        int gaps = 1;
    
        while(gaps < n) {
            gaps = 3*gaps+1;
        }

        ShellSort(v,n,gaps,cmp,valueCouter);
        return valueCouter.get_counter().get_comparisons();
    }

    //Observaçã0:
     // Compare cmp é uma função que recebe dois elementos do tipo T e retorna um bool.
     // Exemplo de como declarar uma função do tipo Compare:
     /*
       struct {
         bool operator() (T &a, T &b) const
            {
                return a < b;
            }
        } cmp;
    */
     // Se cmp(a, b) retorna true, então a é menor que b. 
     // veja nos arquivos de teste como usar essa função.

     // Funçoes auxiliares deve ser implementadas neste arquivo.
}

#endif /* SORT_H */
