//#include <string>
#ifndef __Monsters_hpp__
#define __Monsters_hpp__
#ifndef __Player_hpp__
#define __Player_hpp__


using namespace std;

class Player;
class Monster;

class Weapon {
public:
    Weapon() {}
    float damage;
    float cooldown;
    float duration;
    int projectiles;
    float area;
    float speed;
    int amount;
    string name;
    int level;
    sf::Clock clock;
    virtual void Fire(vector<Monster>& vm, Player& p) {}
    virtual sf::CircleShape Display(Player& p) {}
};

class AntiGayEnergy : public Weapon {
public:
    AntiGayEnergy() {
        damage = 10;
        cooldown = 2;
        area = 50; // circle radius
        name = "Anti-Gay Energy";
        level = 1;
        clock.restart();
    }
    void Fire(vector<Monster>& vm, Player& p) override {
        for (int i = 0; i < vm.size(); ++i) {
            float x = vm[i].x_pos - p.x_pos;
            float y = vm[i].y_pos - p.y_pos;
            if (x*x + y*y <= area*area && (vm[i].clock.getElapsedTime().asSeconds() >= cooldown || vm[i].spawn)) {
                vm[i].hp -= damage;
                vm[i].clock.restart();
                vm[i].spawn = false;
            }
        }
    }
    sf::CircleShape Display(Player& p) override {
        sf::CircleShape sh(area,500);
        sh.setFillColor(sf::Color::Blue);
        sh.setPosition(p.x_pos - area + p.size, p.y_pos - area + p.size);
        return sh;
    }
};

#endif
#endif