#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

void Center_Text_Choose_Y(sf::RenderWindow& window, sf::Text& text, double y, sf::FloatRect& bounds);
bool Mouse_In_Text(sf::Vector2i mouse_pos, sf::Text text, sf::FloatRect& bounds);
void Text_Hover(vector<sf::Text>& vt, sf::Vector2i& mouse_pos);
void Display_Menu(bool& died, bool& menu_opened, sf::RenderWindow& window);