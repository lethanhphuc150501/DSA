#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

using namespace std;

class LinkedList {
public:
	class Node;
private:
	Node* head;
	Node* tail;
	int size;
public:
	class Node {
	private:
		int value;
		Node* next;
		friend class LinkedList;
	public:
		Node() {
			this->next = NULL;
		}
		Node(Node* node) {
			this->value = node->value;
			this->next = node->next;
		} 
		Node(int value, Node* next = NULL) {
			this->value = value;
			this->next = next;
		}
	};
	LinkedList() : head(NULL), tail(NULL), size(0) {};
	void add(int value)
	{
		Node* pNew = new Node(value);
		if (head == NULL || tail == NULL)
		{
			head = pNew;
			tail = pNew;
			head->next = tail;
			tail->next = NULL;
		}
		else
		{
			tail->next = pNew;
			tail = pNew;
		}
		this->size++;
	}
	string toString()
	{
		stringstream ss;
		Node* temp = head;
		while (temp != NULL)
		{
			ss << temp->value << " ";
			temp = temp->next;
		}
		return ss.str();
	}
	void partition(int k);
	void replace(LinkedList* linked_list, int low, int high);
};

void LinkedList::partition(int k)
{
	LinkedList smaller, equal, greater;
	Node* temp = this->head;
	while (temp)
	{
		if (temp->value < k)
		{
			smaller.add(temp->value);
		}
		else if (temp->value == k)
		{
			equal.add(temp->value);
		}
		else
		{
			greater.add(temp->value);
		}
		temp = temp->next;
	}
	this->head = smaller.head;
	smaller.tail->next = equal.head;
	equal.tail->next = greater.head;
}
void LinkedList::replace(LinkedList* linked_list, int low, int high)
{
	Node* temp = this->head;
	Node* preLow;
	Node* pLow;
	Node* pHigh;
	int current = 0;
	for (current = 0; current < low - 1; current++)
	{
		temp = temp->next;
	}
	if (low < 1)
	{
		preLow = NULL;
		pLow = this->head;
	}
	else
	{
		preLow = temp;
		pLow = temp->next;
	}
	for (current; current < high; current++)
	{
		temp = temp->next;
		if (current >= this->size - 1) break;
	}
	
	if (preLow == NULL) this->head = linked_list->head;
	else preLow->next = linked_list->head;
	if (temp != NULL)
	{
		pHigh = temp;
		linked_list->tail->next = temp->next;
	}
	else
	{
		pHigh = this->tail;
		this->tail = linked_list->tail;
	}
	
	while (pLow != pHigh)
	{
		Node* del = pLow;
		pLow = pLow->next;
		delete del;
	}
	delete pHigh;
}
int main()
{
	LinkedList* l1 = new LinkedList();
	LinkedList* l2 = new LinkedList();
	l1->add(10); l1->add(20); l1->add(30); l1->add(40); l1->add(50);
	l2->add(55); l2->add(45); l2->add(42);
	l1->replace(l2, 1, 3);
	cout << l1->toString() << "\n";
	return 0;
}