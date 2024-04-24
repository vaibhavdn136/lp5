#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <vector>
#include<iostream>
#include <chrono>
using namespace std;

void merge(int array[],int low, int mid, int high,int size){
    int temp[size];
    int i = low;
    int j = mid + 1;
    int k = 0;
    while((i <= mid) && (j <= high)){
        if(array[i] >= array[j]){
            temp[k] = array[j];
            k++;
            j++;
        }
        else{
            temp[k] = array[i];
            k++;
            i++;
        }
    }
    while(i <= mid){
        temp[k] = array[i];
        k++;
        i++;
    }
    while(j <= high){
        temp[k] = array[j];
        k++;
        j++;
    }

    k = 0;
    for(int i = low;i <= high;i++){
        array[i] = temp[k];
        k++;
    }
}

void sequentialMergeSort(int array[],int low,int high,int size){
    if(low < high){
        int mid = low + (high - low) / 2;
        sequentialMergeSort(array,low,mid,size);
        sequentialMergeSort(array,mid+1,high,size);
        merge(array,low,mid,high,size);
    }
}

void parallelMergeSort(int arr[], int low, int high,int size) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, low, mid,size);
            #pragma omp section
            parallelMergeSort(arr, mid + 1, high,size);
        }

        merge(arr, low, mid, high,size);
    }
}

int main() {
    int n = 10000; 
    int arr[10000], arr_copy[10000];


    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }

    for (int i = 0; i < n; i++) {
        arr_copy[i] = arr[i];
    }


    double start_time = omp_get_wtime();
    sequentialMergeSort(arr_copy, 0, n - 1,n);
    double sequential_merge_sort_time = omp_get_wtime() - start_time;

    for (int i = 0; i < n; i++) {
        arr_copy[i] = arr[i];
    }

    double start_time1 = omp_get_wtime();
    parallelMergeSort(arr_copy, 0, n - 1,n);
    double parallel_merge_sort_time = omp_get_wtime() - start_time1;


    printf("Sequential Merge Sort Time: %f seconds\n", sequential_merge_sort_time);
    printf("Parallel Merge Sort Time: %f seconds\n", parallel_merge_sort_time);

    return 0;

}