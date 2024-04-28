#ifndef LASER_H
#define LASER_H

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"

#include "vec2.h"
#include "GameObject.h"

class Laser: public GameObject
{
public:
    Laser(Surface & surface, Rect rect = {-1, -1, 2, 20}, int dx = 0, int dy = -LASER_SPEED, bool is_alive = false,
          Color color = ENEMY_LASER_COLOR, bool player = false)
        : GameObject(surface, rect, {dx, dy}, is_alive, LASERS), color_(color), player_(player)
    {}

    //================ getters and setters ================//
    Color & color() { return color_; }
    Color color() const { return color_; }
    bool & player() { return player_; }
    bool player() const { return player_; }
    static Sound & sound() { return sound_; }
    //=====================================================//

    //====================== methods ======================//
    void player_fire(const Rect &);
    void alien_fire(const Rect &);
    // void move();
    // void kill();
    void draw();
    // void find_collision(std::vector < BlueAlien > &);
    // void find_collision(std::vector < PurpleAlien > &);
    // void find_collision(std::vector < RedAlien > &);
    // void find_collision(std::vector < YellowAlien > &);
    //=====================================================//
    
private:
    Color color_;
    bool player_;
    static Sound sound_;
};

inline
void Laser::player_fire(const Rect & rect)
{
    dy() = -LASER_SPEED;
    x() = rect.x + rect.w / 2;
    y() = rect.y - rect.h / 2;
    w() = 2;
    h() = 20;
    is_alive() = true;
    player() = true;
    color() = PLAYER_LASER_COLOR;
    //sound().play();
}

inline
void Laser::alien_fire(const Rect & rect)
{
    dy() = LASER_SPEED;
    x() = rect.x + rect.w / 2;
    y() = rect.y + rect.h / 2;
    w() = 2;
    h() = 10;
    is_alive() = true;
    player() = false;
    color() = ENEMY_LASER_COLOR;
    //sound().play();
}

inline
void Laser::draw()
{
    if (is_alive())
    {
        surface().put_rect(rect(), color());
    }
}

// inline
// void Laser::find_collision(std::vector < BlueAlien > & blues)
// {
//     int lim = blues.size();
//     for (int i = 0; i < lim; ++i)
//     {
//         if (collides(blues[i]))
//         {
//             explosion().play();
//             blues[i].kill();
//             kill();
//         }
//     }
// }

inline
std::ostream & operator<<(std::ostream & cout, const Laser & laser)
{
    cout << "<Rect: (" << laser.rect().x << ", " << laser.rect().y << ", " << laser.rect().w << ", " << laser.rect().h << "), "
         << "Color: (" << laser.color().r << ", " << laser.color().g << ", " << laser.color().b << "), "
         << "Player: " << (laser.player() ? "true" : "false") << ", "
         << "Is Alive: " << (laser.is_alive() ? "true" : "false") << ", "
         << "dx: " << laser.dx() << ", "
         << "dy: " << laser.dy() << '>';

    return cout;
}

#endif
