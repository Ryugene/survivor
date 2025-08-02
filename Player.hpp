#ifndef __Weapons_hpp__
#define __Weapons_hpp__
#include <vector>

using namespace std;

class Weapon;
//class AntiGayEnergy;

class Player {
public:
    Player(float x_cord, float y_cord, float p_size, Weapon* starting_weapon){
        x_pos = x_cord;
        y_pos = y_cord;
        size = p_size;
        pick_up_range = 2*p_size;
        weapons.push_back(starting_weapon);
        immortality_clock.restart();
    }
    float x_pos;
    float y_pos;
    float size;
    float max_hp = 100;
    float hp = max_hp;
    float speed = 0.5;
    float xp = 0;
    int level = 1;
    float pick_up_range;
    vector<Weapon*> weapons;
    sf::CircleShape shape;
    sf::Clock immortality_clock;

    void Update_HP(sf::RectangleShape& curr_hp, sf::RectangleShape& missing_hp) {
        curr_hp.setSize(sf::Vector2f(hp / max_hp*2*size, size/3));
        missing_hp.setSize(sf::Vector2f((1.f - hp/max_hp)*2*size, size/3));
        curr_hp.setPosition(x_pos, y_pos + 13*size/5);
        missing_hp.setPosition(curr_hp.getPosition().x + curr_hp.getSize().x, curr_hp.getPosition().y); 
    }

    void Reset(float start_x, float start_y) {
        hp = max_hp;
        speed = 0.5;
        xp = 0;
        level = 1;
        pick_up_range = 2*size;
        immortality_clock.restart();
        x_pos = start_x;
        y_pos = start_y;
        shape.setPosition(x_pos,y_pos);
    }
};

#endif