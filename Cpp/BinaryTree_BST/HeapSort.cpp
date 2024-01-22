#define SEPARATOR "#<ab@17943918#@>#"
#ifndef SORTING_H
#define SORTING_H
#include <iostream>
using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void ReheapDown(T* start, int position, int last_position) {
        int left = 2 * position + 1;
        int right = 2 * position + 2;
        if (left <= last_position) {
            int larger = left;
            if (right <= last_position && start[right] > start[left]) larger = right;
            if (start[larger] > start[position]) {
                T tmp = start[larger];
                start[larger] = start[position];
                start[position] = tmp;
                ReheapDown(start, larger, last_position);
            }
        }
    }

    //Helping functions go here
    static void heapSort(T* start, T* end){
        int count = end - start;
        int position = count / 2 - 1;
        while (position >= 0) {
            ReheapDown(start, position, count - 1);
            position--;
        }
        int last = count - 1;
        while (last > 0) {
            T tmp = start[0];
            start[0] = start[last];
            start[last] = tmp;
            last--;
            ReheapDown(start, 0, last);
        }
        Sorting<T>::printArray(start,end);
    }
    
};
#endif /* SORTING_H */

int main() {
    int arr[4]={9,6,3,1};
    Sorting<int>::heapSort(&arr[0],&arr[4]);
    return 0;
}