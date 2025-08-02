#include <utility>
#include <random>
#include <math.h>
#include <iostream>
#include <ctime>

using namespace std;

pair<int,int> SpawnMonster(int w1, int w2, int h1, int h2) {
    random_device w;
    default_random_engine gen_w(w());
    uniform_int_distribution<int32_t> widths(w1, w2);
    random_device h;
    default_random_engine gen_h(h());
    uniform_int_distribution<int32_t> heights(h1,h2);
    return make_pair(widths(gen_w), heights(gen_h));
}

pair<float,float> Generate_Direction(float x1, float x2, float y1, float y2) {
    random_device x;
    mt19937 gen_x(x());
    uniform_real_distribution<> dis_x(x1, x2);
    random_device y;
    mt19937 gen_y(y());
    uniform_real_distribution<> dis_y(y1, y2);
    return make_pair(dis_x(gen_x), dis_y(gen_y));
}

class Monster {
public:
    Monster(int w1, int w2, int h1, int h2, float m_xp, float m_hp, float m_speed, float m_damage, int m_id) {
        pair<int, int> p = SpawnMonster(w1, w2, h1, h2);
        x_pos = float(p.first);
        y_pos = float(p.second);
        xp = m_xp;
        hp = m_hp;
        speed = m_speed;
        damage = m_damage;
        id = m_id;
    }
    float x_pos;
    float y_pos;
    float xp;
    float hp;
    float speed;
    float damage;
    float size; // radius
    sf::Clock clock;
    sf::CircleShape shape;
    bool spawn = true;
    int id;
    int random_dir = 1;
    int dir_trigger = 3;
    bool repeat_dir = false;

    void Deal_Damage(Player& p) {
        float dx = abs(p.x_pos - x_pos);
        float dy = abs(p.y_pos - y_pos);
        float t = p.immortality_clock.getElapsedTime().asSeconds();
        if (dx <= p.size && dy <= p.size && p.hp > 0 && t >= 0.5) {
            p.hp -= damage;
            p.immortality_clock.restart();
        }
    }

    void Move(Player& p, vector<Monster>& vm) {
        double x = abs(p.x_pos - x_pos);
        double y = abs(p.y_pos - y_pos);
        if (x == 0)
            x += 0.0000001;
        if (y == 0)
            y += 0.0000001;
        double alpha = atan(y/x);
        double beta = atan(x/y);
        double dx = speed*sin(beta);
        double dy = speed*sin(alpha);
        if (random_dir == dir_trigger) {
            random_dir = 1;
            if (repeat_dir) {
                random_dir = dir_trigger - 1;
                repeat_dir = false;
            }
            else {
                repeat_dir = true;
            }
            pair<float,float> directions = Generate_Direction(-speed, speed, -speed, speed);
            x_pos += directions.first;
            y_pos += directions.second;
        }
        else if (p.x_pos <= x_pos && p.y_pos >= y_pos) { // player is bottom left
            x_pos -= dx;
            y_pos += dy;    
        }
        else if (p.x_pos <= x_pos && p.y_pos <= y_pos) { // player is top left
            x_pos -= dx;
            y_pos -= dy; 
        }
        else if (p.x_pos >= x_pos && p.y_pos <= y_pos) { // player is top right
            x_pos += dx;
            y_pos -= dy; 
        }
        else { // player is bottom right
            x_pos += dx;
            y_pos += dy; 
        }
        shape.setPosition(x_pos, y_pos);
        random_dir++;
    }
};

