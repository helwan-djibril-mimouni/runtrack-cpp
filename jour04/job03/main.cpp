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

template <typename T>
class Box<T*>
{
private:
    T* element;
public:
    Box(T* e);
    ~Box();
    T& getElement();
};

template <typename T>
Box<T*>::Box(T* e) : element{e}
{
}

template <typename T>
Box<T*>::~Box()
{
}

template <typename T>
T& Box<T*>::getElement()
{
    return *element;
}

int main()
{
    Box<int> b1 = Box<int>(3);
    Box<double> b2 = Box<double>(3.14);
    Box<char> b3 = Box<char>('c');
    std::cout << "b1 : " << b1.getElement() << std::endl;
    std::cout << "b2 : " << b2.getElement() << std::endl;
    std::cout << "b3 : " << b3.getElement() << std::endl;

    int i = 1;
    double d = 1.5;
    char c = 'a';
    Box<int*> bp1 = Box<int*>(&i);
    Box<double*> bp2 = Box<double*>(&d);
    Box<char*> bp3 = Box<char*>(&c);
    std::cout << "bp1 : " << bp1.getElement() << std::endl;
    std::cout << "bp2 : " << bp2.getElement() << std::endl;
    std::cout << "bp3 : " << bp3.getElement() << std::endl;
}
