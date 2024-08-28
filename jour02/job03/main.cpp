#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Aquatique
{
private:
    int vitesse_nage;
public:
    Aquatique();
    Aquatique(int v);
    ~Aquatique();
    int get_v_nage();
    void set_v_nage(int v_nage);
    virtual void nage();
};

Aquatique::Aquatique()
{
    vitesse_nage = 0;
}

Aquatique::Aquatique(int v) : vitesse_nage{v}
{
}

Aquatique::~Aquatique()
{
}

int Aquatique::get_v_nage()
{
    return vitesse_nage;
}

void Aquatique::set_v_nage(int v_nage)
{
    vitesse_nage = v_nage;
}

void Aquatique::nage()
{
}



class Terrestre
{
private:
    int vitesse_marche;
public:
    Terrestre();
    Terrestre(int vitesse);
    ~Terrestre();
    int get_v_marche();
    void set_v_marche(int v_marche);
    virtual void marche();
};

Terrestre::Terrestre()
{
    vitesse_marche = 0;
}

Terrestre::Terrestre(int v) : vitesse_marche{v}
{
}

Terrestre::~Terrestre()
{
}

int Terrestre::get_v_marche()
{
    return vitesse_marche;
}

void Terrestre::set_v_marche(int v_marche)
{
    vitesse_marche = v_marche;
}

void Terrestre::marche()
{
}



class Pingouin : Aquatique, Terrestre
{
private:
    int vitesse_glisse;
public:
    static std::vector<std::shared_ptr<Pingouin>> colony;
    Pingouin(int v_nage, int v_marche, int v_glisse);
    Pingouin(Pingouin& p);
    ~Pingouin();
    void set_v_nage(int v_nage);
    void set_v_marche(int v_marche);
    void set_v_glisse(int v_glisse);
    void nage();
    void marche();
    void glisse();
    void presente();
};

Pingouin::Pingouin(int v_nage, int v_marche, int v_glisse) : Aquatique(v_nage), Terrestre(v_marche), vitesse_glisse{v_glisse}
{
    Pingouin::colony.push_back(std::shared_ptr<Pingouin>(this, [](Pingouin*){}));
}

Pingouin::Pingouin(Pingouin& p) : Aquatique(p.get_v_nage()), Terrestre(p.get_v_marche()), vitesse_glisse{p.vitesse_glisse}
{
    Pingouin::colony.push_back(std::shared_ptr<Pingouin>(this, [](Pingouin*){}));
}

Pingouin::~Pingouin()
{
    auto it = std::find_if(colony.begin(), colony.end(), 
                            [this](const std::shared_ptr<Pingouin>& p) { return p.get() == this; });
        if (it != colony.end()) {
            colony.erase(it);
        }
}

void Pingouin::set_v_nage(int v_nage)
{
    Aquatique::set_v_nage(v_nage);
}

void Pingouin::set_v_marche(int v_marche)
{
    Terrestre::set_v_marche(v_marche);
}

void Pingouin::set_v_glisse(int v_glisse)
{
    vitesse_glisse = v_glisse;
}

void Pingouin::nage(){
    std::cout << "Le pingouin nage a " << get_v_nage() << "m/s" << std::endl;
}

void Pingouin::marche()
{
    std::cout << "Le pingouin marche a " << get_v_marche() << "m/s" << std::endl;
}

void Pingouin::glisse()
{
    std::cout << "Le pingouin glisse a " << vitesse_glisse << "m/s" << std::endl;
}

void Pingouin::presente(){
    std::cout << "C'est un pingouin" << std::endl;
}

std::vector<std::shared_ptr<Pingouin>> Pingouin::colony;



int main()
{
    Pingouin pingouin = Pingouin(25, 10, 50);
    pingouin.presente();
    pingouin.marche();
    pingouin.nage();
    pingouin.glisse();
    Pingouin pingoudeux = Pingouin(35, 5, 45);
    Pingouin pingoutrois = Pingouin(15, 15, 55);
    Pingouin pingouquatre = Pingouin(40, 20, 60);
    std::cout << "La colonie contient " << pingouin.colony.size() << " membres" << std::endl;
}