#pragma once

#include<vector>
#include<fstream>

#include "StretchyArray.h"


template<typename T>
void mergeMagic(StretchyArray<T>& arr, int start, int mid, int end) {

    int size1 = mid - start + 1;
    int size2 = end - mid;

    StretchyArray<T> subArr1(size1), subArr2(size2);

    for (int i = 0; i < size1; i++)
        subArr1[i] = arr[start + i];
    for (int j = 0; j < size2; j++)
        subArr2[j] = arr[mid + 1 + j];

    int i, j, k;
    for (i = 0, j = 0, k = start; i < size1 && j < size2; k++) {
        if (subArr1[i] > subArr2[j]) {
            arr[k] = subArr2[j];
            j++;
        }
        else {
            arr[k] = subArr1[i];
            i++;
        }
    }

    while (i < size1) {
        arr[k] = subArr1[i];
        i++;
        k++;
    }

    while (j < size2) {
        arr[k] = subArr2[j];
        j++;
        k++;
    }
}

template<typename T>
void mergeSort_recursive(StretchyArray<T>& arr, int start, int end) {
    if (start < end) {

        int mid = start + (end - start) / 2;

        mergeSort_recursive(arr, start, mid);
        mergeSort_recursive(arr, mid + 1, end);

        mergeMagic(arr, start, mid, end);
    }
}

template<typename T>
void mergeSort(StretchyArray<T>& arr) {
    mergeSort_recursive(arr, 0, arr.size() - 1);
}