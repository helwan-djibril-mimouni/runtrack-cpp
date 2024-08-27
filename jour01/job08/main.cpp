#include <iostream>

bool isBisextile(int x){
    if (x%4 == 0){
        if (x%100 == 0){
            if (x%400 == 0){
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

int main()
{
    int x;
    std::cout << "x : ";
    std::cin >> x;
    if (isBisextile(x)){
        std::cout << x << " is a leap year";
    }
    else{
        std::cout << x << " is not a leap year";
    }
}