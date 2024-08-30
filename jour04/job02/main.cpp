#include <iostream>

template<typename T>
class Box
{
private:
    T element;
public:
    Box(T e);
    ~Box();
    T getElement();
};

template <typename T>
Box<T>::Box(T e) : element{e}
{
}

template <typename T>
Box<T>::~Box()
{
}

template <typename T>
T Box<T>::getElement()
{
    return element;
}

int main()
{
    Box<int> b1 = Box<int>(3);
    Box<double> b2 = Box<double>(3.14);
    Box<char> b3 = Box<char>('c');
    std::cout << "b1 : " << b1.getElement() << std::endl;
    std::cout << "b2 : " << b2.getElement() << std::endl;
    std::cout << "b3 : " << b3.getElement() << std::endl;
}
