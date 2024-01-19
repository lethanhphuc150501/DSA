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

    void printInOrder(Node* root) {
        if (root == NULL) return;
        printInOrder(root->pLeft);
        cout << root->data << " ";
        printInOrder(root->pRight);
    }

    void printInorder() {
        printInOrder(this->root);
    }

    bool search(const T &value, Node* root) {
        if (root == NULL) return false;
        if (value < root->data) search(value, root->pLeft);
        else if (value > root->data) search(value, root->pRight);
        else return true;
    }

    bool search(const T &value) {
        return search(value, this->root);
    }
    Node* deleteRightBalance(Node* root, bool* shorter) {
        if (root->balance == LH) root->balance = EH;
        else if (root->balance == EH) {
            root->balance = RH;
            *shorter = false;
        } else {
            Node* rightTree = root->pRight;
            if (rightTree->balance == LH) {
                Node* leftTree = rightTree->pLeft;
                switch (leftTree->balance) {
                case LH:
                    rightTree->balance = RH;
                    root->balance = EH;
                    break;
                case EH:
                    root->balance = EH;
                    rightTree->balance = EH;
                    break;
                case RH:
                    root->balance = LH;
                    rightTree->balance = EH;
                    break;
                default:
                    break;
                }
                leftTree->balance = EH;
                root->pRight = rotateRight(rightTree);
                root = rotateLeft(root);
            } else {
                if (rightTree->balance != EH) {
                    root->balance = EH;
                    rightTree->balance = EH;
                } else {
                    root->balance = RH;
                    rightTree->balance = LH;
                    *shorter = false;
                }
                root = rotateLeft(root);
            }
        }
        return root;
    }
    Node* deleteLeftBalance(Node* root, bool* shorter) {
        if (root->balance == RH) root->balance = EH;
        else if (root->balance == EH) {
            root->balance = LH;
            *shorter = false;
        } else {
            Node* leftTree = root->pLeft;
            if (leftTree->balance == RH) {
                Node* rightTree = leftTree->pRight;
                switch (rightTree->balance) {
                case LH:
                    leftTree->balance = EH;
                    root->balance = RH;
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
            } else {
                if (leftTree->balance != EH) {
                    root->balance = EH;
                    leftTree->balance = EH;
                } else {
                    root->balance = LH;
                    leftTree->balance = RH;
                    *shorter = false;
                }
                root = rotateRight(root);
            }
        }
        return root;
    }
    Node* AVLDelete(const T &value, Node* root, bool* shorter, bool* success) {
        if (root == NULL) {
            *shorter = false;
            *success = false;
            return NULL;
        }
        if (value < root->data) {
            root->pLeft = AVLDelete(value, root->pLeft, shorter, success);
            if (*shorter) root = deleteRightBalance(root, shorter);
        } else if (value > root->data) {
            root->pRight = AVLDelete(value, root->pRight, shorter, success);
            if (*shorter) root = deleteLeftBalance(root, shorter);
        } else {
            Node* deleteNode = root;
            if (root->pRight == NULL) {
                Node* newRoot = root->pLeft;
                *success = true;
                *shorter = true;
                delete deleteNode;
                return newRoot;
            } else if (root->pLeft == NULL) {
                Node* newRoot = root->pRight;
                *success = true;
                *shorter = true;
                delete deleteNode;
                return newRoot;
            } else {
                Node* exchPtr = root->pLeft;
                while (exchPtr->pRight != NULL) {
                    exchPtr = exchPtr->pRight;
                }
                root->data = exchPtr->data;
                root->pLeft = AVLDelete(exchPtr->data, root->pLeft, shorter, success);
                if (*shorter) root = deleteRightBalance(root, shorter);
            }
        }
        return root;
    }
    void remove(const T &value) {
        bool shorter = false;
        bool success = false;
        this->root = AVLDelete(value, this->root, &shorter, &success);
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
    int arr[] = {10,52,98,32,68,92,40,13,42,63,99,100};
    for (int i = 0; i < 12; i++){
        avl.insert(arr[i]);
    }
    avl.remove(10);
    avl.remove(52);
    avl.remove(98);
    avl.printTreeStructure();
    avl.remove(32);
    avl.remove(68);
    avl.printTreeStructure();
    return 0;
}