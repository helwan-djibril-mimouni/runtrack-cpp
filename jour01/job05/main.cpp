#include <iostream>

void switchPlaces(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a;
    std::cout << "a : ";
    std::cin >> a;
    int b;
    std::cout << "b : ";
    std::cin >> b;
    std::cout << "Numbers before switching : a=" << a << " and b=" << b << std::endl;
    switchPlaces(&a, &b);
    std::cout << "Numbers after switching : a=" << a << " and b=" << b;
}