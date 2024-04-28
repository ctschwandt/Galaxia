#ifndef ALIEN_H
#define ALIEN_H

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
#include "Player.h"

enum ALIENSTATE
{
    FORMATION,
    SIN,
    DROP,
    // TARGET,
    IM_A_FIRIN_MY_LASER,
    DRIFT,
    SPAWNING,
    SPAWNED
};

class Alien: public GameObject
{
public:
     //================== ...structors ====================//
    Alien(Surface & surface, Rect rect = {0, 0, 0, 0}, int dx = SPEED, int dy = 0, bool is_alive = false, int id = ALIENS,
          int state = FORMATION, int attack_delay = 0, int points = 0, int laser_count = 0, bool fired = false)
        : GameObject(surface, rect, {dx, dy}, is_alive, id), state_(state), attack_delay_(attack_delay), points_(points),
          laser_count_(laser_count), fired_(fired),
          home_(GameObject(surface))
    {}
     //====================================================//
    
    //================ getters and setters ================//
    //virtual int & id() { return id_; }
    //virtual int id() const { return id_; }
    int & state() { return state_; }
    int state() const { return state_; }
    int & laser_count() { return laser_count_; }
    int laser_count() const { return laser_count_; }
    int & attack_delay() { return attack_delay_; }
    int attack_delay() const { return attack_delay_; }
    int & points() { return points_; }
    int points() const { return points_; }
    bool & fired() { return fired_; }
    bool fired() const { return fired_; }
    GameObject & home() { return home_; }
    GameObject home() const { return home_; }
    vec2i & spawn_pos() { return spawn_pos_; }
    vec2i spawn_pos() const { return spawn_pos_; }
    vec2i & target_pos() { return target_pos_; }
    vec2i target_pos() const { return target_pos_; }
    int & spawn_x() { return spawn_pos_.get_x(); }
    int spawn_x() const { return spawn_pos_.get_x(); }
    int & spawn_y() { return spawn_pos_.get_y(); }
    int spawn_y() const { return spawn_pos_.get_y(); }
    static int & attack_rate() { return attack_rate_; }
    static int & d_aggression() { return d_aggression_; }
    //=====================================================//

    //====================== methods ======================//
    virtual void draw() = 0;
    void kill();
    void move();
    void move(int d_x, int d_y = 0);
    bool in_formation_mode();
    bool in_drift_mode();
    bool in_attack_mode();
    bool in_spawning_mode();
    bool in_spawned_mode();
    bool is_home();
    void return_home();
    void fire_laser(std::vector < Laser > &);
    void formation_velocity();
    void sin_velocity();
    void drop_velocity();
    void target_velocity();
    void drift_velocity();
    void spawn_velocity();
    virtual void update(std::vector < Laser > &, const bool, Player &);
    void find_collisions(std::vector < Laser > &, Player &);
    //=====================================================//

protected:
    int state_;
    int attack_delay_;
    int points_;
    int laser_count_;
    bool fired_;
    GameObject home_;
    vec2i spawn_pos_;
    vec2i target_pos_;
    static int attack_rate_;
    static int d_aggression_;
};

inline
std::ostream & operator<<(std::ostream & cout, const Alien & alien)
{
    cout << "<Alien: ";
    cout << "Rect: (" << alien.x() << ", " << alien.y() << ", ";
    cout << alien.w() << ", " << alien.h() << "), ";
    cout << "Velocity: (" << alien.dx() << ", " << alien.dy() << "), ";
    cout << "State: " << alien.state() << ", ";
    cout << "Attack Delay: " << alien.attack_delay() << ", ";
    cout << "Is Alive: " << (alien.is_alive() ? "true" : "false") << '>';
    return cout;
}

inline
void Alien::move()
{
    if (is_alive())
    {
        x() += dx();
        y() += dy();
    
        home().move();
    }    
}

inline
void Alien::kill()
{
    GameObject::kill();

    if (attack_rate() - d_aggression() > 0)
    {
        d_aggression() * 1.2;
    }
}
inline
bool Alien::in_formation_mode()
{
    return (state() == FORMATION);
}

inline
bool Alien::in_attack_mode()
{
    return (SIN <= state() && state() <= DROP);
}

inline
bool Alien::in_drift_mode()
{
    return (state() == DRIFT);
}

inline
bool Alien::in_spawning_mode()
{
    return (state() == SPAWNING);
}

inline
bool Alien::in_spawned_mode()
{
    return (state() == SPAWNED);
}

inline
bool Alien::is_home()
{
    // return (x() == home().x() && y() == home().y());
    // return (x() - SPEED <= home().x() && home().x() <= x() + SPEED
    //         && y() - SPEED <= home().y() && home().y() <= y() + SPEED);
    return (y() - SPEED <= home().y() && home().y() <= y() + SPEED);
}

inline
void Alien::return_home()
{
    rect() = home().rect();
    laser_count() = 0;
}

inline
void Alien::formation_velocity()
{
    dx() = home().dx();
    dy() = 0;
}

inline
void Alien::sin_velocity()
{
    // // amplitude: determines how far the alien moves from side to side
    // //            (or up and down in this case) from the center of the screen.
    // // frequency: controls how many oscillations occur over a given time period.
    // //            Higher values result in more frequent oscillations. Frequency is 1 / frequency divisor

    int amplitude = SPEED;
    int frequency_divisor = 40;
    dx() = amplitude * sin(y() / frequency_divisor);
    dy() = SPEED - 1;
}

inline
void Alien::drop_velocity()
{
    dx() = 0;
    dy() = SPEED;
}

// inline
// void Alien::target_velocity()
// {   
//     int delta_x = target_pos().get_x() - x();
//     int delta_y = target_pos().get_y() - y();

//     double distance = sqrt(delta_x * delta_x + delta_y * delta_y);

//     double unit_x = delta_x / distance;
//     double unit_y = delta_y / distance;
    
//     dx() = unit_x * SPEED;
//     dy() = abs(unit_y * SPEED); 
    
// }

inline
void Alien::drift_velocity()
{
    velocity() = {home().dx(), SPEED - 3};
}

inline
void Alien::spawn_velocity()
{
    home().dx() = 0;
    velocity() = {home().dx(), SPEED - 3};
}

inline
void Alien::find_collisions(std::vector < Laser > & lasers, Player & player)
{
    //====================
    // test for collision
    //====================
    int lim = lasers.size();
    for (int i = 0; i < lim; ++i)
    {
        if (lasers[i].player() && lasers[i].is_alive()
            && collides(lasers[i]) && is_alive())
        {
            //explosion_sound().play();
            lasers[i].kill();
            kill();
            d_aggression() *= 2;
            // every time I spawn a new fleet,
            // I should increase the
            // attack rate by a certain value
            player.score() += points();
            // std::cout << player.score() << std::endl;
            // std::cout << attack_rate() << std::endl;
            break;
        }
    }
}

inline
void Alien::fire_laser(std::vector < Laser > & lasers)
{
    //===============================================
    // fire ALIEN_LASER_COUNT lasers straight down
    //===============================================
    if (laser_count() < ALIEN_LASER_COUNT)
    {
        //================
        // fire laser
        //================
        int lim = lasers.size();
        if (attack_delay() == 0)
        {
            // search for laser that isn't alive,
            // set it to alive then fire that one.
            for (int i = 0; i < lim; ++i)
            {
                if (!lasers[i].is_alive())
                {
                    lasers[i].alien_fire(rect());
                    fired() = true;
                    ++laser_count();
                    break;
                }
            }
        }
        if (fired())
        {
            ++attack_delay();
            if (attack_delay() == ALIEN_ATTACK_DELAY)
            {
                attack_delay() = 0;
                fired() = false;
            }
        }
    }
}

inline 
void Alien::update(std::vector < Laser > & lasers, const bool can_attack, Player & player)
{
    if (!is_alive())
        return;
    
    if (in_formation_mode())
    {
        formation_velocity();
        y() = home().y();

        if (can_attack)
        {
            switch (rand() % attack_rate() - d_aggression())
            {
                case SIN:
                    state() = SIN;
                    break;
                case DROP:
                    state() = DROP;
                    break;
                case IM_A_FIRIN_MY_LASER:
                    state() = IM_A_FIRIN_MY_LASER;
                    break;
                // case TARGET:
                //     state() = TARGET;
                //     target_pos().get_x() = player.x();
                //     target_pos().get_y() = player.y();
                //     break;
                default:
                    break;
            }
        }
    }
    else if (state() == SIN)
    {
        sin_velocity();
        fire_laser(lasers);
    }
    else if (state() == DROP)
    {
        drop_velocity();
        fire_laser(lasers);
    }
    else if (state() == IM_A_FIRIN_MY_LASER)
    {
        formation_velocity();
        y() = home().y();
        
        fire_laser(lasers);
        
        if (laser_count() == ALIEN_LASER_COUNT)
        {
            state() = FORMATION;
            laser_count() = 0;
        }
    }
    else if (in_drift_mode())
    {
        drift_velocity();
        x() = home().x();
                   
        if (is_home()) // go back to formation mode
        {
            state() = FORMATION;
            return_home();
        }
    }
    else if (in_spawning_mode())
    {
        place(spawn_x(), spawn_y());
        home().x() = spawn_x();
        home().y() = spawn_y() + SPAWN_OFFSET;
        spawn_velocity();
        state() = SPAWNED;
    }
    else if (in_spawned_mode())
    {
        spawn_velocity();      

        if (is_home())
        {
            state() = FORMATION;
            home().dx() = SPEED;
            //std::cout << "state is " << state() << std::endl;
            return_home();
            x() += home().dx();
        }
    }

    if (top_hit_bottom())
    {
        state() = DRIFT;
        laser_count() = 0;
        // place(home().x(), 0);
        place(home().x(), spawn_y());
    }
}

#endif
