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



class Decor : public GameObject {
public:
    Decor(double x, double y) : GameObject(x, y) {}

    void draw() const override {
        std::cout << "Drawing Decor at (" << x << ", " << y << ")\n";
    }

    void update() override {
        std::cout << "Decor remains static at (" << x << ", " << y << ")\n";
    }
};

class Character : public GameObject {
private:
    std::string name;    
    int healthPoints;  

public:
    Character(const std::string& name, int healthPoints, double x, double y)
        : GameObject(x, y), name(name), healthPoints(healthPoints) {}

    std::string getName() const { return name; }

    int getHealthPoints() const { return healthPoints; }

    void setHealthPoints(int hp) { healthPoints = hp; }

    bool isAlive() const { return healthPoints > 0; }

    void draw() const override {
        std::cout << "Drawing Character '" << name << "' at (" << x << ", " << y << "), Health: " << healthPoints << "\n";
    }

    void update() override {
        std::cout << "Updating Character '" << name << "'.\n";
        if (healthPoints > 0) {
            healthPoints -= 1; 
        }
    }
};

int main() {
    Decor decor(10.0, 20.0);
    decor.draw();
    decor.update();

    Character character("Hero", 10, 0.0, 0.0);
    character.draw();
    character.update();
    character.draw();

    if (character.isAlive()) {
        std::cout << character.getName() << " is still alive with " << character.getHealthPoints() << " HP.\n";
    } else {
        std::cout << character.getName() << " is dead.\n";
    }

    return 0;
}