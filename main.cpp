#include "main.h"
#include "restaurant.cpp"

int main(int argc, char* argv[]) {
    // string fileName = "test.txt";
    // simulate(fileName);
    MAXSIZE = 5;
    struct min_heap_S* Sukana_restaurant = initSukunaRestaurant();
    for (int i = 0; i < 20; i++) {
        Sukana_restaurant = addCustomertoSukuna(Sukana_restaurant, i);
    }
    return 0;
}