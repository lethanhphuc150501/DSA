#include "DLinkedList.h"

template<class T>
class Queue {
protected:
	DLinkedList<T> list;
public:
	Queue() {}
	void push(T item);
	T pop();
	T top();
	bool empty();
	int size();
	void clear();
};

template<class T>
void Queue<T>::push(T item)
{
	list.add(item);
}
template<class T>
T Queue<T>::pop()
{
	return list.removeAt(0);
}
template<class T>
T Queue<T>::top()
{
	return list.get(0);
}
template<class T>
bool Queue<T>::empty()
{
	return list.empty();
}
template<class T>
int Queue<T>::size()
{
	return list.size();
}
template <class T>
void Queue<T>::clear()
{
	list.clear();
}