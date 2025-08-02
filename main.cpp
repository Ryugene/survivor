#include <SFML/Graphics.hpp>
#include <memory>
#include "Player.hpp"
#include "Monsters.hpp"
#include "Weapons.hpp"
#include <iostream>
#include "menu.hpp"

using namespace std;

int max_monsters = 100;

bool CanSpawn(vector<Monster>& vm, float x, float y) {
    for (auto& m : vm) {
        if (abs(m.x_pos-x)*abs(m.x_pos-x) + abs(m.y_pos-y)*abs(m.y_pos-y) <= m.size*m.size)
            return false;
    }
    return true;
}

int SetID(vector<Monster*>& vm) {
    int curr = 0;
    for (int i = 0; i < vm.size(); ++i) {
        curr = max(vm[i]->id, curr);
    }
    return curr+1;
}

void Clear_Arena(vector<Monster*>& vm, Player& p, sf::RectangleShape& arena) {
    for (auto& m : vm) {
        delete m;
    }
    vm.clear();
    for (auto& w : p.weapons) {
        delete w;
    }
    p.weapons.clear();
    AntiGayEnergy* s_w = new AntiGayEnergy();
    p.weapons.push_back(s_w);
    p.Reset(arena.getSize().x/2 + p.size, arena.getSize().y/2 + p.size);
}

int main()
{
    auto w_width = sf::VideoMode::getDesktopMode().width;
    auto w_height = sf::VideoMode::getDesktopMode().height;
    float p_size = (w_width + w_height) / 200;
    AntiGayEnergy* s_w = new AntiGayEnergy();

    sf::RenderWindow window(sf::VideoMode(w_width, w_height), "LGBT survivor",sf::Style::Fullscreen);
    sf::RectangleShape arena(sf::Vector2f(3*w_width ,3*w_height));

    Player player(arena.getSize().x/2 + p_size, arena.getSize().y/2 + p_size, p_size, s_w);
    sf::View view(sf::FloatRect(0,0, w_width,w_height));
    sf::CircleShape player_shape(p_size,500);
    sf::RectangleShape curr_hp(sf::Vector2f(player.hp / player.max_hp*2*p_size, p_size/3));
    sf::RectangleShape missing_hp(sf::Vector2f((1.f - player.hp/player.max_hp)*2*p_size, p_size/3));
    arena.setFillColor(sf::Color::White);
    player_shape.setFillColor(sf::Color::Yellow);
    player.shape = player_shape;
    curr_hp.setFillColor(sf::Color::Red);
    missing_hp.setFillColor(sf::Color::Black);
    
    vector<Monster*> monsters;
    sf::Clock spawn_clock;

    // DEATH TEXT //
    sf::Font font;
    font.loadFromFile("youmurdererbb_reg.ttf");
    sf::Text death_text;
    death_text.setString("YOU DIED");
    death_text.setFont(font);
    death_text.setCharacterSize(150);
    death_text.setFillColor(sf::Color::Magenta);
    // DEATH TEXT //

    bool menu_opened = true;
    bool died = false;

    while (window.isOpen()) {
        // MENU //
        if (menu_opened) {
            window.clear();
            if (died) {
                sf::FloatRect bounds = death_text.getLocalBounds();
                death_text.setPosition(w_width/2 - bounds.width/2, 0);
                window.draw(death_text);
            }
            Display_Menu(died, menu_opened, window);
            continue;
        }
        // MENU //
        view.setCenter(player.x_pos, player.y_pos);
        window.setView(view);
        window.clear();
        sf::Time time = spawn_clock.getElapsedTime();
        float t = time.asSeconds();
        if (t >= 0.01 && monsters.size() < max_monsters) {
            Monster* m = new Monster(int(arena.getPosition().x) + 1, int(arena.getSize().x + arena.getPosition().x) - 2*p_size, int(arena.getPosition().y) + 1, int(arena.getSize().y + arena.getPosition().y) - 2*p_size,
            5.f, 5.f, 2, 50, SetID(monsters));
            while (abs (m->x_pos - player.x_pos) <= w_width || abs(m->y_pos - player.y_pos) <= w_height) {
                pair<int,int> cord_p = SpawnMonster(int(arena.getPosition().x) + 1, int(arena.getSize().x + arena.getPosition().x) - 2*p_size, int(arena.getPosition().y) + 1, int(arena.getSize().y + arena.getPosition().y) - 2*p_size);
                while(!CanSpawn)
                    cord_p = SpawnMonster(int(arena.getPosition().x) + 1, int(arena.getSize().x + arena.getPosition().x) - 2*p_size, int(arena.getPosition().y) + 1, int(arena.getSize().y + arena.getPosition().y) - 2*p_size);
                m->x_pos = cord_p.first;
                m->y_pos = cord_p.second;
            }
            sf::CircleShape m_shape(p_size,52);
            m_shape.setFillColor(sf::Color::Red);
            m_shape.setPosition(m->x_pos,m->y_pos);
            m->shape = m_shape;
            m->size = m_shape.getRadius();
            monsters.push_back(m);
            spawn_clock.restart();
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

        player.Update_HP(curr_hp, missing_hp);
        player.shape.setPosition(player.x_pos, player.y_pos);  
        
        window.draw(arena);
        for (auto& weapon : player.weapons) {
            //weapon->Fire(monsters, player);
            window.draw(weapon->Display(player));
        }
        window.draw(player.shape);
        window.draw(curr_hp);
        window.draw(missing_hp);
        for (auto m = monsters.begin(); m != monsters.end();) {
            (*m)->Deal_Damage(player);
            if (player.hp <= 0) {
                died = true;
                menu_opened = true;
                view.setCenter(w_width/2,w_height/2);
                window.setView(view);
                Clear_Arena(monsters, player, arena);
                break;
            }
            else if ((*m)->hp <= 0) {
                delete *m;
                m = monsters.erase(m);
            }
            else {
                window.draw((*m)->shape);
                (*m)->Move(player, monsters);
                ++m;
            }
        }
        window.display();
    }
    return 0;
}