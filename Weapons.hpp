#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Player;
class Monster;

class Weapon {
public:
    Weapon();
    double damage = 0;
    //in seconds
    double cooldown = 0;
    //in seconds
    double duration = 0;
    int projectiles = 0;
    //circle radius
    double area = 0;
    double speed = 0;
    string name = "";
    int level = 0;
    sf::Clock clock;
    virtual void Fire(SparseMonsterSet& MSet, Player& p) = 0;
    virtual sf::CircleShape Display(Player& p) = 0;
    //virtual void Upgrade(Player& p) = 0;

    virtual ~Weapon() = default;
};

class AntiGayEnergy : public Weapon {
public:
    AntiGayEnergy();
    void Fire(SparseMonsterSet& MSet, Player& p) override;
    sf::CircleShape Display(Player& p) override;
};

class PowerShout : public Weapon {
public:
    PowerShout();
    void Fire(SparseMonsterSet& MSet, Player& p) override;
};

class TruthBomb : public Weapon {

};