#pragma once
#include <SFML/Graphics.hpp>

inline int w_width;
inline int w_height;
inline const int arena_width;
inline const int arena_height;
inline const int line_spacing; //grid squares pixel size
inline sf::RenderWindow window(sf::VideoMode(w_width, w_height), "LGBT survivor",sf::Style::Fullscreen);
inline sf::RectangleShape arena(sf::Vector2f(arena_width, arena_height));