#include <iostream>
#include <chrono>
#include <array>
#include <type_traits>


using namespace std;

template <typename T>
class SortingSystem
{
private:
    T *data;  // Dynamic array for storing input data
    int size; // Size of the array
private:
    int get_max()
    {
        int maximum = data[0];
        for (int i = 0; i < size; i++)
        {
            maximum = max(maximum, data[i]);
        }
        return maximum;
    }

public:
    SortingSystem(int s)
    {
        size = s;
        data = new T[size];
        for (int i = 0; i < size; ++i)
        {
            cout << "Enter data " << i + 1 << ": ";
            cin >> data[i];
        }
    }
    ~SortingSystem()
    {
        delete[] data;
    }

    void insertionSort()
    {
        cout << "Sorting using Insertion Sort..." << endl;
        cout << "Initial Data: ";
        displayData();

        for (int i = 1; i < size; ++i)
        {
            int j = i;
            while (j > 0 && data[j] < data[j - 1])
            {
                swap(data[j], data[j - 1]);
                j--;
            }
            cout << "Iteration " << i << ": ";
            displayData();
        }
        cout << "\nSorted Data: ";
        displayData();
    }

    void selectionSort()
    {
        cout << "Sorting using Selection Sort..." << endl;
        cout << "Initial Data: ";
        displayData();

        for (int i = 0; i < size; ++i)
        {
            int minIndex = i;
            for (int j = i; j < size; ++j)
            {
                if (data[j] < data[minIndex])
                {
                    minIndex = j;
                }
            }
            swap(data[minIndex], data[i]);
            cout << "Iteration " << i + 1 << ": ";
            displayData();
        }
        cout << "\nSorted Data: ";
        displayData();
    }

    void bubbleSort()
    {
        cout << "Sorting using Bubble Sort..." << endl;
        cout << "Initial Data: ";
        displayData();

        for (int i = 0; i < size - 1; ++i)
        {
            bool swapped = false;

            for (int j = 0; j < size - i - 1; ++j)
            {
                if (data[j] > data[j + 1])
                {
                    swap(data[j], data[j + 1]);
                    swapped = true;
                }
            }
            cout << "Iteration " << i + 1 << ": ";
            displayData();

            if (!swapped)
                break;
        }
        cout << "\nSorted Data: ";
        displayData();
    }

    void shellSort()
    {
        cout << "Sorting using Shell Sort..." << endl;
        cout << "Initial Data: ";
        displayData();

        int iteration = 0;
        int gap = size / 2;
        while (gap > 0)
        {
            for (int i = gap; i < size; ++i)
            {
                int j = i;
                while (j >= gap && data[j] < data[j - gap])
                {
                    swap(data[j], data[j - gap]);
                    j -= gap;
                }
            }
            cout << "Gap " << gap << ": ";
            displayData();
            gap /= 2;
            iteration++;
        }
        cout << "\nSorted Data: ";
        displayData();
    }

    void mergeSort(int left, int right)
    {
        if (left >= right)
            return;

        int middle = left + (right - left) / 2;
        mergeSort(left, middle);
        mergeSort(middle + 1, right);
        merge(left, middle, right);

        cout << "Merging elements from index " << left << " to " << right << ": ";
        for (int i = 0; i < size; i++)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void quickSort(int left, int right)
    {
        if (left >= right)
            return;

        int mid = partition(left, right);

        cout << "Partition at index " << mid << " (pivot: " << data[mid] << "): ";
        for (int i = 0; i < size; i++)
        {
            cout << data[i] << " ";
        }
        cout << endl;

        quickSort(left, mid - 1);
        quickSort(mid + 1, right);
    }

    void countSort()
    {
        if constexpr (!is_same_v<T, int>)
        {
            cout << "Count Sort only works with integers!" << endl;
            return;
        }

        cout << "Sorting using Count Sort..." << endl;
        cout << "Initial Data: ";
        displayData();

        int freq_array_size = get_max() + 1;
        int *freq_array = new int[freq_array_size];

        for (int i = 0; i < freq_array_size; i++)
        {
            freq_array[i] = 0;
        }

        for (int i = 0; i < size; i++)
        {
            ++freq_array[data[i]];
        }

        int index = 0;
        for (int i = 0; i < freq_array_size; i++)
        {
            while (freq_array[i] > 0)
            {
                data[index] = i;
                index++;
                --freq_array[i];
            }
        }

        cout << "\nSorted Data: ";
        displayData();

        delete[] freq_array;
    }

    void radixSort()
    {
        if constexpr (!is_same_v<T, int>)
        {
            cout << "Radix Sort only works with integers!" << endl;
            return;
        }

        cout << "Sorting using Radix Sort..." << endl;
        cout << "Initial Data: ";
        displayData();

        int max_element = get_max();

        for (int e = 1; max_element / e > 0; e *= 10)
        {
            int *freq_array = new int[10];
            int *output = new int[size];

            for (int i = 0; i < 10; i++)
            {
                freq_array[i] = 0;
            }

            for (int i = 0; i < size; i++)
            {
                ++freq_array[(data[i] / e) % 10];
            }

            for (int i = 1; i < 10; i++)
            {
                freq_array[i] = freq_array[i] + freq_array[i - 1];
            }

            for (int i = size - 1; i >= 0; i--)
            {
                output[freq_array[(data[i] / e) % 10] - 1] = data[i];
                --freq_array[(data[i] / e) % 10];
            }

            for (int i = 0; i < size; i++)
            {
                data[i] = output[i];
            }

            cout << "After sorting digit at place value " << e << ": ";
            displayData();

            cout << "\nSorted Data: ";
            displayData();

            delete[] output;
            delete[] freq_array;
        }
    }

    void bucketSort()
    {
        if constexpr (is_same_v<T, string>)
        {
            T buckets[256][size];
            int bucketsCount[256] = {};
            for (int i = 0; i < size; ++i)
            {
                buckets[data[i][0]][bucketsCount[data[i][0]]] = data[i];
                bucketsCount[data[i][0]]++;
            }
            for (int i = 0; i < 256; ++i)
            {
                for (int j = 1; j < bucketsCount[i]; ++j)
                {
                    int k = j;
                    while (buckets[i][k] < buckets[i][k - 1] && k > 0)
                    {
                        swap(buckets[i][k], buckets[i][k - 1]);
                        k--;
                    }
                }
            }
            int currentBucket = 0;
            for (int i = 0; i < size;)
            {
                for (int j = 0; j < bucketsCount[currentBucket]; ++j)
                {
                    data[i] = buckets[currentBucket][j];
                    i++;
                }
                currentBucket++;
            }
        }
        else if (is_same_v<T, char>)
        {
            T buckets[256][size];
            int bucketsCount[256] = {};
            for (int i = 0; i < size; ++i)
            {
                buckets[data[i]][bucketsCount[data[i]]] = data[i];
                bucketsCount[data[i]]++;
            }
            int currentBucket = 0;
            for (int i = 0; i < size;)
            {
                for (int j = 0; j < bucketsCount[currentBucket]; j++)
                {
                    data[i] = buckets[currentBucket][j];
                    i++;
                }
                currentBucket++;
            }
        }
        else
        {
            double min = data[0];
            double max = data[0];
            for (int i = 0; i < size; ++i)
            {
                if (data[i] > max)
                {
                    max = data[i];
                }
                if (data[i] < min)
                {
                    min = data[i];
                }
            }
            double bucketRange = (max - min) / size;
            T buckets[size][size];
            int bucketsCount[size] = {};
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    if (data[i] <= min + bucketRange * (j + 1))
                    {
                        buckets[j][bucketsCount[j]] = data[i];
                        bucketsCount[j]++;
                        break;
                    }
                }
            }
            for (int i = 0; i < size; ++i)
            {
                if (bucketsCount[i] == 0)
                {
                    continue;
                }
                for (int j = 1; j < bucketsCount[i]; ++j)
                {
                    int k = j;
                    while (buckets[i][k] < buckets[i][k - 1] && k > 0)
                    {
                        swap(buckets[i][k], buckets[i][k - 1]);
                        k--;
                    }
                }
            }
            int currentBucket = 0;
            for (int i = 0; i < size;)
            {
                for (int j = 0; j < bucketsCount[currentBucket]; ++j)
                {
                    data[i] = buckets[currentBucket][j];
                    i++;
                }
                currentBucket++;
            }
        }
        cout << "\nSorted Data: ";
        displayData();
    }


    void merge(int left, int mid, int right)
    {
        int s1 = mid - left + 1;
        int s2 = right - mid;
        T *leftArr = new T[s1];
        T *rightArr = new T[s2];
        for (int i = 0; i < s1; ++i)
        {
            leftArr[i] = data[left + i];
        }
        for (int i = 0; i < s2; ++i)
        {
            rightArr[i] = data[mid + 1 + i];
        }
        int l = 0, r = 0, k = left;
        while (l < s1 && r < s2)
        {
            if (leftArr[l] <= rightArr[r])
            {
                data[k] = leftArr[l];
                l++;
            }
            else
            {
                data[k] = rightArr[r];
                r++;
            }
            k++;
        }
        while (l < s1)
        {
            data[k] = leftArr[l];
            l++;
            k++;
        }
        while (r < s2)
        {
            data[k] = rightArr[r];
            r++;
            k++;
        }
        delete[] leftArr;
        delete[] rightArr;
    }

    int partition(int low, int high)
    {
        T pivot = data[low];
        int i = low;
        for (int j = low + 1; j <= high; j++)
        {
            if (data[j] < pivot)
            {
                i++;
                swap(data[i], data[j]);
            }
        }
        swap(data[i], data[low]);
        return i;
    }

    void displayData()
    {
        cout << "[";
        for (int i = 0; i < size; i++)
        {
            cout << data[i];
            if (i < size - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }

    void measureSortTime(void (SortingSystem::*sortFunc)())
    {
        auto initial = chrono::high_resolution_clock::now();
        (this->*sortFunc)();
        auto final = chrono::high_resolution_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(final - initial);

        cout << "Sorting Time: " << time.count() / 1000000.0 << " seconds" << endl;
    }

    void runMergeSort()
    {
        cout << "Sorting using Merge Sort..." << endl;
        cout << "Initial Data: ";
        displayData();

        auto initial = chrono::high_resolution_clock::now();
        mergeSort(0, size - 1);
        auto final = chrono::high_resolution_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(final - initial);

        cout << "Sorted Data: ";
        displayData();
        cout << "Sorting Time: " << time.count() / 1000000.0 << " seconds" << endl;
    }

    void runQuickSort()
    {
        cout << "Sorting using Quick Sort..." << endl;
        cout << "Initial Data: ";
        displayData();

        auto initial = chrono::high_resolution_clock::now();
        quickSort(0, size - 1);
        auto final = chrono::high_resolution_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(final - initial);

        cout << "Sorted Data: ";
        displayData();
        cout << "Sorting Time: " << time.count() / 1000000.0 << " seconds" << endl;
    }

    void showMenu()
    {
        while (true)
        {
            cout << "Enter the number of items to sort: " << endl;
            int size;
            cin >> size;

            cout << "Enter the datatype of your data set: " << endl;
            cout << "1. int" << endl;
            cout << "2. float" << endl;
            cout << "3. double" << endl;
            cout << "4. char" << endl;
            cout << "5. string" << endl;
            char data_set_type;
            cin >> data_set_type;

            cout << "Select a sorting algorithm: " << endl;
            cout << "1. Insertion Sort" << endl;
            cout << "2. Selection Sort" << endl;
            cout << "3. Bubble Sort" << endl;
            cout << "4. Shell Sort" << endl;
            cout << "5. Merge Sort" << endl;
            cout << "6. Quick Sort" << endl;
            cout << "7. Count Sort (Only for integers)" << endl;
            cout << "8. Radix Sort (Only for integers)" << endl;
            cout << "9. Bucket Sort" << endl;
            cout << "Enter your choice (1-9):" << endl;

            char choice;
            cin >> choice;

            switch (data_set_type)
            {
            case '1':
            {
                SortingSystem<int> sorter(size);
                switch (choice)
                {
                case '1':
                    sorter.measureSortTime(&SortingSystem<int>::insertionSort);
                    break;
                case '2':
                    sorter.measureSortTime(&SortingSystem<int>::selectionSort);
                    break;
                case '3':
                    sorter.measureSortTime(&SortingSystem<int>::bubbleSort);
                    break;
                case '4':
                    sorter.measureSortTime(&SortingSystem<int>::shellSort);
                    break;
                case '5':
                    sorter.runMergeSort();
                    break;
                case '6':
                    sorter.runQuickSort();
                    break;
                case '7':
                    sorter.measureSortTime(&SortingSystem<int>::countSort);
                    break;
                case '8':
                    sorter.measureSortTime(&SortingSystem<int>::radixSort);
                    break;
                case '9':
                    sorter.measureSortTime(&SortingSystem<int>::bucketSort);
                    break;
                default:
                    cout << "Invalid Choice, try again." << endl;
                    continue;
                }
                break;
            }
            case '2':
            {
                SortingSystem<float> sorter(size);
                switch (choice)
                {
                case '1':
                    sorter.measureSortTime(&SortingSystem<float>::insertionSort);
                    break;
                case '2':
                    sorter.measureSortTime(&SortingSystem<float>::selectionSort);
                    break;
                case '3':
                    sorter.measureSortTime(&SortingSystem<float>::bubbleSort);
                    break;
                case '4':
                    sorter.measureSortTime(&SortingSystem<float>::shellSort);
                    break;
                case '5':
                    sorter.runMergeSort();
                    break;
                case '6':
                    sorter.runQuickSort();
                    break;
                case '7':
                    cout << "Count Sort only works with integers!" << endl;
                    break;
                case '8':
                    cout << "Radix Sort only works with integers!" << endl;
                    break;
                case '9':
                    sorter.measureSortTime(&SortingSystem<float>::bucketSort);
                    break;
                default:
                    cout << "Invalid Choice, try again." << endl;
                    continue;
                }
                break;
            }
            case '3':
            {
                SortingSystem<double> sorter(size);
                switch (choice)
                {
                case '1':
                    sorter.measureSortTime(&SortingSystem<double>::insertionSort);
                    break;
                case '2':
                    sorter.measureSortTime(&SortingSystem<double>::selectionSort);
                    break;
                case '3':
                    sorter.measureSortTime(&SortingSystem<double>::bubbleSort);
                    break;
                case '4':
                    sorter.measureSortTime(&SortingSystem<double>::shellSort);
                    break;
                case '5':
                    sorter.runMergeSort();
                    break;
                case '6':
                    sorter.runQuickSort();
                    break;
                case '7':
                    cout << "Count Sort only works with integers!" << endl;
                    break;
                case '8':
                    cout << "Radix Sort only works with integers!" << endl;
                    break;
                case '9':
                    sorter.measureSortTime(&SortingSystem<double>::bucketSort);
                    break;
                default:
                    cout << "Invalid Choice, try again." << endl;
                    continue;
                }
                break;
            }
            case '4':
            {
                SortingSystem<char> sorter(size);
                switch (choice)
                {
                case '1':
                    sorter.measureSortTime(&SortingSystem<char>::insertionSort);
                    break;
                case '2':
                    sorter.measureSortTime(&SortingSystem<char>::selectionSort);
                    break;
                case '3':
                    sorter.measureSortTime(&SortingSystem<char>::bubbleSort);
                    break;
                case '4':
                    sorter.measureSortTime(&SortingSystem<char>::shellSort);
                    break;
                case '5':
                    sorter.runMergeSort();
                    break;
                case '6':
                    sorter.runQuickSort();
                    break;
                case '7':
                    cout << "Count Sort only works with integers!" << endl;
                    break;
                case '8':
                    cout << "Radix Sort only works with integers!" << endl;
                    break;
                case '9':
                    sorter.measureSortTime(&SortingSystem<char>::bucketSort);
                    break;
                default:
                    cout << "Invalid Choice, try again." << endl;
                    continue;
                }
                break;
            }
            case '5':
            {
                SortingSystem<string> sorter(size);
                switch (choice)
                {
                case '1':
                    sorter.measureSortTime(&SortingSystem<string>::insertionSort);
                    break;
                case '2':
                    sorter.measureSortTime(&SortingSystem<string>::selectionSort);
                    break;
                case '3':
                    sorter.measureSortTime(&SortingSystem<string>::bubbleSort);
                    break;
                case '4':
                    sorter.measureSortTime(&SortingSystem<string>::shellSort);
                    break;
                case '5':
                    sorter.runMergeSort();
                    break;
                case '6':
                    sorter.runQuickSort();
                    break;
                case '7':
                    cout << "Count Sort only works with integers!" << endl;
                    break;
                case '8':
                    cout << "Radix Sort only works with integers!" << endl;
                    break;
                case '9':
                    sorter.measureSortTime(&SortingSystem<string>::bucketSort);
                    break;
                default:
                    cout << "Invalid Choice, try again." << endl;
                    continue;
                }
                break;
            }
            default:
                cout << "Invalid choice, try again." << endl;
                continue;
            }

            cout << "Do you want to sort another dataset? (y/n): ";
            string resort;
            cin >> resort;

            if (resort == "n" || resort == "N")
            {
                cout << "Thank you for using the sorting system! Goodbye!" << endl;
                break;
            }
        }

    } // Display menu for user interaction
};
