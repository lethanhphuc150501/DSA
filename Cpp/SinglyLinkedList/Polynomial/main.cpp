#include <iostream>
#include <assert.h>
#include <string.h>
#include <sstream>

using namespace std;

template <class T>
class SLinkedList
{
public:
	class Iterator; //forward declaration
	class Node; //forward declaration
protected:
	Node* head;
	Node* tail;
	int count;
public:
	SLinkedList() : head(NULL), tail(NULL), count(0) {};
	~SLinkedList();
	void add(const T& e);
	void add(int index, const T& e);
	T removeAt(int index);
	bool removeItem(const T& removeItem);
	bool empty();
	int size();
	void clear();
	T get(int index);
	void set(int index, const T& e);
	int indexOf(const T& item);
	bool contains(const T& item);
	string toString()
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
	SLinkedList(const SLinkedList& list)
	{
		this->count = 0;
		this->head = NULL;
		this->tail = NULL;
	}
	Iterator begin()
	{
		return Iterator(this, true);
	}
	Iterator end()
	{
		return Iterator(this, false);
	}
public:
	class Node
	{
	private:
		T data;
		Node* next;
		friend class SLinkedList<T>;
	public:
		Node()
		{
			next = 0;
		}
		Node(Node* next)
		{
			this->next = next;
		}
		Node(T data, Node* next = NULL)
		{
			this->data = data;
			this->next = next;
		}
	};
	class Iterator
	{
	private:
		SLinkedList<T>* pList;
		Node* current;
		int index; // corresponding with current node
	public:
		Iterator(SLinkedList<T>* pList, bool begin);
		Iterator& operator=(const Iterator& iterator);
        void remove();
		void set(const T& e);
		T& operator*();
		bool operator!=(const Iterator& iterator);
		// Prefix ++ overload
		Iterator& operator++();
		// Postfix ++ overload
		Iterator operator++(int);
	};
};

template <class T>
void SLinkedList<T>::add(const T& e)
{
    Node* pNew = new Node(e);
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
    this->count++;
}
template <class T>
void SLinkedList<T>::add(int index, const T& e)
{
    Node* pPre = new Node();
    Node* pNew = new Node(e);
    if (index == 0) //head
    {
        pNew->next = head;
        head = pNew;
    }
    else
    {
        pPre = head;
        for (int i = 0; i < index - 1; i++)
        {
            pPre = pPre->next;
        }
        if (pPre == NULL) //tail
        {
            add(e);
        }
        else
        {
            pNew->next = pPre->next;
            pPre->next = pNew;
        }
    }
    this->count++;
}
template <class T>
int SLinkedList<T>::size()
{
    return this->count;
}
template <class T>
bool SLinkedList<T>::empty()
{
    if (this->count == 0) return 1;
    else return 0;
}
template <class T>
T SLinkedList<T>::get(int index)
{
    Node* temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp->data;
}
template <class T>
void SLinkedList<T>::set(int index, const T& e)
{
    Node* temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    temp->data = e;
}
template <class T>
int SLinkedList<T>::indexOf(const T& item)
{
    Node* temp = head;
    int index = 0;
    while (temp != NULL)
    {
        if (temp->data == item) return index;
        temp = temp->next;
        index++;
    }
    return -1;
}
template <class T>
bool SLinkedList<T>::contains(const T& item)
{
    Node* temp = head;
    while (temp != NULL)
    {
        if (temp->data == item) return 1;
        temp = temp->next;
    }
    return 0;
}
template <class T>
T SLinkedList<T>::removeAt(int index)
{
    Node* pLoc = head;
    int value = head->data;
    if (index > 0)
    {
        Node* pPre = head;
        for (int i = 0; i < index; i++)
        {
            pLoc = pLoc->next;
            if (i > 0) pPre = pPre->next;
        }
        pPre->next = pLoc->next;
        value = pLoc->data;
        delete pLoc;
        this->count--;
    }
    else
    {
        head = pLoc->next;
        delete pLoc;
        this->count--;
    }
    return value;
}
template <class T>
bool SLinkedList<T>::removeItem(const T& removeItem)
{
    Node* temp = head;
    int pre_count = this->count;
    for (int index = 0; index < this->count; index++)
    {
        if (temp->data == removeItem)
        {
            removeAt(index);
            return true;
        }
        temp = temp->next;
    }
    return false;
}
template <class T>
void SLinkedList<T>::clear()
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

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
    this->pList = pList;
    if (begin == true)
    {
        if (pList != NULL)
        {
            this->current = pList->head;
            this->index = 0;
        }
        else
        {
            this->current = NULL;
            this->index = -1;
        }
    }
    else
    {
        this->current = NULL;
        if (pList != NULL)
        {
            this->index = pList->size();
        }
        else
        {
            this->index = 0;
        }
    }
}
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
    this->current = iterator.current;
    this->index = iterator.index;
    this->pList = iterator.pList;
    return *this;
}
template <class T>
void SLinkedList<T>::Iterator::remove()
{
    if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
        
    if (this->current == this->pList->head) //Remove the head node
    {
        this->current = NULL;
        this->index = -1;
        this->pList->removeAt(0);
    }
    else
    {
        Node* pre = this->pList->head;
        while (pre->next != this->current)
        {
            pre = pre->next;
        }
        this->current = pre;
        this->pList->removeAt(this->index);
        this->index--;
        pre = NULL; delete[] pre;
    }
}
template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
    else this->pList->set(this->index, e);
}
template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
    else return current->data;
}
template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    if (this->pList == iterator.pList && this->current == iterator.current && this->index == iterator.index) return true;
    else return false;
}
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    if (this->current == NULL)
    {
        this->current = this->pList->head;
        this->index = 0;
    }
    else
    {
        this->current = this->current->next;
        this->index++;
    }
    return *this;
}
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    Iterator iterator = *this;
    ++* this;
    return iterator;
}


class Polynomial;
class Term {
private:
    double coeff;
    int exp;
    friend class Polynomial;
public:
    Term(double coeff = 0.0, int exp = 0) {
        this->coeff = coeff;
        this->exp = exp;
    }
    bool operator==(const Term& rhs) const {
        return this->coeff == rhs.coeff && this->exp == rhs.exp;
    }
    friend ostream& operator<<(ostream& os, const Term& term) {
        cout << endl;
        cout << "Term: " << "(" << term.coeff << " " << term.exp << ")";
        return os;
    }
};
class Polynomial {
private:
    SLinkedList<Term>* terms;
public:
    Polynomial() {
        this->terms = new SLinkedList<Term>();
    }
    ~Polynomial() {
        this->terms->clear();
    }
    void insertTerm(const Term& term);
    void insertTerm(double coeff, int exp);
    void print() {
        SLinkedList<Term>::Iterator it;
        cout << "[";
        for (it = this->terms->begin(); it != this->terms->end(); it++) {
            cout << (*it);
        }
        cout << endl << "]";
    }
};
template class SLinkedList<int>;
int main()
{
    SLinkedList<int> list;
    int size = 10;
    for (int idx = 0; idx < size; idx++) {
        list.add(idx);
    }
    SLinkedList<int>::Iterator it = SLinkedList<int>::Iterator(&list, false);
    int expvalue = 0;
    for (it = list.begin(); it != list.end(); it++) {
        assert(*it == expvalue);
        expvalue += 1;
    }
	return 0;
}