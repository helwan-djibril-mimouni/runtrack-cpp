#include <iostream> 

constexpr int fibonacci(int n) {
    return (n <= 1) ? n : (fibonacci(n - 1) + fibonacci(n - 2));
}

bool estNombreBitsUnPair(unsigned int nombre) {
    int compteBits = 0;
    while (nombre) {
        compteBits += (nombre & 1);  
        nombre >>= 1;  
    }
    return (compteBits % 2 == 0);
}

int main() {
    std::cout << "Les dix premiers termes de la suite de Fibonacci sont :" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << fibonacci(i) << " ";  
    }
    std::cout << std::endl;
    unsigned int nombre;
    std::cout << "Entrez un nombre non-signé de 32 bits : ";
    std::cin >> nombre;
    if (estNombreBitsUnPair(nombre)) {
        std::cout << "Le nombre de bits à 1 dans " << nombre << " est pair." << std::endl;
    } else {
        std::cout << "Le nombre de bits à 1 dans " << nombre << " est impair." << std::endl;
    }
    return 0; 
}