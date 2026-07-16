#include "Monsters.hpp"
#include "Player.hpp"
#include "resource.hpp"
#include "Grid.hpp"

// Initialization
void Create_Available_MonsterIDs(set<int>& available_monster_ids) {
    available_monster_ids.clear();
    for (int i = 0; i <= max_monsters ; ++i) {
        available_monster_ids.insert(i);
    }
}

int Assign_MonsterID(set<int>& available_monster_ids) {
    auto first = available_monster_ids.begin();
    int new_id = *first;
    available_monster_ids.erase(first);
    return new_id;
}

Monster::Monster(vector<pair<int,int>>& grid_keys, map<pair<int,int>, bool>& free, Player& p, 
                double m_xp, double m_hp, double m_speed, double m_damage) {

    if (SpawnMonster(grid_keys, free, p)) {
        xp = m_xp;
        hp = m_hp;
        speed = m_speed;
        damage = m_damage;
        id = Assign_MonsterID(available_monster_ids);
        sf::CircleShape m_shape(p.size, 50);
        m_shape.setFillColor(sf::Color::Red);
        m_shape.setPosition(x_pos, y_pos);
        shape = m_shape;
        size = m_shape.getRadius();
    }
}

// true if monster is in a safe distance from player
bool Monster::CanSpawn(Player& p) {
    return (abs(x_pos - p.x_pos) >= w_width/4 && abs(y_pos - p.y_pos) >= w_height/4);
}

// true if monster Spawned. Tries to spawn a monster
bool Monster::SpawnMonster(vector<pair<int,int>>& grid_keys, map<pair<int,int>, bool>& free, Player& p) {
    int start = 0;
    int end = grid_keys.size()-1;
    random_device w;
    default_random_engine gen(w());
    uniform_int_distribution<int32_t> ind(start, end);
    pair<int,int> cords = grid_keys[ind(gen)];
    if (free[cords] && CanSpawn(p)) {
        free[cords] = false;
        x_pos = static_cast<double>(cords.first);
        y_pos = static_cast<double>(cords.second);
        return true;
    }
    return false;
}


void Monster::Deal_Damage(Player& p) {
    double dx = abs(p.x_pos - x_pos);
    double dy = abs(p.y_pos - y_pos);
    double t = p.immortality_clock.getElapsedTime().asSeconds();
    if (dx <= p.size && dy <= p.size && p.hp > 0 && t >= 0.5) {
        p.hp -= damage;
        p.immortality_clock.restart();
    }
}

void Monster::ChooseDestination(Player& p) {
    /*if (clock.getElapsedTime().asSeconds() < 1)
            return;
    else clock.restart();*/
    double x = p.x_pos - x_pos;
    double y = p.y_pos - y_pos;
    double pi = 3.14159265358979323846;
    double alpha = atan2(y, x) * 180.0 / pi;
    alpha = - alpha; // some inversion problem
    double dx = 0;
    double dy = 0;
    //cout << alpha << " " << x_pos << " " << y_pos << "\n";
    if (alpha > -22.5 && alpha <= 22.5) {
        dx += speed;                    // →
    }
    else if (alpha > 22.5 && alpha <= 67.5) {
        dx += speed;
        dy -= speed;                    // ↗
    }
    else if (alpha > 67.5 && alpha <= 112.5) {
        dy -= speed;                    // ↑
    }
    else if (alpha > 112.5 && alpha <= 157.5) {
        dx -= speed;
        dy -= speed;                    // ↖
    }
    else if (alpha > 157.5 || alpha <= -157.5) {
        dx -= speed;                    // ←
    }
    else if (alpha > -157.5 && alpha <= -112.5) {
        dx -= speed;
        dy += speed;                    // ↙
    }
    else if (alpha > -112.5 && alpha <= -67.5) {
        dy += speed;                    // ↓
    }
    else if (alpha > -67.5 && alpha <= -22.5) {
        dx += speed;
        dy += speed;                    // ↘
    }

    Move(dx, dy);
}

void Monster::Move(double dx, double dy) {
    pair<int,int> grid_cords = Get_Grid_Cords_From_Position(x_pos, y_pos);
    pair<int,int> new_grid_cords = Get_Grid_Cords_From_Position(x_pos + dx, y_pos + dy);
    if (grid_cords == new_grid_cords) { // Move within the same grid
        shape.setPosition(x_pos + dx, y_pos + dy);
        return;
    }
    else if (!monster_ground_free_map[new_grid_cords]) { // grid to move to is occupied
        return;
    }

    monster_ground_free_map[new_grid_cords] = false;
    monster_ground_free_map[grid_cords] = true;
    shape.setPosition(x_pos + dx, y_pos + dy);
}