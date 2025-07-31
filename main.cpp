#include <SFML/Graphics.hpp>
#include <memory>
#include "Player.hpp"
#include "Monsters.hpp"
#include "Weapons.hpp"
#include <iostream>

using namespace std;

int max_monsters = 100;

bool CanSpawn(vector<Monster>& vm, float x, float y) {
    for (auto& m : vm) {
        if (abs(m.x_pos-x)*abs(m.x_pos-x) + abs(m.y_pos-y)*abs(m.y_pos-y) <= m.size*m.size)
            return false;
    }
    return true;
}

int SetID(vector<Monster>& vm) {
    int curr = 0;
    for (int i = 0; i < vm.size(); ++i) {
        curr = max(vm[i].id, curr);
    }
    return curr+1;
}


int main()
{
    auto w_width = sf::VideoMode::getDesktopMode().width;
    auto w_height = sf::VideoMode::getDesktopMode().height;
    float p_size = (w_width + w_height) / 200;
    AntiGayEnergy* s_w;
    


    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "LGBT survivor",sf::Style::Fullscreen);
    sf::RectangleShape arena(sf::Vector2f(3*w_width ,3*w_height));

    Player player(arena.getSize().x/2 + p_size, arena.getSize().y/2 + p_size, p_size, s_w);
    sf::View view(sf::FloatRect(0,0, w_width,w_height));
    sf::CircleShape player_shape(p_size,500);
    sf::RectangleShape hp_bar1(sf::Vector2f(player.hp / player.max_hp * 2*p_size, p_size/3));
    sf::RectangleShape hp_bar2(sf::Vector2f((1.f - player.hp/player.max_hp) * 2*p_size, p_size/3));
    arena.setFillColor(sf::Color::White);
    player_shape.setFillColor(sf::Color::Yellow);
    hp_bar1.setFillColor(sf::Color::Red);
    hp_bar2.setFillColor(sf::Color::Black);
    
    vector<Monster> monsters;
    sf::Clock clock;
    
    int curr_pnt = 0;
    while (window.isOpen()) {
        view.setCenter(player.x_pos, player.y_pos);
        window.setView(view);
        window.clear();
        sf::Time time = clock.getElapsedTime();
        float t = time.asSeconds();
        if (t >= 0.01 && monsters.size() < max_monsters) {
            Monster m(int(arena.getPosition().x) + 1, int(arena.getSize().x + arena.getPosition().x) - 2*p_size, int(arena.getPosition().y) + 1, int(arena.getSize().y + arena.getPosition().y) - 2*p_size,
            5.f, 5.f, 2, 1.f, SetID(monsters));
            while (abs (m.x_pos - player.x_pos) <= w_width || abs(m.y_pos - player.y_pos) <= w_height) {
                pair<int,int> cord_p = SpawnMonster(int(arena.getPosition().x) + 1, int(arena.getSize().x + arena.getPosition().x) - 2*p_size, int(arena.getPosition().y) + 1, int(arena.getSize().y + arena.getPosition().y) - 2*p_size);
                while(!CanSpawn)
                    cord_p = SpawnMonster(int(arena.getPosition().x) + 1, int(arena.getSize().x + arena.getPosition().x) - 2*p_size, int(arena.getPosition().y) + 1, int(arena.getSize().y + arena.getPosition().y) - 2*p_size);
                m.x_pos = cord_p.first;
                m.y_pos = cord_p.second;
            }
            sf::CircleShape m_shape(p_size,52);
            m_shape.setFillColor(sf::Color::Red);
            m_shape.setPosition(m.x_pos,m.y_pos);
            m.shape = m_shape;
            m.size = m_shape.getRadius();
            monsters.push_back(m);
            clock.restart();
        }
    

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.x_pos >= arena.getPosition().x + player.speed) {
            player.x_pos -= player.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.x_pos <= arena.getPosition().x + arena.getSize().x - 2*player.size - player.speed) {
            player.x_pos += player.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.y_pos >= arena.getPosition().y + player.speed) {
            player.y_pos -= player.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.y_pos <= arena.getPosition().y + arena.getSize().y - 2*player.size - player.speed) {
            player.y_pos += player.speed;
        }

        player_shape.setPosition(player.x_pos, player.y_pos);
        hp_bar1.setPosition(player.x_pos, player.y_pos + 13*player.size/5);
        hp_bar2.setPosition(hp_bar1.getPosition().x + hp_bar1.getSize().x, hp_bar1.getPosition().y);
        
        
        window.draw(arena);
        for (auto weapon : player.weapons) {
            AntiGayEnergy g;
            weapon = &g;
            weapon->Fire(monsters, player);
            window.draw(weapon->Display(player));
        }
        window.draw(player_shape);
        window.draw(hp_bar1);
        window.draw(hp_bar2);
        for (auto m = monsters.begin(); m != monsters.end(); ++m) {
            if (m->hp <= 0) {
                monsters.erase(m);
            }
            else
                window.draw(m->shape);
            window.draw(m->Move(player, monsters));
        }
        window.display();
    }
    return 0;
}