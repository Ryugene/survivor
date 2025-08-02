#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

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
void Display_Menu(bool& died, bool& menu_opened, sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("youmurdererbb_reg.ttf");
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
            died = false;
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && Mouse_In_Text(mouse_pos, vt[1],exit_rect)) {
            menu_opened = false;
            window.close();
        }
    }
}