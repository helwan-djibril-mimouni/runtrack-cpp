#include <iostream>

class Shape {
public:
    virtual void draw() const = 0;

    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Circle." << std::endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Rectangle." << std::endl;
    }
};

template <typename T>
void drawShape(const T& shape) {
    shape.draw();
}

int main() {
    Circle circle;
    Rectangle rectangle;

    drawShape(circle);
    drawShape(rectangle);

    return 0;
}