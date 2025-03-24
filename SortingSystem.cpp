#include <iostream>
using namespace std;

template <typename T>
class SortingSystem {
private:
    T* data; // Dynamic array for storing input data
    int size; // Size of the array

public:
    SortingSystem(int n);  // Constructor
    ~SortingSystem();      // Destructor

     void insertionSort() {
        for (int i = 1; i < size; ++i) {
            int j = i;
            while (data[j] < data[j-1] && j > 0) {
                swap(data[j], data[j-1]);
                j--;
            }
        }
     }

    void selectionSort() {
         for (int i = 0; i < size; ++i) {
             int minIndex = i;
             for (int j = i; j < size; ++j) {
                 if (data[j] < data[minIndex]) {
                     minIndex = j;
                 }
             }
             swap(data[minIndex], data[i]);
         }
    }

    void bubbleSort();     // (3) Bubble Sort

    void shellSort() {
        int gap = size/2;
        while (gap > 0) {
            for (int i = gap; i < size; ++i) {
                int j = i;
                while (data[j] < data[j-gap] && j >= gap) {
                    swap(data[j], data[j-gap]);
                    j -= gap;
                }
            }
            gap /= 2;
        }
    }

    void mergeSort(int left, int right); // (5) Merge Sort
    void quickSort(int left, int right); // (6) Quick Sort
    void countSort();      // (7) Count Sort (Only for int)
    void radixSort();      // (8) Radix Sort (Only for int)
    void bucketSort();     // (9) Bucket Sort

    void merge(int left, int mid, int right); // Merge Sort Helper
    int partition(int low, int high); // Quick Sort Helper

    void displayData();  // Print the current state of the array
    void measureSortTime(void (SortingSystem::*sortFunc)()); // Measure sorting time

    void showMenu(); // Display menu for user interaction
};
