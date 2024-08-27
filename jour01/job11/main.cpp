#include <iostream>

int swapValues()
{
    int a;
    std::cout << "a : ";
    std::cin >> a;
    int b;
    std::cout << "b : ";
    std::cin >> b;
    std::cout << "Numbers before switching : a=" << a << " and b=" << b << std::endl;
    int temp = a;
    a = b;
    b = temp;
    std::cout << "Numbers after switching : a=" << a << " and b=" << b;
}

int main(){
    swapValues();
}