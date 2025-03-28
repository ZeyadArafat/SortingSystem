#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class SortingSystem {
private:
    T* data; // Dynamic array for storing input data
    int size; // Size of the array

public:
    SortingSystem(int s) {
        size = s;
        data = new T[size];
        for (int i = 0; i < size; ++i) {
            cout << "enter data " << i+1 << ": ";
            cin >> data[i];
        }
    }
    ~SortingSystem() {
        delete[] data;
    }

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

    void bubbleSort() {
        bool swapped;
        for (int i = 0; i < size; ++i) {
            swapped = false;

            for (int j = 1; j < size; ++j) {
                if (data[j] < data[j-1]) {
                    swap(data[j], data[j-1]);
                }
            }
            if (!swapped) break;
        }
    }    // (3) Bubble Sort

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

    void mergeSort(int left, int right) {
        if (right > left) {
            int middle = left + (right - left) / 2;
            mergeSort(left, middle);
            mergeSort(middle+1, right);
            merge(left, middle, right);
        }
    }


    void quickSort(int left, int right) {
        if (left >= right) return;

        int mid = partition(left, right);

        quickSort(left, mid-1);
        quickSort(mid + 1, right);
    }


    void countSort() {
        int freq_array_size = get_max() + 1;
        int* freq_array = new int[freq_array_size];

        for (int i = 0; i < freq_array_size; i++) {
            freq_array[i] = 0;
        }

        for (int i = 0; i < size; i++) {
            freq_array[data[i]]++;
        }

        int index = 0;
        for (int i = 0; i < freq_array_size; i++) {
            while (freq_array[i] > 0) {
                data[index] = i;
                index++;
                freq_array[i]--;
            }
        }

        delete[] freq_array;
    }    // (7) Count Sort (Only for int)
    void radixSort();      // (8) Radix Sort (Only for int)

    void bucketSort() {
         if constexpr (is_same_v<T, string>) {
             vector<vector<T>> buckets(256);
             for (int i = 0; i < size; ++i) {
                 buckets[data[i][0]].push_back(data[i]);
             }
             for (int i = 0; i < size; ++i) {
                 for (int j = 1; j < buckets[i].size(); ++j) {
                     int k = j;
                     while (buckets[i][k] < buckets[i][k-1] && k > 0) {
                         swap(buckets[i][k], buckets[i][k-1]);
                         k--;
                     }
                 }
             }
             int currentBucket = 0;
             for (int i = 0; i < size;) {
                 for (T value: buckets[currentBucket]) {
                     data[i] = value;
                     i++;
                 }
                 currentBucket++;
             }
         }
         else if (is_same_v<T,char>) {
             vector<vector<T>> buckets(256);
             for (int i = 0; i < size; ++i) {
                 buckets[data[i]].push_back(data[i]);
             }
             int currentBucket = 0;
             for (int i = 0; i < size;) {
                 for (T value: buckets[currentBucket]) {
                     data[i] = value;
                     i++;
                 }
                 currentBucket++;
             }
         }
         else {
             double min = data[0];
             double max = data[0];
             for (int i = 0; i < size; ++i) {
                 if (data[i] > max) {
                     max = data[i];
                 }
                 if (data[i] < min) {
                     min = data[i];
                 }
             }
             double bucketRange = (max - min) / size;
             vector<vector<T>> buckets(size);
             for (int i = 0; i < size; ++i) {
                 for (int j = 0; j < size; ++j) {
                     if (data[i] <= min + bucketRange * (j+1)) {
                         buckets[j].push_back(data[i]);
                         break;
                     }
                 }
             }
             for (int i = 0; i < size; ++i) {
                 for (int j = 1; j < buckets[i].size(); ++j) {
                     int k = j;
                     while (buckets[i][k] < buckets[i][k-1] && k > 0) {
                         swap(buckets[i][k], buckets[i][k-1]);
                         k--;
                     }
                 }
             }
             int currentBucket = 0;
             for (int i = 0; i < size;) {
                 for (int j = 0; j < buckets[currentBucket].size(); ++j) {
                     data[i] = buckets[currentBucket][j];
                     i++;
                 }
                 currentBucket++;
             }
         }

    }

    void merge(int left, int mid, int right) {
        int s1 = mid - left + 1;
        int s2 = right - mid;
        T* leftArr = new T[s1];
        T* rightArr = new T[s2];
        for (int i = 0; i < s1; ++i) {
            leftArr[i] = data[left + i];
        }
        for (int i = 0; i < s2; ++i) {
            rightArr[i] = data[mid + 1 + i];
        }
        int l = 0, r = 0, k = left;
        while (l < s1 && r < s2) {
            if (leftArr[l] < rightArr[r]) {
                data[k] = leftArr[l];
                l++;
            }
            else {
                data[k] = rightArr[r];
                r++;
            }
            k++;
        }
        while (l < s1) {
            data[k] = leftArr[l];
            l++;
            k++;
        }
        while (r < s2) {
            data[k] = rightArr[r];
            r++;
            k++;
        }
        delete[] leftArr;
        delete[] rightArr;
    }


    int partition(int low, int high) {
        T pivot = data[low];
        int i = low;
        for (int j = low + 1; j <= high; j++) {
            if (pivot > data[j]) {
                i++;
                swap(data[i], data[j]);
            }
        }
        swap(data[i], data[low]);
        return i;
    }

    int get_max() {
        int maximum = data[0];
        for (int i = 0; i < size; i++) {
            maximum = max(maximum, data[i]);
        }
        return maximum;
    }

    void displayData();  // Print the current state of the array
    void measureSortTime(void (SortingSystem::*sortFunc)()); // Measure sorting time

    void showMenu(); // Display menu for user interaction
};
