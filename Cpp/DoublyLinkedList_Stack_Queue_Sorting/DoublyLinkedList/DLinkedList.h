#include <iostream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <class T>
class DLinkedList {
public:
	class Node; // Forward declaration
protected:
	Node* head;
	Node* tail;
	int count;
public:
	DLinkedList();
	//~DLinkedList();
	void add(const T& e);
	void add(int index, const T& e);
	T removeAt(int index);
	//bool removeItem(const T& removeItem);
	int size();
	void clear();
	string toString();
	bool empty();
	T get(int index);
	void set(int index, const T& e);
	int indexOf(const T& item);
	bool contains(const T& item);
public:
	class Node
	{
	private:
		T data;
		Node* next;
		Node* previous;
		friend class DLinkedList<T>;
	public:
		Node()
		{
			this->previous = NULL;
			this->next = NULL;
		}
		Node(const T& data)
		{
			this->data = data;
			this->previous = NULL;
			this->next = NULL;
		}
	};
};

template <class T>
DLinkedList<T>::DLinkedList()
{
	this->head = NULL;
	this->tail = NULL;
	this->count = 0;
}
template <class T>
void DLinkedList<T>::add(const T& e) {
	Node* pNew = new Node(e);
	if (this->count == 0) //empty list
	{
		this->head = pNew;
		this->tail = pNew;
	}
	else //non-empty list
	{
		pNew->previous = this->tail;
		this->tail->next = pNew;
		this->tail = pNew;
	}
	this->count++;
}
template <class T>
void DLinkedList<T>::add(int index, const T& e) {
	if ((index == this->count - 1 && index != 0) || this->count == 0)
	{
		add(e);
	}
	else if (index == 0)
	{
		Node* pNew = new Node(e);
		pNew->next = this->head;
		this->head->previous = pNew;
		this->head = pNew;
		this->count++;
	}
	else
	{
		Node* pNew = new Node(e);
		Node* tmp = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			tmp = tmp->next;
		}
		Node* pre = tmp->previous;
		pNew->previous = pre;
		pre->next = pNew;
		pNew->next = tmp;
		tmp->previous = pNew;
		this->count++;
	}
}
template <class T>
T DLinkedList<T>::removeAt(int index)
{
	Node* tmp = this->head;
	if (this->count == 1)
	{
		this->head = NULL;
		this->tail = NULL;
	}
	else if (index == 0)
	{
		this->head = tmp->next;
		this->head->previous = NULL;
	}
	else if (index == this->count - 1)
	{
		tmp = this->tail;
		this->tail = tmp->previous;
		this->tail->next = NULL;
	}
	else
	{
		for (int i = 0; i < index; i++)
		{
			tmp = tmp->next;
		}
		Node* pre = tmp->previous;
		Node* post = tmp->next;
		pre->next = post;
		post->previous = pre;
	}	
	T data = tmp->data;
	delete tmp;
	this->count--;
	return data;
}
template <class T>
int DLinkedList<T>::size() {
	return this->count;
}
template <class T>
string DLinkedList<T>::toString()
{
	stringstream ss;
	Node* temp = head;
	while (temp != NULL)
	{
		ss << temp->data << " ";
		temp = temp->next;
	}
	return ss.str();
}
template <class T>
bool DLinkedList<T>::empty()
{
	if (this->count == 0) return true;
	else return false;
}
template <class T>
T DLinkedList<T>::get(int index)
{
	Node* tmp = this->head;
	for (int i = 0; i < index; i++)
	{
		tmp = tmp->next;
	}
	return tmp->data;
}
template <class T>
void DLinkedList<T>::set(int index, const T& e)
{
	Node* tmp = this->head;
	for (int i = 0; i < index; i++)
	{
		tmp = tmp->next;
	}
	tmp->data = e;
}
template <class T>
int DLinkedList<T>::indexOf(const T& item)
{
	if (this->count == 0) return -1;
	Node* tmp = this->head;
	int index = 0;
	do
	{
		if (tmp->data == item) return index;
		tmp = tmp->next;
		index++;
	} while (tmp != NULL);
	return -1;
}
template <class T>
bool DLinkedList<T>::contains(const T& item)
{
	if (this->count == 0) return false;
	Node* tmp = this->head;
	int index = 0;
	do
	{
		if (tmp->data == item) return true;
		tmp = tmp->next;
		index++;
	} while (tmp != NULL);
	return false;
}
template <class T>
void DLinkedList<T>::clear()
{
	Node* temp;
	while (this->head != NULL)
	{
		temp = this->head;
		this->head = this->head->next;
		delete temp;
	}
	this->count = 0;
}