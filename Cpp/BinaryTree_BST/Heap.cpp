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
    T peek();
    bool pop();
    int size();
    bool isEmpty();
    bool contains(T item);
    void printHeap() {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]";
    }
private:
    void ensureCapacity(int minCapacity); 
    void reheapUp(int position);
    void reheapDown(int position);
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
void Heap<T>::reheapDown(int position) {
    int left = 2 * position + 1;
    int right = 2 * position + 2;
    if (left < this->count) {
        int larger = left;
        if (right < this->count && this->elements[right] > this->elements[left]) larger = right;
        if (this->elements[larger] > this->elements[position]) {
            int tmp = this->elements[larger];
            this->elements[larger] = this->elements[position];
            this->elements[position] = tmp;
            reheapDown(larger);
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
template <class T>
T Heap<T>::peek() {
    return this->elements[0];
}
template <class T>
bool Heap<T>::pop() {
    if (this->count > 0) {
        this->count--;
        this->elements[0] = this->elements[this->count];
        reheapDown(0);
        return true;
    }
    return false;
}
template <class T>
int Heap<T>::size() {
    return this->count;
}
template <class T>
bool Heap<T>::isEmpty() {
    return (this->count == 0);
}
template <class T>
bool Heap<T>::contains(T item) {
    for (int i = 0; i < this->count; i++) {
        if (this->elements[i] == item) return true;
    }
    return false;
}
int main() {    	
    Heap<int> maxHeap;
    for (int i = 0; i < 10; i++) {
        maxHeap.push(i);
    }
    cout << maxHeap.isEmpty();
    return 0;
}