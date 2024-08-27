#include <iostream> 

int main() {
    int n; 
    int sum = 0;  
    std::cout << "Number (n>5) : ";
    std::cin >> n;
    if (n < 5) {
        std::cout << "Error, number lower than 5" << std::endl;
        return 1;
    }
    for (int i = 5; i <= n; ++i) {
        sum += i*i*i;  
    }
    std::cout << "Sum : " << sum << std::endl;
    return 0;  
}