#include <iostream>

bool isNumEven(int x){
    return x%2 == 0;   
}

int main()
{
    int x;
    std::cout << "x : ";
    std::cin >> x;
    if (isNumEven(x)){
        std::cout << x << " is even";
    }
    else{
        std::cout << x << " is odd";
    }
}