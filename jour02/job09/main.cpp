#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <unordered_map>

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
    std::map<std::string, int> competences;
    std::set<std::weak_ptr<Pingouin>, std::owner_less<std::weak_ptr<Pingouin>>> amis;
    std::unordered_map<std::string, std::string> journal;
public:
    static std::vector<std::shared_ptr<Pingouin>> colony;
    static std::list<std::string> lieux;
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
    void ajouterLieu(std::string lieu);
    void supprimerLieu(std::string lieu);
    void afficherLieux();
    void modifierCompetence(const std::string& nom, int niveau);
    void supprimerCompetence(const std::string& nom);
    void afficherCompetences();
    void ajouterAmi(const std::shared_ptr<Pingouin>& ami);
    void retirerAmi(const std::shared_ptr<Pingouin>& ami);
    void afficherAmis();
    void ajouterJournal(std::string date, std::string description);
    void supprimerJournal(std::string date);
    void afficherJournal();
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

void Pingouin::ajouterLieu(std::string lieu) {
    lieux.push_back(lieu);
}

void Pingouin::supprimerLieu(std::string lieu) {
    lieux.remove(lieu);
}

void Pingouin::afficherLieux() {
    std::cout << "Lieux de rencontre des pingouins :" << std::endl;
    for (const auto& lieu : lieux) {
        std::cout << "- " << lieu << std::endl;
    }
}

void Pingouin::modifierCompetence(const std::string& comp, int niveau) {
    competences[comp] = niveau;
}

void Pingouin::supprimerCompetence(const std::string& comp) {
    competences.erase(comp);
}

void Pingouin::afficherCompetences() {
    std::cout << "Competences de " << get_nom() << " :" << std::endl;
    for (const auto& paire : competences) {
        std::cout << paire.first << " : Niveau " << paire.second << std::endl;
    }
}

void Pingouin::ajouterAmi(const std::shared_ptr<Pingouin>& ami) {
    amis.insert(ami);
}

void Pingouin::retirerAmi(const std::shared_ptr<Pingouin>& ami) {
    auto it = std::find_if(amis.begin(), amis.end(),
                        [&ami](const std::weak_ptr<Pingouin>& wptr) {
                            if (auto sptr = wptr.lock()) {
                                return sptr == ami;
                            }
                            return false;
                        });
    if (it != amis.end()) {
        amis.erase(it);
    }
}

void Pingouin::afficherAmis() {
    std::cout << "Amis de " << get_nom() << " : " << std::endl;
    for (const auto& wptr : amis) {
        if (auto sptr = wptr.lock()) {
            std::cout << "- " << sptr.get()->get_nom() << std::endl;
        }
    }
}

void Pingouin::ajouterJournal(std::string date, std::string description) {
    journal[date] = description;
}

void Pingouin::supprimerJournal(std::string date) {
    journal.erase(date);
}

void Pingouin::afficherJournal() {
    std::cout << "Journal de " << get_nom() << " :" << std::endl;
    for (const auto& entree : journal) {
        std::cout << "Date: " << entree.first << " -> Description: " << entree.second << std::endl;
    }
}

std::vector<std::shared_ptr<Pingouin>> Pingouin::colony;
std::list<std::string> Pingouin::lieux;



int main()
{
    auto pingouin = std::make_shared<Pingouin>(25, 10, 50, "Pingou1");
    pingouin->presente();
    pingouin->marche();
    pingouin->nage();
    pingouin->glisse();
    auto pingoudeux = std::make_shared<Pingouin>(35, 5, 45, "Pingou2");
    auto pingoutrois = std::make_shared<Pingouin>(15, 15, 55, "Pingou3");
    auto pingouquatre = std::make_shared<Pingouin>(40, 20, 60, "Pingou4");
    std::cout << "La colonie contient " << pingouin->colony.size() << " membres" << std::endl;
    pingouin->olympic();
    pingouin->ajouterLieu("glacier");
    pingouin->afficherLieux();
    pingouin->ajouterLieu("mer");
    pingouin->afficherLieux();
    pingouin->modifierCompetence("Laser Glace", 90);
    pingouin->modifierCompetence("Hydrocanon", 110);
    pingoudeux->modifierCompetence("Laser Glace", 80);
    pingouin->afficherCompetences();
    pingoudeux->afficherCompetences();
    pingouin->ajouterAmi(pingoudeux);
    pingouin->ajouterAmi(pingoutrois);
    pingoudeux->ajouterAmi(pingouin);
    pingoutrois->ajouterAmi(pingouin);
    pingouin->afficherAmis();
    pingoudeux->afficherAmis();
    pingoutrois->afficherAmis();
    pingouquatre->afficherAmis();
    pingouin->ajouterJournal("27/08/2024", "manger");
    pingouin->ajouterJournal("28/08/2024", "glisser");
    pingoudeux->ajouterJournal("27/08/2024", "dormir");
    pingoutrois->ajouterJournal("27/08/2024", "nager");
    pingouin->afficherJournal();
    pingoudeux->afficherJournal();
    pingoutrois->afficherJournal();
    pingouquatre->afficherJournal();
}