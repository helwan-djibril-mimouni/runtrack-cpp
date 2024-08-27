#include <iostream>

int multiplyNum(int a, int b){
    return a * b;
}

int main()
{
    int a;
    int b;
    std::cout << "a : ";
    std::cin >> a;
    std::cout << "b : ";
    std::cin >> b;
    int c = multiplyNum(a, b);
    std::cout << a << " * " << b << " = " << c;
}