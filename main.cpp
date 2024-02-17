#include "main.h"
#include "restaurant.cpp"

int main(int argc, char* argv[]) {
    // string fileName = "test.txt";
    // simulate(fileName);
    MAXSIZE = 7;
    g_Gojo_restaurant = initGojoRestaurant();
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 22);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 8);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 15);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 1);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 43);
    g_Gojo_restaurant = addCustomertoGojo(g_Gojo_restaurant, 29);
    cout << numOfWays(g_Gojo_restaurant[1].root);
    return 0;
}