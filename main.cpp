#include "main.h"
#include "restaurant.cpp"

int main(int argc, char* argv[]) {
    // string fileName = "test.txt";
    // simulate(fileName);
    MAXSIZE = 7;
    g_Sukuna_restaurant = initSukunaRestaurant();
    for (int i = 0; i < 20; i++) {
        g_Sukuna_restaurant = addCustomertoSukuna(g_Sukuna_restaurant, i);
    }
    CLEAVE(3);  // 2 cases: NUM = 2, 3
    return 0;
}