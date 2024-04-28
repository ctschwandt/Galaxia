#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"

#include "vec2.h"
#include "GameObject.h"
#include "Laser.h"

class Player: public GameObject
{
public:
     //============ ...structors ============//
    Player(Surface & surface, Rect rect = image().getRect(), int dx = SPEED, int dy = SPEED, bool is_alive = false,
           int lives = DEFAULT_PLAYER_LIVES, int score = 0, int attack_delay = 0,
           bool fired = false, int iv_frames = 0, bool hit = false)
        : GameObject(surface, rect, {dx, dy}, is_alive, PLAYERS),
          lives_(lives), score_(score), attack_delay_(attack_delay),
          fired_(fired), iv_frames_(iv_frames), hit_(hit)
    {}
    //======================================//
    
    //================ getters and setters ================//
    int & lives() { return lives_; }
    int lives() const { return lives_; }
    int & score() { return score_; }
    int score() const { return score_; }
    int & attack_delay() { return attack_delay_; }
    int attack_delay() const { return attack_delay_; }
    bool & fired() { return fired_; }
    bool fired() const { return fired_; }
    int & iv_frames() { return iv_frames_; }
    int iv_frames() const { return iv_frames_; }
    bool & hit() { return hit_; }
    bool hit() const { return hit_; }
    static Image & image() { return image_; }
    //=====================================================//

    //====================== methods ======================//
    void build(); // inherited // center ship
    bool top_hit_top();
    bool bottom_hit_bottom();
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void move(KeyPressed &);
    // void kill(); // inherited
    void draw();
    void update(KeyPressed &, std::vector < Laser > &);
    void find_collision(std::vector < Laser > &);
    void take_damage();
    //=====================================================//

private:
    int lives_;
    int score_;
    int attack_delay_;
    bool fired_;
    int iv_frames_;
    bool hit_;

    static Image image_;
};

inline
std::ostream & operator<<(std::ostream & cout, const Player & player)
{
    cout << "<Rect: (" << player.x() << ", " << player.y()
         << ", " << player.w() << ", " << player.h() << "), "
         << "Lives: " << player.lives() << ", "
         << "Score: " << player.score() << ", "
         << "Attack Delay: " << player.attack_delay() << ", "
         << "Fired: " << (player.fired() ? "Yes" : "No") << '>';

    return cout;
}

inline
void Player::build()
{
    x() = (W - 1) / 2;
    y() = H / 1.13;
    is_alive() = true;
}

inline
void Player::move_left()
{
    x() -= dx();
}

inline
void Player::move_right()
{
    x() += dx();
}

inline
void Player::move_up()
{
    y() -= dy();
}

inline
void Player::move_down()
{
    y() += dy();
}

inline
void Player::draw()
{
    if(iv_frames() % 14 <= 6 && is_alive())
        surface().put_image(image(), rect());
}

inline
bool Player::top_hit_top()
{
    return (y() <= H / 2);
}

inline
bool Player::bottom_hit_bottom()
{
    return (y() >= H - BOTTOM_OFFSET - 35);
}

inline
void Player::move(KeyPressed & keypressed)
{
    //===================================================
    // take user inputs to move spaceship in one of
    // 8 cardinal directions
    //===================================================
    bool up = keypressed[UPARROW] || keypressed['w'];
    bool down = keypressed[DOWNARROW] || keypressed['s'];
    bool left = keypressed[LEFTARROW] || keypressed['a'];
    bool right = keypressed[RIGHTARROW] || keypressed['d'];

    if (up && !top_hit_top())
    {
        if (right && !right_hit_right())
        {
            move_up();
            move_right();
        }
        else if (left && !left_hit_left())
        {
            move_up();
            move_left();
        }
        else
        {
            move_up();
        }
    }
    else if (down && !bottom_hit_bottom())
    {
        if (right && !right_hit_right())
        {
            move_down();
            move_right();
        }
        else if (left && !left_hit_left())
        {
            move_down();
            move_left();
        }
        else
        {
            move_down();
        }
    }
    else if (right && !right_hit_right())
    {
        move_right();
    }
    else if (left && !left_hit_left())
    {
        move_left();
    }
}

inline
void Player::update(KeyPressed & keypressed, std::vector < Laser > & lasers)
{
    move(keypressed);

    //================
    // fire laser
    //================
    int lim = lasers.size();
    if (keypressed[SPACE] && attack_delay() == 0)
    {
        // search for laser that isn't alive,
        // set it to alive then fire that one.
        for (int i = 0; i < lim; ++i)
        {
            if (!lasers[i].is_alive())
            {
                lasers[i].player_fire(rect());
                fired() = true;
                break;
            }
        }
    }
    if (fired())
    {
        ++attack_delay();
        if (attack_delay() == PLAYER_ATTACK_DELAY)
        {
            attack_delay() = 0;
        }
    }

    //===============================================
    // 1) move lasers
    // 2) kill them if they move off the
    // top or bottom of the screen
    //===============================================
    for (int i = 0; i < lim; ++i)
    {
        if (lasers[i].is_alive())
        {
            lasers[i].move();
            if (lasers[i].y() <= 0 && lasers[i].player()
                || lasers[i].y() >= H && !lasers[i].player())
            {
                lasers[i].kill();
            }
        }
    }

    //============================
    // reset iv_frames if needed
    //============================
    if (iv_frames() >= IV_FRAMES)
    {
        iv_frames() = 0;
        hit() = false;
    }
    else if (hit())
    {
        ++iv_frames();
    }
}

inline
void Player::find_collision(std::vector < Laser > & lasers)
{
    int lim = lasers.size();
    for (int i = 0; i < lim; ++i)
    {
        if (lasers[i].collides(*this))
        {
            lasers[i].kill();
            take_damage();
            //explosion_sound().play();
        }
    }
}

inline
void Player::take_damage()
{
    hit() = true;
    lives() -= 1;
    if (lives() < 0)
    {
        is_alive() = false;
    }
}

#endif
