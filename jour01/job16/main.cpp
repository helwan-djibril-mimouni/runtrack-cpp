#include <iostream>
#include <cstring>  

void swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

void MySortString(char* tableau[], int taille) {
    for (int i = 0; i < taille - 1; ++i) {
        for (int j = 0; j < taille - 1 - i; ++j) {
            if (strcmp(tableau[j], tableau[j + 1]) > 0) {
                swap(&tableau[j], &tableau[j + 1]);
            }
        }
    }
}

int main() {
    const int TAILLE = 5;
    char* tableau[TAILLE] = {
        (char*)"Banane",
        (char*)"Pomme",
        (char*)"Orange",
        (char*)"Fraise",
        (char*)"Cerise"
    };
    std::cout << "Avant le tri : " << std::endl;
    for (int i = 0; i < TAILLE; ++i) {
        std::cout << tableau[i] << std::endl;
    }
    MySortString(tableau, TAILLE);
    std::cout << "Après le tri : " << std::endl;
    for (int i = 0; i < TAILLE; ++i) {
        std::cout << tableau[i] << std::endl;
    }
    return 0;  
}