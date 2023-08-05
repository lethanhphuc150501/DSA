// Online C++ compiler to run C++ program online
#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>
using namespace std;

template <class T>
class SLinkedList
{
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList() : head(NULL), tail(NULL), count(0) {};
    ~SLinkedList() { };
    void add(T e);
    void add(int index, T e);
    int size();
    bool empty();
    void clear();
    Node* get_head()
    {
        return this->head;
    }
    T get(int index);
    void set(int index, T e);
    int indexOf(T item);
    bool contains(T item);
    T removeAt(int index);
    bool removeItem(T item);
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
    void array_to_list(T* arr, int size)
    {
        for (int index = 0; index < size; index++)
        {
            add(*arr);
            arr++;
        }
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
            this->next = NULL;
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
        string toString()
        {
            stringstream ss;
            Node* temp = this;
            while (temp != NULL)
            {
                ss << temp->data << " ";
                temp = temp->next;
            }
            return ss.str();
        }
        Node* foldedLinkedList(Node* head)
        {
            Node* temp = head;
            //Find the size of array
            int size = 0;
            while (temp != NULL)
            {
                temp = temp->next;
                size++;
            }
            temp = head;

            //Copy the first half list to the folded list
            int fd_size = (size % 2) ? (size / 2 + 1) : (size / 2);
            Node* fd_head = new Node();
            fd_head->data = temp->data;
            for (int i = 1; i < fd_size; i++)
            {
                temp = temp->next;
                Node* pNew = new Node(temp->data, fd_head);
                fd_head = pNew;
            }

            //Add the rest list with folded list
            Node* fd_temp = fd_head;
            if (size % 2 == 1)
            {
                fd_temp = fd_temp->next;
            }
            for (int i = fd_size; i < size; i++)
            {
                temp = temp->next;
                fd_temp->data += temp->data;
                fd_temp = fd_temp->next;
            }            
            return fd_head;
        }
        Node* replaceFirstGreater(Node* head)
        {
            Node* temp = head;
            Node* rpl_head = new Node();
            
            Node* aux_temp = temp->next;
            while (aux_temp)
            {
                if (aux_temp->data > temp->data)
                {
                    rpl_head->data = aux_temp->data;
                    break;
                }
                else
                {
                    rpl_head->data = 0;
                }
                aux_temp = aux_temp->next;
            }

            Node* rpl_temp = rpl_head;
            
            temp = temp->next;
            while (temp)
            {
                Node* aux_rpl_temp = new Node();
                rpl_temp->next = aux_rpl_temp;
                aux_temp = temp->next;
                while (aux_temp)
                {
                    if (aux_temp->data > temp->data)
                    {
                        aux_rpl_temp->data = aux_temp->data;
                        break;
                    }
                    else
                    {
                        aux_rpl_temp->data = 0;
                    }
                    aux_temp = aux_temp->next;
                }
                temp = temp->next;
                rpl_temp = rpl_temp->next;
            }
            return rpl_head;
        }
        Node* rotateLinkedList(Node* head, int k)
        {
            for (int i = 0; i < k; i++)
            {
                Node* temp = head->next;
                Node* second = head;
                while ((temp->next)->next)
                {
                    temp = temp->next;
                }
                head = temp->next;
                temp->next = NULL;
                head->next = second;
            }
            return head;
        }
        Node* reverseLinkedList(Node* head)
        {
            Node* temp = head->next;
            Node* rv_node = new Node(head->data);
            while (temp)
            {
                Node* pNew = new Node(temp->data, rv_node);
                rv_node = pNew;
                temp = temp->next;
            }            
            return rv_node;
        }
    };
};

template <class T>
void SLinkedList<T>::add(T e)
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
void SLinkedList<T>::add(int index, T e)
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
void SLinkedList<T>::set(int index, T e)
{
    Node* temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    temp->data = e;
}
template <class T>
int SLinkedList<T>::indexOf(T item)
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
bool SLinkedList<T>::contains(T item)
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
bool SLinkedList<T>::removeItem(T item)
{
    Node* temp = head;
    int pre_count = this->count;
    for (int index = 0; index < this->count; index++)
    {
        if (temp->data == item)
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

template class SLinkedList<int>;
int main() {
    Stack<int> stack;
    int item[] = { 3, 1, 4, 5, 2, 8, 10, 12 };
    for (int idx = 0; idx < 8; idx++) stack.push(item[idx]);
    assert(stack.top() == 12);
    stack.pop();
    stack.pop();
    cout << stack.top();
    return 0;
}