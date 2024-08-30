#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
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
    template <typename T>
    static void registerShape(const std::string& shapeType) {
        creators()[shapeType] = []() -> std::unique_ptr<Shape> {
            return std::make_unique<T>();
        };
    }

    static std::unique_ptr<Shape> createShape(const std::string& shapeType) {
        auto it = creators().find(shapeType);
        if (it != creators().end()) {
            return it->second();
        } else {
            throw std::runtime_error("Type de forme non supporté : " + shapeType);
        }
    }

private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Shape>()>>& creators() {
        static std::unordered_map<std::string, std::function<std::unique_ptr<Shape>()>> shapeCreators;
        return shapeCreators;
    }
};

int main() {
    ShapeFactory::registerShape<Circle>("circle");
    ShapeFactory::registerShape<Rectangle>("rectangle");

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