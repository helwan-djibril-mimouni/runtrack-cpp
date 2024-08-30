#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <memory>
#include <algorithm> // Include this for std::remove_if

// Définition de la classe Vector2d
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

// Définition de la classe abstraite GameObject
class GameObject : public Vector2d {
public:
    GameObject() : Vector2d() {}
    GameObject(double x, double y) : Vector2d(x, y) {}

    virtual void draw() const = 0;
    virtual void update() = 0;

    virtual ~GameObject() = default;
};

// Classe Decor
class Decor : public GameObject {
public:
    Decor(double x, double y) : GameObject(x, y) {}

    void draw() const override {
        std::cout << "Drawing Decor at (" << getX() << ", " << getY() << ")\n";
    }

    void update() override {
        // Le décor ne bouge pas, donc cette méthode ne fait rien
    }
};

// Classe Character
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
        std::cout << "Drawing Character '" << name << "' at (" << getX() << ", " << getY() << "), Health: " << healthPoints << "\n";
    }

    void update() override {
        // Pour l'instant, cette méthode ne fait rien.
        // Vous pouvez ajouter de la logique de mise à jour ici si nécessaire.
    }

    void receiveDamage(int damage) {
        healthPoints -= damage;
        if (healthPoints < 0) healthPoints = 0;
    }

    void move(double dx, double dy) {
        setX(getX() + dx);
        setY(getY() + dy);
    }
};

// Interface Weapon
class Weapon {
public:
    virtual void attack(Character& target) const = 0;
    virtual ~Weapon() = default;
};

// Classe Bow
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

// Classe Spear
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

// Classe Sword
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

// Classe Enemy
class Enemy : public Character {
public:
    Character* target; // Le joueur ciblé
    Enemy(const std::string& name, int healthPoints, double x, double y, Character* target)
        : Character(name, healthPoints, x, y), target(target) {}

    void update() override {
        if (isAlive() && target) {
            double step = 0.1; // Pas de déplacement
            double dx = target->getX() - getX();
            double dy = target->getY() - getY();
            double dist = distance(*target);

            if (dist > 1) { // Si l'ennemi n'est pas encore à portée
                double moveX = step * dx / dist;
                double moveY = step * dy / dist;
                setX(getX() + moveX);
                setY(getY() + moveY);
                std::cout << getName() << " moves to (" << getX() << ", " << getY() << ")\n";
            } else { // L'ennemi est à portée pour attaquer
                std::cout << getName() << " is attacking " << target->getName() << "!\n";
                target->receiveDamage(2); // Exemple de dégâts infligés par l'ennemi
            }
        }
    }
};

// Classe Player
class Player : public Character {
private:
    Weapon* weapon; // Arme actuelle (pointeur brut)
    std::vector<std::unique_ptr<Weapon>> weaponCycle; // Cycle d'armes
    size_t weaponIndex = 0; // Index de l'arme actuelle
    
public:
    Enemy* enemy; // Référence à l'ennemi cible
    Player(const std::string& name, int healthPoints, double x, double y, Enemy* enemy)
        : Character(name, healthPoints, x, y), enemy(enemy) {
        // Initialise le cycle d'armes
        weaponCycle.push_back(std::make_unique<Bow>());
        weaponCycle.push_back(std::make_unique<Spear>());
        weaponCycle.push_back(std::make_unique<Sword>());
        weapon = weaponCycle[0].get(); // Utilisation du pointeur brut de la première arme
    }

    void switchWeapon() {
        weaponIndex = (weaponIndex + 1) % weaponCycle.size();
        weapon = weaponCycle[weaponIndex].get(); // Référence à la nouvelle arme
        std::cout << getName() << " switches to ";
        if (dynamic_cast<Bow*>(weapon)) std::cout << "Bow\n";
        else if (dynamic_cast<Spear*>(weapon)) std::cout << "Spear\n";
        else if (dynamic_cast<Sword*>(weapon)) std::cout << "Sword\n";
    }

    void move(double dx, double dy) {
        setX(getX() + dx);
        setY(getY() + dy);
    }

    void update() override {
        if (isAlive() && enemy) {
            std::cout << getName() << " attacks with ";
            if (dynamic_cast<Bow*>(weapon)) std::cout << "Bow\n";
            else if (dynamic_cast<Spear*>(weapon)) std::cout << "Spear\n";
            else if (dynamic_cast<Sword*>(weapon)) std::cout << "Sword\n";
            weapon->attack(*enemy); // Attaque l'ennemi

            // Changement d'arme pour le prochain tour
            switchWeapon();
        }
    }

    void handleInput(char action) {
        switch (action) {
            case 'm': {
                double dx, dy;
                std::cout << "Enter move coordinates (dx dy): ";
                std::cin >> dx >> dy;
                move(dx, dy);
                break;
            }
            case 'a': {
                if (enemy) {
                    std::cout << getName() << " attacks with ";
                    if (dynamic_cast<Bow*>(weapon)) std::cout << "Bow\n";
                    else if (dynamic_cast<Spear*>(weapon)) std::cout << "Spear\n";
                    else if (dynamic_cast<Sword*>(weapon)) std::cout << "Sword\n";
                    weapon->attack(*enemy);
                }
                break;
            }
            case 'w': {
                switchWeapon();
                break;
            }
            default:
                std::cout << "Invalid command\n";
                break;
        }
    }
};

// Classe GameWorld
class GameWorld {
private:
    std::vector<std::unique_ptr<GameObject>> objects;

public:
    void addObject(std::unique_ptr<GameObject> object) {
        objects.push_back(std::move(object));
    }

    void update() {
        for (auto& obj : objects) {
            obj->update();
        }
    }

    void draw() const {
        for (const auto& obj : objects) {
            obj->draw();
        }
    }

    // Méthodes pour accéder aux objets
    Player* getPlayer() {
        for (const auto& obj : objects) {
            if (auto player = dynamic_cast<Player*>(obj.get())) {
                return player;
            }
        }
        return nullptr;
    }

    Enemy* getEnemy() {
        for (const auto& obj : objects) {
            if (auto enemy = dynamic_cast<Enemy*>(obj.get())) {
                return enemy;
            }
        }
        return nullptr;
    }

    void removeDeadObjects() {
        objects.erase(std::remove_if(objects.begin(), objects.end(),
            [](const std::unique_ptr<GameObject>& obj) { 
                if (auto character = dynamic_cast<Character*>(obj.get())) {
                    return !character->isAlive();
                }
                return false; 
            }), objects.end());
    }
};

int main() {
    // Création de la GameWorld
    GameWorld world;

    // Création des objets
    auto enemy = std::make_unique<Enemy>("Enemy", 10, 5.0, 5.0, nullptr);
    auto player = std::make_unique<Player>("Player", 10, 0.0, 0.0, nullptr);

    // Réinitialiser les références après avoir ajouté les objets au monde
    enemy->target = player.get(); // Référence à l'objet Player dans l'Enemy
    player->enemy = enemy.get();  // Référence à l'objet Enemy dans le Player

    // Ajouter les objets au monde
    world.addObject(std::move(player));
    world.addObject(std::move(enemy));

    // Simulation du jeu
    int turn = 0;
    while (true) {
        std::cout << "\nTurn " << ++turn << ":\n";
        world.update();
        world.draw();

        // Accès aux personnages
        Character* characterPtr = world.getPlayer(); // Utiliser Character* pour éviter le conflit
        Enemy* enemyPtr = world.getEnemy();

        if (characterPtr && enemyPtr) {
            std::cout << characterPtr->getName() << " has " << characterPtr->getHealthPoints() << " HP remaining.\n";
            std::cout << enemyPtr->getName() << " has " << enemyPtr->getHealthPoints() << " HP remaining.\n";

            if (!characterPtr->isAlive()) {
                std::cout << characterPtr->getName() << " is dead. Game Over.\n";
                break;
            }

            if (!enemyPtr->isAlive()) {
                std::cout << enemyPtr->getName() << " is dead. You win!\n";
                break;
            }
        } else {
            std::cerr << "Error: Player or Enemy not found in the world.\n";
            break;
        }

        // Nettoyer les objets morts
        world.removeDeadObjects();

        // Entrée utilisateur
        Player* playerPtr = world.getPlayer();
        if (playerPtr) {
            char action;
            std::cout << "Enter action (m: move, a: attack, w: switch weapon): ";
            std::cin >> action;
            playerPtr->handleInput(action);
        }
    }

    return 0;
}
