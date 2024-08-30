#include <iostream>
#include <cmath> 

class Vector2d {
protected:
    double x, y; 

public:
    Vector2d() : x(0), y(0) {} 
    Vector2d(double x, double y) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }

    Vector2d operator+(const Vector2d& other) const {
        return Vector2d(x + other.x, y + other.y);
    }

    Vector2d operator-(const Vector2d& other) const {
        return Vector2d(x - other.x, y - other.y);
    }

    double distance(const Vector2d& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    virtual ~Vector2d() = default;
};

class GameObject : public Vector2d {
public:
    GameObject() : Vector2d() {} 
    GameObject(double x, double y) : Vector2d(x, y) {} 

    // Méthodes virtuelles pures
    virtual void draw() const = 0;   
    virtual void update() = 0;       

    virtual ~GameObject() = default;
};


int main() {
    Vector2d v1(3.0, 4.0);
    Vector2d v2(6.0, 8.0);

    std::cout << "v1: (" << v1.getX() << ", " << v1.getY() << ")\n";
    std::cout << "v2: (" << v2.getX() << ", " << v2.getY() << ")\n";

    Vector2d v3 = v1 + v2;
    Vector2d v4 = v1 - v2;
    std::cout << "v1 + v2: (" << v3.getX() << ", " << v3.getY() << ")\n";
    std::cout << "v1 - v2: (" << v4.getX() << ", " << v4.getY() << ")\n";

    std::cout << "Distance entre v1 et v2: " << v1.distance(v2) << "\n";

    return 0;
}