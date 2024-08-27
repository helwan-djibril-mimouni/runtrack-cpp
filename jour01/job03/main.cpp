#include <iostream>

int main()
{
    double avg = 0;
    std::cout << "Average of 5 numbers" << std::endl;
    int x;
    std::cout << "1st number : ";
    std::cin >> x;
    avg += x;
    std::cout << "2nd number : ";
    std::cin >> x;
    avg += x;
    std::cout << "3rd number : ";
    std::cin >> x;
    avg += x;
    std::cout << "4th number : ";
    std::cin >> x;
    avg += x;
    std::cout << "5th number : ";
    std::cin >> x;
    avg += x;
    avg /= 5;
    std::cout << "Average : " << avg;
}