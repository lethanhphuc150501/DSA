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
    BinarySearchTree<int> bst;
bst.add(9);
bst.add(2);
bst.add(10);
bst.add(8);
cout << bst.inOrder()<<endl;
bst.add(11);
bst.deleteNode(9);
cout << bst.inOrder();
    return 0;
}