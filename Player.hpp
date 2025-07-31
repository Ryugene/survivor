#include <vector>
#ifndef __Weapons_hpp__
#define __Weapons_hpp__


using namespace std;

class Weapon;
class AntiGayEnergy;

class Player {
public:
    Player(float x_cord, float y_cord, float p_size, Weapon* starting_weapon) {
        x_pos = x_cord;
        y_pos = y_cord;
        size = p_size;
        pick_up_range = 2*p_size;
        weapons.push_back(starting_weapon);
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
};

#endif