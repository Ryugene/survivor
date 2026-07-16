#include "Player.hpp"
#include "Weapons.hpp"

Player::Player(double x_cord, double y_cord, double p_size, unique_ptr<Weapon> starting_weapon) {
    x_pos = x_cord;
    y_pos = y_cord;
    size = p_size;
    pick_up_range = 2*p_size;
    weapons.push_back(std::move(starting_weapon));
    immortality_clock.restart();
}

void Player::Update_HP(sf::RectangleShape& curr_hp, sf::RectangleShape& missing_hp) {
    curr_hp.setSize(sf::Vector2f(hp / max_hp*2*size, size/3));
    missing_hp.setSize(sf::Vector2f((1.f - hp/max_hp)*2*size, size/3));
    curr_hp.setPosition(x_pos, y_pos + 13*size/5);
    missing_hp.setPosition(curr_hp.getPosition().x + curr_hp.getSize().x, curr_hp.getPosition().y); 
}

void Player::Reset(double start_x, double start_y) {
    hp = max_hp;
    speed = 0.5;
    xp = 0;
    level = 1;
    pick_up_range = 2*size;
    immortality_clock.restart();
    x_pos = start_x;
    y_pos = start_y;
    shape.setPosition(x_pos,y_pos);
    dead = false;
}