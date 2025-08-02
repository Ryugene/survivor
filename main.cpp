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
void Center_Text_Choose_Y(sf::RenderWindow& window, sf::Text& text, float y, sf::FloatRect& bounds) {
    text.setPosition(window.getSize().x/2 - bounds.width/2 , y);
}

bool Mouse_In_Text(sf::Vector2i mouse_pos, sf::Text text, sf::FloatRect& bounds) {
    float x = text.getPosition().x;
    float y = text.getPosition().y;
    if (mouse_pos.x >= x && mouse_pos.x <= x + bounds.width && mouse_pos.y >= y && mouse_pos.y <= y + bounds.height) {
        return true;
    }
    return false;
}

void Text_Hover(vector<sf::Text>& vt, sf::Vector2i& mouse_pos) {
    for (auto& text : vt) {
        sf::FloatRect bounds = text.getLocalBounds();
        if (Mouse_In_Text(mouse_pos,text,bounds)) {
            text.setFillColor(sf::Color::Red);
        }
        else
            text.setFillColor(sf::Color::White);
    }
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
    sf::RectangleShape curr_hp(sf::Vector2f(player.hp / player.max_hp*2*p_size, p_size/3));
    sf::RectangleShape missing_hp(sf::Vector2f((1.f - player.hp/player.max_hp)*2*p_size, p_size/3));
    arena.setFillColor(sf::Color::White);
    player_shape.setFillColor(sf::Color::Yellow);
    curr_hp.setFillColor(sf::Color::Red);
    missing_hp.setFillColor(sf::Color::Black);
    
    vector<Monster> monsters;
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
    

    while (window.isOpen()) {
        // MENU //
        if (menu_opened) {
            window.clear();
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            vector<sf::Text> vt;

            sf::Text play_text;
            play_text.setString("PLAY");
            play_text.setFont(font);
            play_text.setCharacterSize(150);
            sf::FloatRect play_rect = play_text.getLocalBounds();
            play_text.setOrigin(play_rect.left, play_rect.top);
            Center_Text_Choose_Y(window,play_text,300,play_rect);
            vt.push_back(play_text);

            sf::Text exit_text;
            exit_text.setString("EXIT");
            exit_text.setFont(font);
            exit_text.setCharacterSize(150);
            sf::FloatRect exit_rect = exit_text.getLocalBounds();
            exit_text.setOrigin(exit_rect.left, exit_rect.top);
            Center_Text_Choose_Y(window,exit_text,500,exit_rect);
            vt.push_back(exit_text);

            Text_Hover(vt,mouse_pos);
            for (auto& text : vt) {
                window.draw(text);
            }
            window.display();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    menu_opened = false;
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && Mouse_In_Text(mouse_pos, vt[0],play_rect)) {
                    menu_opened = false;
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && Mouse_In_Text(mouse_pos, vt[1],exit_rect)) {
                    menu_opened = false;
                    window.close();
                }
            }
            continue;
        }
        // MENU //
        view.setCenter(player.x_pos, player.y_pos);
        window.setView(view);
        window.clear();
        sf::Time time = spawn_clock.getElapsedTime();
        float t = time.asSeconds();
        if (t >= 0.01 && monsters.size() < max_monsters) {
            Monster m(int(arena.getPosition().x) + 1, int(arena.getSize().x + arena.getPosition().x) - 2*p_size, int(arena.getPosition().y) + 1, int(arena.getSize().y + arena.getPosition().y) - 2*p_size,
            5.f, 5.f, 2, 50, SetID(monsters));
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
        player_shape.setPosition(player.x_pos, player.y_pos);  
        
        window.draw(arena);
        for (auto weapon : player.weapons) {
            AntiGayEnergy g;
            weapon = &g;
            //weapon->Fire(monsters, player);
            window.draw(weapon->Display(player));
        }
        window.draw(player_shape);
        window.draw(curr_hp);
        window.draw(missing_hp);
        for (auto m = monsters.begin(); m != monsters.end(); ++m) {
            if (m->hp <= 0) {
                monsters.erase(m);
            }
            else
                window.draw(m->shape);
            m->Move(player, monsters);
            m->Deal_Damage(player);
            if (player.hp <= 0) {
                death_text.setPosition(player.x_pos - (w_width/10), player.y_pos - (w_height/3));
                window.draw(death_text);
            }
        }
        window.display();
    }
    return 0;
}