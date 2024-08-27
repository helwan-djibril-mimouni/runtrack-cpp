#include <iostream>

bool EqualNumber(unsigned int A, unsigned int B)
{
    return ( A ^ B ) ;
}

bool estBitsPair(unsigned int nombre) {
    unsigned int bits = nombre;
    unsigned int pair = 0;
    for (size_t i = 0; i < 32; i++)
    {
        if (!EqualNumber(bits%10, 0)){
            bits -= 1;
            pair++;
        }
        bits /= 10;
    }    
    return EqualNumber(pair%2, 0);
}

int main() {
    unsigned int nombre;
    std::cout << "Entrez un nombre non-signe de 32 bits : ";
    std::cin >> nombre;
    if (estBitsPair(nombre)) {
        std::cout << "Le nombre de bits à 1 dans " << nombre << " est pair." << std::endl;
    } else {
        std::cout << "Le nombre de bits à 1 dans " << nombre << " est impair." << std::endl;
    }
    return 0; 
}