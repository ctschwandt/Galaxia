#ifndef EXPLOSION_H
#define EXPLOSION_H

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
#include "Player.h"
#include "Laser.h"
#include "Alien.h"
#include "BlueAlien.h"
#include "PurpleAlien.h"

enum State
{
    DISSIPATE,
    FALL,
    FADE
};
    
class Shrapnel: public GameObject
{
public:
    //================== ...structors ====================//
    Shrapnel(Surface & surface, Rect rect = {0, 0, 4, 4}, vec2i velocity = {0, 0}, bool is_alive = false,
             Color color = {255, 165, 0}, int state = DISSIPATE, int dissipate_timer = 0, int fade_timer = 0)
        : GameObject(surface, rect, velocity, is_alive, SHRAPNELS),
          color_(color), state_(state), dissipate_timer_(dissipate_timer), fade_timer_(fade_timer)
    {}
    //====================================================//
    
    //================ getters and setters ================//
    int & state() { return state_; }
    int state() const { return state_; }
    int & dissipate_timer() { return dissipate_timer_; }
    int dissipate_timer() const { return dissipate_timer_; }
    int & fade_timer() { return fade_timer_; }
    int fade_timer() const { return fade_timer_; }
    Color & color() { return color_; }
    Color color() const { return color_; }
    static Color & init_color() { return init_color_; }
    static Color & target_color() { return target_color_; }
    //=====================================================//

    //====================== methods ======================//
    void draw();
    void update();
    void randomize_trajectory();
    void explode(const int, const int);
    void print();
    //=====================================================//
    
private:
    static Color init_color_;
    static Color target_color_;
    
    Color color_;
    int state_;
    int dissipate_timer_;
    int fade_timer_;

};

inline
void Shrapnel::draw()
{
    if (is_alive())
        surface().put_rect(rect(), color());
}

inline
void Shrapnel::update()
{
    if (!is_alive())
        return;

    if (state() == DISSIPATE)
    {
        move();
        ++dissipate_timer();
        if (dissipate_timer() >= DISSIPATE_TIMER)
        {
            state() = FALL;
            dissipate_timer() = 0;
            dx() = 0;
            dy() = FALLING_SPEED;
        }
    }
    else if (state() == FALL)
    {
        move();
        ++fade_timer();
        if (fade_timer() >= FADE_TIMER)
        {
            state() = FADE;
            fade_timer() = 0;
        }
    }
    else if (state() == FADE)
    {
        // approaches the color grey
        if (color().r > target_color().r) color().r -= 2;
        if (color().g > target_color().g) color().g -= 1;
        if (color().b < target_color().b) color().b += 1;
        
        move();
        if (y() >= H)
        {
            kill();
            state() = DISSIPATE;
        }
    }    
}

inline
void Shrapnel::randomize_trajectory()
{
    dissipate_timer() = rand() % DISSIPATE_TIMER;
    if (rand() % 2 == 0)
    {
        dx() += 1;
    }
    else
    {
        dx() -= 1;
    }
}

inline
void Shrapnel::explode(const int ax, const int ay)
{
    is_alive() = true;
    color() = init_color();
    x() = ax;
    y() = ay;
    randomize_trajectory();
    state() = DISSIPATE;
}

inline
void Shrapnel::print()
{
    std::cout << "Shrapnel ["
       << "Position: (" << x() << ", " << y() << "), "
       << "Velocity: (" << dx() << ", " << dy() << "), "
       << "Alive: " << (is_alive() ? "Yes" : "No") << ", "
       << "State: ";

    switch (state())
    {
        case DISSIPATE:
            std::cout << "DISSIPATE";
            break;
        case FALL:
            std::cout << "FALL";
            break;
        case FADE:
            std::cout << "FADE";
            break;
        default:
            std::cout << "UNKNOWN";
    }

    std::cout << ", Dissipate Timer: " << dissipate_timer()
         << ", Fade Timer: " << fade_timer();

    std::cout << ']';
}


class Explosion: public GameObject
{
  public:
    //================== ...structors ====================//
    Explosion(Surface & surface, Rect rect = {0, 0, 0, 0}, vec2i velocity = {0, 0}, bool is_alive = false)
        : GameObject(surface, rect, velocity, is_alive, EXPLOSIONS),
          shrapnels
    {
        Shrapnel(surface, {0, 0, 4, 4},
    {-DISS_SPEED, -DISS_SPEED + FALLING_SPEED}, false, Shrapnel::init_color(), DISSIPATE, 0, 0), // NW
        Shrapnel(surface, {0, 0, 4, 4},
    {0, -DISS_SPEED + FALLING_SPEED}, false, Shrapnel::init_color(), DISSIPATE, 0, 0),  // N
        Shrapnel(surface, {0, 0, 4, 4},
    {DISS_SPEED, -DISS_SPEED + FALLING_SPEED}, false, Shrapnel::init_color(), DISSIPATE, 0, 0),  // NE
        Shrapnel(surface, {0, 0, 4, 4},
    {-DISS_SPEED, FALLING_SPEED}, false, Shrapnel::init_color(), DISSIPATE, 0, 0),      // W
        Shrapnel(surface, {0, 0, 4, 4},
    {0, FALLING_SPEED}, false, Shrapnel::init_color(), DISSIPATE, 0, 0),       // C
        Shrapnel(surface, {0, 0, 4, 4},
    {DISS_SPEED, FALLING_SPEED}, false, Shrapnel::init_color(), DISSIPATE, 0, 0),       // E
        Shrapnel(surface, {0, 0, 4, 4},
    {-DISS_SPEED, DISS_SPEED + FALLING_SPEED}, false, Shrapnel::init_color(), DISSIPATE, 0, 0),  // SW
        Shrapnel(surface, {0, 0, 4, 4},
    {0, DISS_SPEED + FALLING_SPEED}, false, Shrapnel::init_color(), DISSIPATE, 0, 0),   // S
        Shrapnel(surface, {0, 0, 4, 4},
    {DISS_SPEED, DISS_SPEED + FALLING_SPEED}, false, Shrapnel::init_color(), DISSIPATE, 0, 0)    // SE
    }
    {}
    //====================================================//
    
    //================ getters and setters ================//
    static Sound & explosion_sound() { return explosion_sound_; }
    //=====================================================//

    //====================== methods ======================//
    void draw();
    void update();
    void explode(const int, const int);
    bool is_dead();
    void set_default_velocity();
    //=====================================================//
    
    //private:
    Shrapnel shrapnels[9];

    static Sound explosion_sound_;

};

inline
void Explosion::draw()
{
    if (is_alive())
    {
        //std::cout << "drawing explosion " << std::endl;
        for (int i = 0; i < 9; ++i)
        {
            shrapnels[i].Shrapnel::draw();
        }
    }
}

inline
void Explosion::update()
{
    if (is_alive())
    {
        for (int i = 0; i < 9; ++i)
        {
            shrapnels[i].Shrapnel::update();
        }
    }
    is_alive() = !is_dead();
}

inline
void Explosion::explode(const int ax, const int ay)
{
    is_alive() = true;
    x() = ax;
    y() = ay;
    set_default_velocity();
    for (int i = 0; i < 9; ++i)
    {
        shrapnels[i].explode(ax, ay);
    }
    explosion_sound().play();
}

inline
bool Explosion::is_dead()
{
    for (int i = 0; i < 9; ++i)
    {
        if (shrapnels[i].is_alive())
        {
            return false;
        }
    }
    return true;
}

inline
void Explosion::set_default_velocity()
{
    vec2i velocities[9] =
        {
            {-DISS_SPEED, -DISS_SPEED + FALLING_SPEED},  // NW
            {0, -DISS_SPEED + FALLING_SPEED},           // N
            {DISS_SPEED, -DISS_SPEED + FALLING_SPEED},  // NE
            {-DISS_SPEED, 0},                           // W
            {0, 0},                                     // C (Center)
            {DISS_SPEED, 0},                            // E
            {-DISS_SPEED, DISS_SPEED + FALLING_SPEED},  // SW
            {0, DISS_SPEED + FALLING_SPEED},            // S
            {DISS_SPEED, DISS_SPEED + FALLING_SPEED}    // SE
        };

    for (int i = 0; i < 9; ++i)
    {
        shrapnels[i].velocity() = velocities[i];
    }
}


#endif
