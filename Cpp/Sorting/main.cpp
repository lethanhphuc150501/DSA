#include <sstream>
#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
template <class T>
class Sorting
{
private:
	/* Function to print an array */
	static void printArray(T* start, T* end)
	{
		int size = end - start;
		for (int i = 0; i < size - 1; i++)
			cout << start[i] << ", ";
		cout << start[size - 1];
		cout << endl;
	}
	static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total);
public:
	static void selectionSort(T* start, T* end);
	static void insertionSort(T* start, T* end);
	static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases);
};

template <class T>
void Sorting<T>::selectionSort(T* start, T* end)
{
	int size = end - start;
	T cur_min = *start;
	int cur_idx = 0;
	for (int i = 0; i < size - 1; i++)
	{
		cur_min = *(start + i);
		cur_idx = i;
		for (int j = i; j < size; j++)
		{
			if (cur_min > * (start + j))
			{
				cur_min = *(start + j);
				cur_idx = j;
			}				
		}
		//swap
		*(start + cur_idx) = *(start + i);
		*(start + i) = cur_min;
		printArray(start, end);
	}
}
template <class T>
void Sorting<T>::insertionSort(T* start, T* end)
{
	int count = end - start;
	if (count > 1)
	{
		int curr = 1;
		while (curr < count)
		{
			T tmp = *(start + curr);
			int step = curr - 1;
			while ((step >= 0) && (tmp < *(start + step)))
			{
				*(start + step + 1) = *(start + step);
				step--;
			}
			*(start + step + 1) = tmp;
			curr++;
			printArray(start, end);
		}
	}
}
template <class T>
void Sorting<T>::sortSegment(T* start, T* end, int segment_idx, int cur_segment_total)
{
	int count = end - start;
	int curr = segment_idx + cur_segment_total;
	while (curr < count)
	{
		T tmp = *(start + curr);
		int step = curr - cur_segment_total;
		while ((step >= 0) && (tmp < *(start + step)))
		{
			*(start + step + cur_segment_total) = *(start + step);
			step = step - cur_segment_total;
		}
		*(start + step + cur_segment_total) = tmp;
		curr = curr + cur_segment_total;
	}
}
template <class T>
void Sorting<T>::ShellSort(T* start, T* end, int* num_segment_list, int num_phases)
{
	int count = num_phases;
	int k = *(num_segment_list + count - 1);
	while (k >= 1)
	{
		int segment = 0;
		while (segment < k)
		{
			sortSegment(start, end, segment, k);
			segment++;
		}
		cout << k << " segments: ";
		printArray(start, end);
		count--;
		k = *(num_segment_list + count - 1);
	}
}

bool isPermutation(string a, string b) 
{
	if (a.size() != b.size())
	{
		return 0;
	}
	else
	{
		string a_arr = a;
		string b_arr = b;
		Sorting<char>::selectionSort(&a_arr[0], &a_arr[a.size()]);
		Sorting<char>::selectionSort(&b_arr[0], &b_arr[b.size()]);
		for (int i = 0; i < a.size(); i++)
		{
			if (a_arr[i] != b_arr[i]) return 0;
		}
		return 1;
	}
}

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	Sorting<int>::insertionSort(&arr[0], &arr[6]);
	return 0;
}