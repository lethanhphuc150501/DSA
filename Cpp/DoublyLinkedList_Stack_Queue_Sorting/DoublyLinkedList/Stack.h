#include "DLinkedList.h"

template<class T>
class Stack {
protected:
	DLinkedList<T> list;
public:
	Stack() {}
	void push(T item);
	T pop();
	T top();
	bool empty();
	int size();
	void clear();
};

template<class T>
void Stack<T>::push(T item)
{
	list.add(0, item);
}
template<class T>
T Stack<T>::pop()
{
	return list.removeAt(0);
}
template<class T>
T Stack<T>::top()
{
	return list.get(0);
}
template<class T>
bool Stack<T>::empty()
{
	return list.empty();
}
template<class T>
int Stack<T>::size()
{
	return list.size();
}
template <class T>
void Stack<T>::clear()
{
	list.clear();
}