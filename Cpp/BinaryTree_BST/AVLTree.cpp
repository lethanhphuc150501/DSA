#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue {
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n) {
    for (int i = 0; i < n - 1; i++) cout << " ";
}

void printInteger(int &n) {
    cout << n << " ";
}

template<class T>
class AVLTree {
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node) {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight() {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure() {
        int height = this->getHeight();
        if (this->root == NULL) {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty()) {
            temp = q.front();
            q.pop();
            if (temp == NULL) {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode) {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height) return;
        }
    }

    Node* rotateRight(Node* root) {
        Node* tmp = root->pLeft;
        root->pLeft = tmp->pRight;
        tmp->pRight = root;
        return tmp; // new root
    }
    Node* rotateLeft(Node* root) {
        Node* tmp = root->pRight;
        root->pRight = tmp->pLeft;
        tmp->pLeft = root;
        return tmp; // new root
    }
    Node* leftBalance(Node* root, bool *taller) {
        Node* leftTree = root->pLeft;
        if (leftTree->balance == LH) {
            root->balance = EH;
            leftTree->balance = EH;
            root = rotateRight(root);
            *taller = false;
        } else {
            Node* rightTree = leftTree->pRight;
            switch (rightTree->balance) {
            case LH:
                root->balance = RH;
                leftTree->balance = EH;
                break;
            case EH:
                root->balance = EH;
                leftTree->balance = EH;
                break;
            case RH:
                root->balance = EH;
                leftTree->balance = LH;
                break;
            default:
                break;
            }
            rightTree->balance = EH;
            root->pLeft = rotateLeft(leftTree);
            root = rotateRight(root);
            *taller = false;
        }
        return root;
    }
    Node* rightBalance(Node* root, bool *taller) {
        Node* rightTree = root->pRight;
        if (rightTree->balance == RH) {
            root->balance = EH;
            rightTree->balance = EH;
            root = rotateLeft(root);
            *taller = false;
        } else {
            Node* leftTree = rightTree->pLeft;
            switch (leftTree->balance) {
            case RH:
                root->balance = LH;
                rightTree->balance = EH;
                break;
            case EH:
                root->balance = EH;
                leftTree->balance = EH;
                break;
            case LH:
                root->balance = EH;
                rightTree->balance = RH;
                break;
            default:
                break;
            }
            leftTree->balance = EH;
            root->pRight = rotateRight(rightTree);
            root = rotateLeft(root);
            *taller = false;
        }
        return root;
    }
    Node* AVLInsert(Node* root, const T &value, bool *taller) {
        if (root == NULL) {
            root = new Node(value);
            *taller = true;
            return root;
        }
        if (value < root->data) {
            root->pLeft = AVLInsert(root->pLeft, value, taller);
            if (*taller) {
                switch (root->balance) {
                case LH:
                    root = leftBalance(root, taller);
                    break;
                case EH:
                    root->balance = LH;
                    break;
                case RH:
                    root->balance = EH;
                    *taller = false;
                    break;
                default:
                    break;
                }
            }
        } else {
            root->pRight = AVLInsert(root->pRight, value, taller);
            if (*taller) {
                switch (root->balance) {
                case LH:
                    root->balance = EH;
                    *taller = false;
                    break;
                case EH:
                    root->balance = RH;
                    break;
                case RH:
                    root = rightBalance(root, taller);
                    break;
                default:
                    break;
                }
            }
        }
        return root;
    }
    
    void insert(const T &value) {
        bool taller = false;
        this->root = AVLInsert(this->root, value, &taller);
    }

    class Node {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

int main() {
    	
    AVLTree<int> avl;
    int arr[] = {25,73,89,23,14,53,51,55,17,16,21,12,14,90,6,54,12,60,8,53,86,90,69,18,69,100,0,70,77,65};
    for (int i = 0; i < 30; i++){
        avl.insert(arr[i]);
    }
    avl.printTreeStructure();
    return 0;
}