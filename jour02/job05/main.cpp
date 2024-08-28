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
    std::string nom;
public:
    static std::vector<std::shared_ptr<Pingouin>> colony;
    Pingouin(int v_nage, int v_marche, int v_glisse, std::string nom);
    Pingouin(Pingouin& p);
    ~Pingouin();
    void set_v_nage(int v_nage);
    void set_v_marche(int v_marche);
    void set_v_glisse(int v_glisse);
    std::string get_nom();
    void nage();
    void marche();
    void glisse();
    void presente();
    int record_perso(){
        int temps = 0;
        temps += 15/vitesse_glisse;
        temps += 20/get_v_marche();
        temps += 50/get_v_nage();
        temps += 15/get_v_marche();
        return temps;
    };
    static void trierColonie() {
        std::sort(colony.begin(), colony.end(), 
                [](const std::shared_ptr<Pingouin>& a, const std::shared_ptr<Pingouin>& b) {
                    return a->record_perso() < b->record_perso();
                });
    }
    static void olympic(){
        for (size_t i = 0; i < colony.size(); i++)
        {
            int temps = 0;
            temps += 15/colony[i].get()->vitesse_glisse;
            temps += 20/colony[i].get()->get_v_marche();
            temps += 50/colony[i].get()->get_v_nage();
            temps += 15/colony[i].get()->get_v_marche();

            std::cout << colony[i].get()->get_nom() << " a fait le parcours en " << temps << " secondes" << std::endl;
        }
    };
};

Pingouin::Pingouin(int v_nage, int v_marche, int v_glisse, std::string n) : Aquatique(v_nage), Terrestre(v_marche), vitesse_glisse{v_glisse}, nom{n}
{
    Pingouin::colony.push_back(std::shared_ptr<Pingouin>(this, [](Pingouin*){}));
    trierColonie();
}

Pingouin::Pingouin(Pingouin& p) : Aquatique(p.get_v_nage()), Terrestre(p.get_v_marche()), vitesse_glisse{p.vitesse_glisse}, nom{p.get_nom()}
{
    Pingouin::colony.push_back(std::shared_ptr<Pingouin>(this, [](Pingouin*){}));
    trierColonie();
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

std::string Pingouin::get_nom(){
    return nom;
}

void Pingouin::nage(){
    std::cout << get_nom() << " nage a " << get_v_nage() << "m/s" << std::endl;
}

void Pingouin::marche()
{
    std::cout << get_nom() << " marche a " << get_v_marche() << "m/s" << std::endl;
}

void Pingouin::glisse()
{
    std::cout << get_nom() << " glisse a " << vitesse_glisse << "m/s" << std::endl;
}

void Pingouin::presente(){
    std::cout << "Ce pingouin s'appelle " << get_nom() << std::endl;
}

std::vector<std::shared_ptr<Pingouin>> Pingouin::colony;



int main()
{
    Pingouin pingouin = Pingouin(25, 10, 50, "Pingou1");
    pingouin.presente();
    pingouin.marche();
    pingouin.nage();
    pingouin.glisse();
    Pingouin pingoudeux = Pingouin(35, 5, 45, "Pingou2");
    Pingouin pingoutrois = Pingouin(15, 15, 55, "Pingou3");
    Pingouin pingouquatre = Pingouin(40, 20, 60, "Pingou4");
    std::cout << "La colonie contient " << pingouin.colony.size() << " membres" << std::endl;
    pingouin.olympic();
}