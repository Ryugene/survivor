#pragma once
#include <utility>
#include <random>
#include <math.h>
#include <iostream>
#include <ctime>
#include <map>
#include <set>
#include <numeric>
#include "DataStructures.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

class Player;

inline constexpr int max_monsters = 50;
set<int> available_monster_ids;

void Create_Available_MonsterIDs(set<int>& available_monster_ids);
int Assign_MonsterID(set<int>& available_monster_ids);

class Monster {
public:
    // arena parameters and monster parameters w1 is start position w2 is end position same logic for h1, h2
    // calls SpawnMonster to assign cordinates
    Monster(vector<pair<int,int>>& grid_keys, map<pair<int,int>, bool>& free, Player& p,
            double m_xp, double m_hp, double m_speed, double m_damage);

    double x_pos;
    double y_pos;
    double xp;
    double hp;
    double speed;
    double damage;
    double size; // radius
    sf::Clock clock;
    sf::CircleShape shape;
    bool spawn = true;
    int id = SparseMonsterSet::invalidIndex;

    bool CanSpawn(Player& p);
    bool SpawnMonster(vector<pair<int,int>>& grid_keys, map<pair<int,int>, bool>& free, Player& p);
    void Deal_Damage(Player& p);
    void ChooseDestination(Player& p);
    virtual void Move(double dx, double dy);
};

class Type1 : public Monster {
public:
    using Monster::Monster;
};