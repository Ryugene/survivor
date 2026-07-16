#include "Weapons.hpp"
#include "Monsters.hpp"
#include "Player.hpp"
#include "DataStructures.hpp"

AntiGayEnergy::AntiGayEnergy() {
    damage = 10;
    cooldown = 2;
    area = 50; 
    name = "Anti-Gay Energy";
    level = 1;
    clock.restart();
}

void AntiGayEnergy::Fire(SparseMonsterSet& MSet, Player& p) {
    for (auto it = MSet.begin(); it != MSet.end(); ++it) {
        double x = (*it)->x_pos - p.x_pos;
        double y = (*it)->y_pos - p.y_pos;
        if (x*x + y*y <= area*area && ((*it)->clock.getElapsedTime().asSeconds() >= cooldown || (*it)->spawn)) {
            (*it)->hp -= damage;
            (*it)->clock.restart();
            (*it)->spawn = false;
        }
    }
}

sf::CircleShape AntiGayEnergy::Display(Player& p) {
    sf::CircleShape aura(area,250);
    aura.setFillColor(sf::Color::Blue);
    aura.setPosition(p.x_pos - area + p.size, p.y_pos - area + p.size);
    return aura;
}

PowerShout::PowerShout() {
    
}