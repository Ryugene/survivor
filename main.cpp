#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Player.hpp"
#include "Monsters.hpp"
#include "Weapons.hpp"
#include <iostream>
#include "menu.hpp"
#include "resource.hpp"
#include "DataStructures.hpp"
#include "Grid.hpp"

using namespace std;

// deletes monsters, weapons, sets start weapon, resets player stats to default
void Clear_Arena(SparseMonsterSet& MSet, Player& p, sf::RectangleShape& arena) {
    for (auto& m : MSet) {
        MSet.erase((*m).id, available_monster_ids);
    }
    p.weapons.clear();
    auto s_w = make_unique<AntiGayEnergy>();
    p.weapons.push_back(move(s_w));
    p.Reset(arena.getSize().x/2 + p.size, arena.getSize().y/2 + p.size);
}

int main()
{
    double p_size = (w_width + w_height) / 200;
    const double player_start_x = arena_width/2 + p_size;
    const double player_start_y = arena_height/2 + p_size;
    auto s_w = make_unique<AntiGayEnergy>();
    Player player(player_start_x, player_start_y, p_size, move(s_w));
    sf::View view(sf::FloatRect(0,0, w_width,w_height));
    sf::CircleShape player_shape(p_size,250);
    sf::RectangleShape curr_hp(sf::Vector2f(player.hp / player.max_hp*2*p_size, p_size/3));
    sf::RectangleShape missing_hp(sf::Vector2f((1.f - player.hp/player.max_hp)*2*p_size, p_size/3));
    arena.setFillColor(sf::Color::White);
    player_shape.setFillColor(sf::Color::Yellow);
    player.shape = player_shape;
    curr_hp.setFillColor(sf::Color::Red);
    missing_hp.setFillColor(sf::Color::Black);
    
    SparseMonsterSet monsters(max_monsters);
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

    Create_Available_MonsterIDs(available_monster_ids);
    Create_Grid_Maps();

    bool menu_opened = true;

    while (window.isOpen()) {
        // MENU //
        if (menu_opened) {
            window.clear();
            if (player.dead) {
                sf::FloatRect bounds = death_text.getLocalBounds();
                death_text.setPosition(w_width/2 - bounds.width/2, 0);
                window.draw(death_text);
            }
            Display_Menu(player.dead, menu_opened, window);
            continue;
        }
        // MENU //
        // GAME STARTS //
        view.setCenter(player.x_pos, player.y_pos);
        window.setView(view);
        window.clear();
        sf::Time spawn_clock_time = spawn_clock.getElapsedTime();
        double spawn_time = static_cast<double>(spawn_clock_time.asSeconds());
        double spawn_rate = 0.01;

        // MONSTER SPAWN //
        if (spawn_time >= spawn_rate && monsters.size() < max_monsters) { //one monster per spawn_rate seconds
            double m_xp = 5;
            double m_hp = 5;
            double m_speed = player.speed/2;
            double m_damage = 11;
            auto m = make_unique<Type1>(grid_keys, monster_ground_free_map, player, m_xp, m_hp, m_speed, m_damage);
            // Monsters spawn in safe distance from player
            // Monsters are assigned one block from the grid
            m->SpawnMonster(grid_keys, monster_ground_free_map, player);
            monsters.insert(move(m));
            spawn_clock.restart();
        }
        // MONSTER SPAWN //

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.x_pos >= arena.getPosition().x + player.speed) {
            player.x_pos -= player.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.x_pos <= arena.getPosition().x + arena_width - 2*player.size - player.speed) {
            player.x_pos += player.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.y_pos >= arena.getPosition().y + player.speed) {
            player.y_pos -= player.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.y_pos <= arena.getPosition().y + arena_height - 2*player.size - player.speed) {
            player.y_pos += player.speed;
        }

        player.Update_HP(curr_hp, missing_hp);
        player.shape.setPosition(player.x_pos, player.y_pos);  
        
        window.draw(arena);
        for (auto& weapon : player.weapons) {
            weapon->Fire(monsters, player);
            window.draw(weapon->Display(player));
        }
        window.draw(player.shape);
        window.draw(curr_hp);
        window.draw(missing_hp);
        //Draw_Map();
        int m_i = 0;
        while (m_i < monsters.size()) {
            Monster* m = monsters[m_i].get();
            m->Deal_Damage(player);
            if (player.hp <= 0) {
                player.dead = true;
                menu_opened = true;
                view.setCenter(w_width/2,w_height/2);
                window.setView(view);
                Clear_Arena(monsters, player, arena);
                break;
            }
            else if (m->hp <= 0) {
                monsters.erase(m->id, available_monster_ids);
            }
            else {
                window.draw(m->shape);
                m->ChooseDestination(player);
                ++m_i;
            }
        }
        
        //Draw_Grid(arena, window);
        window.display();
    }
    return 0;
}