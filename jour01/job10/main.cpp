#include <iostream>

int main()
{
    int a = 18, b = 13, c = 7, d = 12, e = 17, f = 3, g = 5;
    int* tab[] = {&a, &b, &c, &d, &e, &f, &g};
    int size = sizeof(tab) / sizeof(tab[0]);
    int min = NULL;
    for (size_t i = 0; i < size; i++) {
        if (min == NULL){
            min = *tab[i];
        }
        else{
            if (min > *tab[i]){
                min = *tab[i];
            }
        }
    }
    std::cout << "Lowest number is " << min << std::endl;
}