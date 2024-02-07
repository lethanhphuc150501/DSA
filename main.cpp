#include "main.h"
#include "restaurant.cpp"

int main(int argc, char* argv[]) {
    // string fileName = "test.txt";
    // simulate(fileName);
    struct customer_seat_G* root = NULL;
    root = addBST(root, 9);
    root = addBST(root, 2);
    root = addBST(root, 10);
    root = addBST(root, 8);
    root = addBST(root, 9);
    root = addBST(root, 11);
    return 0;
}