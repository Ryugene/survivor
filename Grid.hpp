#pragma once
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

inline map<pair<int,int>, bool> grid_map; // pairs<x,y> separated by line spacing
inline map<pair<int,int>, bool> monster_ground_free_map; // map of available squares - true if free
inline vector<pair<int,int>> grid_keys; // used for grid_map random access

void Create_Grid_Maps();
pair<int,int> Get_Grid_Cords_From_Position(double x, double y);
void Draw_Map();
void Draw_Grid(sf::RectangleShape& arena, sf::RenderWindow& window);