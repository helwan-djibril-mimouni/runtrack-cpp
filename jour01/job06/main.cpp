#include <iostream>

int main()
{
    double priceHT;
    std::cout << "Prix HT d'un kilo de carottes (en $) : ";
    std::cin >> priceHT;
    int kilos;
    std::cout << "Nombre de kilos de carottes : ";
    std::cin >> kilos;
    double tva;
    std::cout << "Taux de TVA (en %) : ";
    std::cin >> tva;
    std::cout << kilos << " kilos de carottes valent " << (kilos*priceHT)*((tva/100)+1) << "$";
}