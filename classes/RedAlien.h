#ifndef REDALIEN_H
#define REDALIEN_H

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

class RedAlien: public Alien
{
  public:
    //================== ...structors ====================//
    RedAlien(Surface & surface, Rect rect = image().getRect(), int dx = SPEED, int dy = 0, bool is_alive = false,
             int state = 0, int attack_delay = 0, int points = 100)
        : Alien(surface, rect, dx, dy, is_alive, REDS, state, attack_delay, points)
    {}
    ~RedAlien() {}
    //====================================================//
    
    //================ getters and setters ================//
    //virtual int & id() { return id_; }
    //virtual int id() const { return id_; }
    Alien *& mother_ship() { return mother_ship_; }
    Alien * mother_ship() const { return mother_ship_; }
    static Image & image() { return image_; }
    //=====================================================//

    //====================== methods ======================//
    //void build();
    // void move(); // inherited
    // void kill(); // inherited
    void draw();
    void update(std::vector < Laser > &, const bool, Player &);
    //void update();
    //====================================================//
    
  private:
    Alien * mother_ship_;
    
    static Image image_;
};

inline
void RedAlien::draw()
{
    surface().put_image(image(), rect());
}

inline 
void RedAlien::update(std::vector < Laser > & lasers, const bool can_attack, Player & player)
{
    if (!is_alive())
        return;
    
    if (in_formation_mode())
    {
        formation_velocity();
        y() = home().y();

        if ((can_attack && !mother_ship()->is_alive()))
        {
            switch (rand() % attack_rate() - d_aggression())
            {
                case SIN:
                    state() = SIN;
                    break;
                case DROP:
                    state() = DROP;
                    break;
                // case TARGET:
                //     state() = TARGET;
                //     target_pos().get_x() = player.x();
                //     target_pos().get_y() = player.y();
                //     target_velocity();
                //     break;
                case ARC:
                    state() = ARC;
                    theta() = 0;
                    dir() = (x() < player.x() ? 1 : -1);
                    break;
                default:
                    break;
            }
        }
        else if (mother_ship()->is_alive() && mother_ship()->in_attack_mode())
        {
            state() = mother_ship()->state();
            theta() = 0;
        }
    }
    else if (state() == SIN)
    {
        if (mother_ship()->is_alive() && mother_ship()->state() == state())
        {
            velocity() = mother_ship()->velocity();
        }
        else
        {
            sin_velocity();
        }
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
    else if (state() == DROP)
    {
        if (mother_ship()->is_alive() && mother_ship()->state() == state())
        {
            velocity() = mother_ship()->velocity();
        }
        else
        {
            drop_velocity();
        }
        fire_laser(lasers);
    }
    else if (state() == ARC)
    {
        if (mother_ship()->is_alive() && mother_ship()->state() == state())
        {
            velocity() = mother_ship()->velocity();
        }
        else
        {
            if (theta() < PI / 2)
            {
                arc_velocity();
            }
            else
            {
                laser_count() = ALIEN_LASER_COUNT;
                state() = DROP;
            }
        }
    }
    else if (in_drift_mode())
    {
        drift_velocity();
        //spawn_velocity();
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
            return_home();
            x() += home().dx();
        }
    }

    if (top_hit_bottom())
    {
        state() = DRIFT;
        laser_count() = 0;
        place(home().x(), spawn_y());
    }
}

#endif
