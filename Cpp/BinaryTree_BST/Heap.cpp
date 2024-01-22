#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

template <class T>
class Heap {
protected:
    T *elements;
    int capacity;
    int count;
public:
    Heap() {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap() {
        delete []elements;
    }
    void push(T item);
    void printHeap() {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]";
    }
private:
    void ensureCapacity(int minCapacity); 
    void reheapUp(int position);
};

// Your code here
template <class T>
void Heap<T>::ensureCapacity(int minCapacity) {
    if (minCapacity > this->capacity) {
        int newCapacity = (this->capacity * 3) / 2 + 1;
        if (newCapacity < minCapacity) newCapacity = minCapacity;
        T* newStorage = new T[newCapacity];
        memcpy(newStorage, this->elements, this->count);
        this->capacity = newCapacity;
        delete this->elements;
        this->elements = newStorage;
    }
}

template <class T>
void Heap<T>::reheapUp(int position) {
    if (position > 0) {
        int parent = (position - 1) / 2;
        if (this->elements[parent] < this->elements[position]) {
            int tmp = this->elements[parent];
            this->elements[parent] = this->elements[position];
            this->elements[position] = tmp;
            reheapUp(parent);
        }
    }
}

template <class T>
void Heap<T>::push(T item) {
    ensureCapacity(this->count + 1);
    this->elements[this->count] = item;
    reheapUp(this->count);
    this->count++;
}

int main() {    	
    Heap<int> maxHeap;
    for(int i = 0; i <5;i++)
        maxHeap.push(i);
    maxHeap.printHeap();
    return 0;
}