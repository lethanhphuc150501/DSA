#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function
    void recursiveAdd(Node*& node, T value) {
        if (node == NULL) {
            node = new Node(value);
        } else {
            if (value > node->value) recursiveAdd(node->pRight, value);
            else recursiveAdd(node->pLeft, value);
        }
    }

    void add(T value){
        recursiveAdd(this->root, value);
    }

    void recursiveDeteleNode(Node*& root, T value) {
        if (root == NULL) return;
        if (value > root->value) recursiveDeteleNode(root->pRight, value);
        else if (value < root->value) recursiveDeteleNode(root->pLeft, value);
        else {
            if (root->pLeft == NULL) {
                Node *dltPtr = root;
                root = root->pRight;
                delete dltPtr;
                return;
            } else if (root->pRight == NULL) {
                Node *dltPtr = root;
                root = root->pLeft;
                delete dltPtr;
                return;
            } else {
                Node *dltPtr = root->pRight;
                while (dltPtr->pLeft != NULL) {
                    dltPtr = dltPtr->pLeft;
                }
                root->value = dltPtr->value;
                recursiveDeteleNode(root->pRight, dltPtr->value);
            }
        }
    }
   
    void deleteNode(T value){
        recursiveDeteleNode(this->root, value);
    }
    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    T getMin() {
        Node *tmp = this->root;
        if (tmp == NULL) return 0;
        while (tmp->pLeft != NULL) {
            tmp = tmp->pLeft;
        }
        return tmp->value;
    }

    T getMax() {
        Node *tmp = this->root;
        if (tmp == NULL) return 0;
        while (tmp->pRight != NULL) {
            tmp = tmp->pRight;
        }
        return tmp->value;
    }

    bool find(T i, Node* node) {
        if (node == NULL) return false;
        if (i < node->value) find(i, node->pLeft);
        else if (i > node->value) find(i, node->pRight);
        else return true;
    }

    bool find(T i) {
        return find(i, this->root);
    }

    T sum(Node* node, T l, T r) {
        if (node == NULL) return 0;
        int left = sum(node->pLeft, l, r);
        int right = sum(node->pRight, l, r);
        if (node->value >= l && node->value <= r) return node->value + left + right;
        else return left + right;
    }

    T sum(T l, T r) {
        return sum(this->root, l, r);
    }
    
    string inOrder(){
        return inOrderRec(this->root);
    }
    
    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

int main() {
    int values[] = { 75,13,83,83,30,40,10,86,17,21,45,22,22,72,63 };
    BinarySearchTree<int> bst;
    for (int i = 0; i < 15; ++i) {
        bst.add(values[i]);
    }

    cout << bst.find(34) << endl;
    cout << bst.sum(10, 40);
    return 0;
}