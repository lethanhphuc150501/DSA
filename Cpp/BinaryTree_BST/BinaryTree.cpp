#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;  // Cho phép lớp Binary Tree truy cập vào vùng private của lớp Node
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }
    // STUDENT ANSWER BEGIN 
    int tree_height(Node* root) {
        if (root == NULL) return 0;
        Node* tmp = root;
        int left = tree_height(root->pLeft);
        int right = tree_height(root->pRight);
        if (left > right) return 1 + left;
        else return 1 + right;
    }

    int getHeight() {
        // TODO: return height of the binary tree.
        return tree_height(root);
    }

    void printPreorder(struct Node* node) {
        if (node == NULL) return;
        cout << node->value << " ";
        printPreorder(node->pLeft);
        printPreorder(node->pRight);
    }

    string preOrder() {
        // TODO: return the sequence of values of nodes in pre-order.
        printPreorder(root);
        return "";
    }

    void printInorder(struct Node* node) {
        if (node == NULL) return;
        printInorder(node->pLeft);
        cout << node->value << " ";
        printPostorder(node->pRight);
    }

    string inOrder() {
        // TODO: return the sequence of values of nodes in in-order.
        printInorder(root);
        return "";
    }

    void printPostorder(struct Node* node) {
        if (node == NULL) return;
        printPostorder(node->pLeft);
        printPostorder(node->pRight);
        cout << node->value << " ";
    }

    string postOrder() {
        printPostorder(root);
        return "";
    }
    // STUDENT ANSWER END
};

int main() {
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("",2, 4);
    binaryTree.addNode("L",3, 6);
    binaryTree.addNode("R",5, 9);
    binaryTree.addNode("LL",4, 10);
    binaryTree.addNode("LR",6, -3);
    binaryTree.addNode("LLL",7, 2);
    binaryTree.addNode("LLLR",8, 7);
    binaryTree.addNode("RR",9, 30);
    binaryTree.addNode("RL",10, 307);
    binaryTree.addNode("RLL",11, 2000);
    binaryTree.addNode("RLLL",11, 2000);

    cout << binaryTree.getHeight() << endl;
    cout << binaryTree.preOrder() << endl;
    cout << binaryTree.inOrder() << endl;
    cout << binaryTree.postOrder() << endl;
    return 0;
}