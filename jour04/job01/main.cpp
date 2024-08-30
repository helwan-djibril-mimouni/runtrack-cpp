#include <iostream>

template<typename T>
T max(T a, T b){
    return a < b ? b : a;
}

int main()
{
    std::cout << "max of 1 & 3 : " << max(1, 3) << std::endl;
    std::cout << "max of 1.2 & 3.7 : " << max(1.2, 3.7) << std::endl;
    std::cout << "max of a & c : " << max('a', 'c') << std::endl;
}