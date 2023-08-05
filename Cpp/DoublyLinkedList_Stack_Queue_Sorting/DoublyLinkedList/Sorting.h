#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
void swap(T* a, T* b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}

template <class T>
class Sorting {
private:
	static T* Partition(T* start, T* end)
	{
		T pivot = *start;
		int i = 0;
		int j = end - start + 1;
		while (i < j)
		{
			do
			{
				i++;
			} while (*(start + i) < pivot);

			do
			{
				j--;
			} while (*(start + j) > pivot);

			swap(start + i, start + j);
		}
		swap(start + i, start + j);
		swap(start, start + j);
		return (start + j);
	}
public:
	/*
	static void QuickSort(T* start, T* end)
	{
		if (start < end)
		{
			T* pivot = Partition(start, end);
			QuickSort(start, pivot - 1);
			QuickSort(pivot + 1, end);
		}
	}
	*/
	/* Function to print an array */
	static void printArray(T* start, T* end)
	{
		int size = end - start;
		for (int i = 0; i < size - 1; i++)
			cout << start[i] << ", ";
		cout << start[size - 1];
		cout << endl;
	}
	static void selectionSort(T* start, T* end);		
};

template <class T>
void Sorting<T>::selectionSort(T* start, T* end)
{
	int current = 0;
	int count = end - start;
	while (current < count - 1)
	{
		int smallest = current;
		int walker = current + 1;
		while (walker < count)
		{
			if (*(start + walker) < *(start + smallest))
			{
				smallest = walker;
			}
			walker++;
		}
		swap(start + current, start + smallest);
		printArray(start, end);
		current++;
	}
}
