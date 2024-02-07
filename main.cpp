#include "main.h"
#include "restaurant.cpp"

int main(int argc, char* argv[]) {
    // string fileName = "test.txt";
    // simulate(fileName);
    MAXSIZE = 3;
    struct area_G* Gojo_restaurant = initGojoRestaurant();
    for (int i = 10; i < 15; i++) Gojo_restaurant = addCustomertoGojo(Gojo_restaurant, i);
    for (int i = 4; i >= 0; i--) Gojo_restaurant = addCustomertoGojo(Gojo_restaurant, i);
    for (int i = 19; i >= 15; i--) Gojo_restaurant = addCustomertoGojo(Gojo_restaurant, i);
    for (int i = 5; i < 10; i++) Gojo_restaurant = addCustomertoGojo(Gojo_restaurant, i);
    return 0;
}