#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;

class Weapon;

class Player {
public:
    Player(double x_cord, double y_cord, double p_size, unique_ptr<Weapon> starting_weapon);
    bool dead;
    double x_pos;
    double y_pos;
    double size;
    double max_hp = 100;
    double hp = max_hp;
    double speed = 0.5;
    double xp = 0;
    int level = 1;
    double pick_up_range;
    vector<unique_ptr<Weapon>> weapons;
    sf::CircleShape shape;
    sf::Clock immortality_clock;

    void Update_HP(sf::RectangleShape& curr_hp, sf::RectangleShape& missing_hp);
    void Reset(double start_x, double start_y);
};