#include "resource.hpp"
#include "Grid.hpp"

void Create_Grid_Maps() {
    int start_y = arena.getPosition().y;
    int start_x = arena.getPosition().x;
    for (int y = start_y; y < start_y + arena_height; y += line_spacing) {
        for (int x = start_x; x < start_x + arena_width; x += line_spacing) {
            grid_map.insert(make_pair(make_pair(x,y), false));
            monster_ground_free_map.insert(make_pair(make_pair(x,y), true));
            grid_keys.push_back(make_pair(x,y));
        }
    }
}

pair<int,int> Get_Grid_Cords_From_Position(double x, double y) {
    int x_int = static_cast<int>(x);
    int y_int = static_cast<int>(y);
    x_int -= x_int % line_spacing;
    y_int -= y_int % line_spacing;
    return make_pair(x_int, y_int);
}

void Draw_Map() {
    for (auto& kv : grid_map) {
        if (kv.second) {
            sf::RectangleShape square(sf::Vector2f(line_spacing,line_spacing));
            square.setFillColor(sf::Color::Green);
            square.setPosition(sf::Vector2f(kv.first.first, kv.first.second));
            window.draw(square);
        }
    }
}

void Draw_Grid(sf::RectangleShape& arena, sf::RenderWindow& window) {
    int start_y = arena.getPosition().y;
    int start_x = arena.getPosition().x;
    //horizontal lines
    for (int y = start_y; y < start_y + arena_height; y += line_spacing) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(start_x, y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(start_x + arena_width, y), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
    }
    //vertical lines
    for (int x = start_x; x < start_x + arena_width; x += line_spacing) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, start_y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x, start_y + arena_height), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
    }
}