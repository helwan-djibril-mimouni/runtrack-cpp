#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <stdexcept>

class Enemy {
public:
    virtual void attack() const = 0;
    virtual ~Enemy() {}
};

class Goblin : public Enemy {
public:
    void attack() const override {
        std::cout << "Goblin attacks with a dagger!" << std::endl;
    }
};

class Ogre : public Enemy {
public:
    void attack() const override {
        std::cout << "Ogre swings a massive club!" << std::endl;
    }
};

class Dragon : public Enemy {
public:
    void attack() const override {
        std::cout << "Dragon breathes fire!" << std::endl;
    }
};

class EnemyFactory {
public:
    EnemyFactory() {
        enemyMap["goblin"] = []() -> std::unique_ptr<Enemy> { return std::make_unique<Goblin>(); };
        enemyMap["ogre"] = []() -> std::unique_ptr<Enemy> { return std::make_unique<Ogre>(); };
        enemyMap["dragon"] = []() -> std::unique_ptr<Enemy> { return std::make_unique<Dragon>(); };
    }

    std::unique_ptr<Enemy> createEnemy(const std::string& type) const {
        auto it = enemyMap.find(type);
        if (it != enemyMap.end()) {
            return it->second();  
        } else {
            throw std::runtime_error("Enemy type not supported : " + type);
        }
    }

private:
    std::unordered_map<std::string, std::function<std::unique_ptr<Enemy>()>> enemyMap;
};

int main() {
    EnemyFactory factory;

    try {
        std::unique_ptr<Enemy> enemy1 = factory.createEnemy("goblin");
        enemy1->attack();

        std::unique_ptr<Enemy> enemy2 = factory.createEnemy("ogre");
        enemy2->attack();

        std::unique_ptr<Enemy> enemy3 = factory.createEnemy("dragon");
        enemy3->attack();

        std::unique_ptr<Enemy> enemy4 = factory.createEnemy("troll"); 
        enemy4->attack(); 
    } catch (const std::exception& e) {
        std::cerr << "Error : " << e.what() << std::endl;
    }

    return 0;
}