#include "main.h"
#include "restaurant.cpp"

int main(int argc, char* argv[]) {
    // string fileName = "test.txt";
    // simulate(fileName);
    MAXSIZE = 7;
    g_Gojo_restaurant = initGojoRestaurant();
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 22);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 23);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 11);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 14);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 20);
    for (int i = 10; i >= 0; i -= 2) {
        g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, i);
    }
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 15);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 1);
    for (int i = 21; i >= 9; i--) {
        g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, i);
    }
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 43);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 29);
    for (int i = 23; i < 43; i += 3) {
        g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, i);
    }
    KOKUSEN();
    return 0;
}