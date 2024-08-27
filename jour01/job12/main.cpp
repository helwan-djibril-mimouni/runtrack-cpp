#include <iostream>

int doubleArray(int *tab, int size)
{
    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        tab[i] *= 2;
        sum += tab[i];
    }
    return sum;
}

void printArray(int* tab, int size) {
    std::cout << "Array : ";
    for (int i = 0; i < size; ++i) {
        std::cout << *(tab + i) << " ";  
    }
    std::cout << std::endl;
}

int main()
{
    int size;
    std::cout << "Size of Array :" << std::endl;
    std::cin >> size;
    int tab[size];
    for (size_t i = 0; i < size; i++)
    {
        std::cout << "Number #" << i+1 << std::endl;
        std::cin >> tab[i];
    }
    printArray(tab, size);
    std::cout << "Sum of doubled array : " << doubleArray(tab, size) << std::endl;
    printArray(tab, size);
}