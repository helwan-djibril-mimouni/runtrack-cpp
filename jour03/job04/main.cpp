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

    void update() override {}
    
    void receiveDamage(int damage) {
            healthPoints -= damage;
            if (healthPoints < 0) healthPoints = 0;
        }
};

class Weapon {
public:
    virtual void attack(Character& target) const = 0; 
    virtual ~Weapon() = default; 
};

class Bow : public Weapon {
private:
    const int range = 4;
    const int power = 1;

public:
    void attack(Character& target) const override {
        std::cout << "Attacking " << target.getName() << " with a Bow, causing " << power << " damage.\n";
        target.receiveDamage(power);
    }
};

class Spear : public Weapon {
private:
    const int range = 2;
    const int power = 2;

public:
    void attack(Character& target) const override {
        std::cout << "Attacking " << target.getName() << " with a Spear, causing " << power << " damage.\n";
        target.receiveDamage(power);
    }
};

class Sword : public Weapon {
private:
    const int range = 1;
    const int power = 4;

public:
    void attack(Character& target) const override {
        std::cout << "Attacking " << target.getName() << " with a Sword, causing " << power << " damage.\n";
        target.receiveDamage(power);
    }
};

int main() {
    Character hero("Hero", 10, 0.0 , 0.0);

    Bow bow;
    Spear spear;
    Sword sword;

    bow.attack(hero);
    std::cout << hero.getName() << " has " << hero.getHealthPoints() << " HP remaining.\n";

    spear.attack(hero);
    std::cout << hero.getName() << " has " << hero.getHealthPoints() << " HP remaining.\n";

    sword.attack(hero);
    std::cout << hero.getName() << " has " << hero.getHealthPoints() << " HP remaining.\n";

    return 0;
}