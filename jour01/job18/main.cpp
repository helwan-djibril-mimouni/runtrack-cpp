#include <iostream>  

int* addElement(int* tableau, int tailleActuelle, int nouvelElement, int& nouvelleTaille) {
    nouvelleTaille = tailleActuelle + 1;
    int* nouveauTableau = new int[nouvelleTaille];
    for (int i = 0; i < tailleActuelle; ++i) {
        nouveauTableau[i] = tableau[i];
    }
    nouveauTableau[tailleActuelle] = nouvelElement;
    delete[] tableau;
    return nouveauTableau;
}

void showTable(const int* tableau, int taille) {
    std::cout << "Tableau : ";
    for (int i = 0; i < taille; ++i) {
        std::cout << tableau[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int tailleActuelle = 0;
    int capaciteInitiale = 5;
    int* tableau = new int[capaciteInitiale];
    tableau = addElement(tableau, tailleActuelle, 10, tailleActuelle);
    tableau = addElement(tableau, tailleActuelle, 20, tailleActuelle);
    tableau = addElement(tableau, tailleActuelle, 30, tailleActuelle);
    tableau = addElement(tableau, tailleActuelle, 40, tailleActuelle);
    tableau = addElement(tableau, tailleActuelle, 50, tailleActuelle);
    tableau = addElement(tableau, tailleActuelle, 60, tailleActuelle);
    showTable(tableau, tailleActuelle);
    delete[] tableau;
    return 0;
}