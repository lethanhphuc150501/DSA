#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList {
public:
	class Node; // Forward declaration
protected:
	Node* head;
	Node* tail;
	int count;
public:
	SLinkedList()
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
	~SLinkedList() {};
	void add(T e)
	{
		Node* pNew = new Node(e);
		if (this->count == 0)
		{
			this->head = this->tail = pNew;
		}
		else
		{
			this->tail->next = pNew;
			this->tail = pNew;
		}
		this->count++;
	}
	int size()
	{
		return this->count;
	}
	void printList()
	{
		stringstream ss;
		ss << "[";
		Node* ptr = head;
		while (ptr != tail)
		{
			ss << ptr->data << ",";
			ptr = ptr->next;
		}
		if (count > 0)
			ss << ptr->data << "]";
		else
			ss << "]";
		cout << ss.str() << endl;
	}
public:
	class Node {
	private:
		T data;
		Node* next;
		friend class SLinkedList<T>;
	public:
		Node() {
			next = 0;
		}
		Node(T data) {
			this->data = data;
			this->next = nullptr;
		}
	};
	void bubbleSort();
};

template <class T>
void SLinkedList<T>::bubbleSort()
{
	int curr = this->size() - 1;
	bool flag = false;
	while (curr > 0 && flag == false)
	{
		int step = 0;
		Node* tmp = this->head;
		flag = true;
		while (step < curr)
		{
			if (tmp->data > (tmp->next)->data)
			{
				flag = false; 
				//Swap
				T t_value = tmp->data;
				tmp->data = (tmp->next)->data;
				(tmp->next)->data = t_value;
			}
			tmp = tmp->next;
			step++;
		}
		this->printList();
		curr--;
	}
}

int main()
{
	int arr[] = { 23, 78, 45, 8, 56, 32 };
	SLinkedList<int> list;
	for (int i = 0; i <int(sizeof(arr)) / 4; i++)
		list.add(arr[i]);
	list.bubbleSort();
	return 0;
}