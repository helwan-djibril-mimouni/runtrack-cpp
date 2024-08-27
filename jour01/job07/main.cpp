#include <iostream>

int invertNumber(int n){
    int i = 1;
    int reverse = 0;
    while (i <= n){
        i *= 10;
        reverse *= 10;
        reverse += (n%i)/(i/10);
    }
    return reverse;
}

int main()
{
    int n;
    std::cout << "n : ";
    std::cin >> n;
    int reverse = invertNumber(n);
    std::cout << "Number before inverse : " << n << std::endl;
    std::cout << "Number after inverse : " << reverse;
}