#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

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

class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(const std::string& shapeType) {
        if (shapeType == "circle") {
            return std::make_unique<Circle>();
        } else if (shapeType == "rectangle") {
            return std::make_unique<Rectangle>();
        } else {
            throw std::runtime_error("Type de forme non supporté : " + shapeType);
        }
    }
};

int main() {
    try {
        std::unique_ptr<Shape> shape1 = ShapeFactory::createShape("circle");
        shape1->draw();

        std::unique_ptr<Shape> shape2 = ShapeFactory::createShape("rectangle");
        shape2->draw();

        std::unique_ptr<Shape> shape3 = ShapeFactory::createShape("triangle");
        shape3->draw();
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}