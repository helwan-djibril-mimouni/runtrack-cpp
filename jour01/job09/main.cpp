#include <iostream>

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
    int min = NULL;
    for (int j : tab){
        if (min == NULL){
            min = j;
        }
        else{
            if (min > j){
                min = j;
            }
        }
    }
    std::cout << "Lowest number is " << min << std::endl;
}