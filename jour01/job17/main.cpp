#include <iostream>  
#include <cstdlib>   
#include <ctime>     

enum Specialite {
    IA,             
    Web,            
    Logiciel,       
    SystemeImmersif, 
    Cybersécurité   
};

const int NOMBRE_SPECIALITES = 5;
int nombreEtudiants[NOMBRE_SPECIALITES];

const char* nomsSpecialites[NOMBRE_SPECIALITES] = {
    "Intelligence Artificielle",
    "Développement Web",
    "Développement Logiciel",
    "Système Immersif",
    "Cybersécurité"
};

void afficherSpecialite(Specialite s) {
    std::cout << "Spécialité: " << nomsSpecialites[s] << std::endl;
    std::cout << "Nombre d'étudiants: " << nombreEtudiants[s] << std::endl;
}

void initialiserNombreEtudiants() {
    for (int i = 0; i < NOMBRE_SPECIALITES; ++i) {
        nombreEtudiants[i] = 12 + rand() % 55;  
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    initialiserNombreEtudiants();
    for (int i = 0; i < NOMBRE_SPECIALITES; ++i) {
        afficherSpecialite(static_cast<Specialite>(i));
        std::cout << std::endl;
    }
    return 0; 
}