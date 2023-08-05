#include <iostream>

using namespace std;

class Node
{
public:
	Node(int data = 0, Node* next = NULL);
	~Node();
	void set(int data, Node* next)
	{
		this->data = data;
		this->next = next;
	}

	Node* get_next(Node* pre)
	{
		return pre->next;
	}

	int get_data()
	{
		return this->data;
	}
private:
	int data;
	Node* next;
};

Node::Node(int data, Node* next)
{
	this->data = data;
	this->next = next;
}

int main()
{
	Node* head = new Node();
	Node* next_node = new Node(15, NULL);
	head->set(10, next_node);
	Node* temp = head->get_next(head);
	cout << temp->get_data();
	return 0;
}