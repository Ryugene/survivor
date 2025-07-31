#include <utility>
#include <random>
#include <math.h>

using namespace std;

double PI = 3.1415926535;

pair<int,int> SpawnMonster(int w1, int w2, int h1, int h2) {
    random_device w;
    default_random_engine engine_w(w());
    uniform_int_distribution<int32_t> widths(w1, w2);
    random_device h;
    default_random_engine engine_h(h());
    uniform_int_distribution<int32_t> heights(h1,h2);
    return make_pair(widths(engine_w), heights(engine_h));
}

class Monster {
public:
    Monster(int w1, int w2, int h1, int h2, float m_xp, float m_hp, float m_speed, float m_damage, int m_id) {
        pair<int, int> p = SpawnMonster(w1, w2, h1, h2);
        x_pos = float(p.first);
        y_pos = float(p.second);
        xp = m_xp;
        hp = m_hp;
        speed = m_speed;
        damage = m_damage;
        id = m_id;
    }
    float x_pos;
    float y_pos;
    float xp;
    float hp;
    float speed;
    float damage;
    float size; // radius
    sf::Clock clock;
    sf::CircleShape shape;
    bool spawn = true;
    int id;

    /*bool CanMove(float dx, float dy, Monster& m, vector<Monster>& vm) {
    for (int p = 0; p < m.shape.getPointCount(); ++p) {
        pair<float,float> dm = make_pair(m.shape.getPoint(p).x+dx+m.x_pos, m.shape.getPoint(p).y+dy+m.y_pos);
        for (int i = 0; i < vm.size(); ++i) {
            pair<float,float> rel = make_pair(abs(dm.first - vm[i].x_pos), abs(dm.second - vm[i].y_pos)); // relative position to monster center
            if (m.id != vm[i].id && rel.first*rel.first + rel.second*rel.second <= vm[i].size*vm[i].size) {
                return false;
            }
        }
    }
    return true;
}*/


    sf::CircleShape Move(Player& p, vector<Monster>& vm) { // complexity: vm^2*100 ... vm < 1000?
        double x = abs(p.x_pos - x_pos);
        double y = abs(p.y_pos - y_pos);
        double alpha = atan(y/x);
        double beta = atan(x/y);
        double dx = speed*sin(beta);
        double dy = speed*sin(alpha);
        for (int d = 0; d < 90; ++d) {
            double alpha1 = (180*alpha/PI) - d;
            double beta1 = (180*beta/PI) + d;
            double alpha2 = (180*alpha/PI) + d;
            double beta2 = (180*beta/PI) - d;
            double dx1 = speed*sin(beta1/180*PI);
            double dx2 = speed*sin(beta2/180*PI);
            double dy1 = speed*sin(alpha1/180*PI);
            double dy2 = speed*sin(alpha2/180*PI);
            //for (int i = vm.size(); ++i) {
                //pair<float,float>
            //}
        }
        sf::CircleShape dir(size/5, 10);
        dir.setFillColor(sf::Color::Cyan);
        dir.setPosition(sf::Vector2f(x_pos + size - (size/5), y_pos + size - (size/5) ));
        if (p.x_pos <= x_pos && p.y_pos >= y_pos) { // bottom left
            dir.setPosition(dir.getPosition().x - dx, dir.getPosition().y + dy);
        }
        else if (p.x_pos <= x_pos && p.y_pos <= y_pos) { // top left
            dir.setPosition(dir.getPosition().x - dx, dir.getPosition().y - dy);
        }
        else if (p.x_pos >= x_pos && p.y_pos <= y_pos) { // top right
            dir.setPosition(dir.getPosition().x + dx, dir.getPosition().y - dy);
        }
        else { // bottom right
            dir.setPosition(dir.getPosition().x + dx, dir.getPosition().y + dy);
        }
        return dir;
    }
};

