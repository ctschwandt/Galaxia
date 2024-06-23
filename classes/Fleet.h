#ifndef FLEET_H
#define FLEET_H

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
#include "Alien.h"
#include "BlueAlien.h"
#include "PurpleAlien.h"
#include "RedAlien.h"
#include "Laser.h"
#include "mainFunctions.h"

class Fleet: public GameObject
{
public:
     //================== ...structors ====================//
    Fleet(Surface & surface, Rect rect = {0, 0, 0, 0},
          int dx = SPEED, int dy = 0, bool is_alive = false)
        : GameObject(surface),
          blue_can_attack_(true), purple_can_attack_(false), red_can_attack_(false), yellow_can_attack_(false)
    {
        count() = 1;
    }
    ~Fleet() {}
     //====================================================//

    //================ getters and setters ================//
    std::vector < Alien * > & aliens() { return aliens_; }
    std::vector < Alien * > aliens() const { return aliens_; }
    bool & blue_can_attack() { return blue_can_attack_; }
    bool blue_can_attack() const { return blue_can_attack_; }
    bool & purple_can_attack() { return purple_can_attack_; }
    bool purple_can_attack() const { return purple_can_attack_; }
    bool & red_can_attack() { return red_can_attack_; }
    bool red_can_attack() const { return red_can_attack_; }
    bool & yellow_can_attack() { return yellow_can_attack_; }
    bool yellow_can_attack() const { return yellow_can_attack_; }
    Alien *& left_most() { return left_most_; }
    Alien * left_most() const { return left_most_; }
    Alien *& right_most() { return right_most_; }
    Alien * right_most() const { return right_most_; }
    int & count() { return count_; }
    int count() const {return count_;}
    //=====================================================//

    //====================== methods ======================//
    void build(std::vector < BlueAlien > & blues,
               std::vector < PurpleAlien > & purples,
               std::vector < RedAlien > & reds,
               std::vector < YellowAlien > & yellows);
    void draw_aliens();
    void draw_homes();
    bool all_dead();
    void revive_all();
    bool determine_parameter(const int);
    void update_can_attack();
    void update_left_most_and_right_most();
    void update_velocity();
    void update_collisions(std::vector < Laser > &, Player &);
    void update(std::vector < Laser > &, Player &);
    //=====================================================//

protected:
    static std::vector < Alien * > aliens_;

    bool blue_can_attack_;
    bool purple_can_attack_;
    bool red_can_attack_;
    bool yellow_can_attack_;
    
    static Alien * left_most_;
    static Alien * right_most_;

    int count_; 
};

inline
void Fleet::build(std::vector < BlueAlien > & blues,
                  std::vector < PurpleAlien > & purples,
                  std::vector < RedAlien > & reds,
                  std::vector < YellowAlien > & yellows)
{
    is_alive() = true;
    
    build_blues(surface(), blues);
    build_purples(surface(), purples);
    build_yellows(surface(), yellows);
    build_reds(surface(), reds, yellows);
    
    int lim = blues.size();
    for (int i = 0; i < lim; ++i)
    {
        aliens().push_back(&blues[i]);
    }
    lim = purples.size();
    for (int i = 0; i < lim; ++i)
    {
        aliens().push_back(&purples[i]);
    }
    lim = reds.size();
    for (int i = 0; i < lim; ++i)
    {
        aliens().push_back(&reds[i]);
    }
    lim = yellows.size();
    for (int i = 0; i < lim; ++i)
    {
        aliens().push_back(&yellows[i]);
    }
}

inline
void Fleet::draw_aliens()
{
    int lim = aliens().size();
    for (int i = 0; i < lim; ++i)
    {
        if(aliens()[i]->is_alive())
        {
            aliens()[i]->draw();
        }
    }
}

inline
void Fleet::draw_homes()
{
    int lim = aliens().size();
    for (int i = 0; i < lim; ++i)
    {
        if(aliens()[i]->is_alive())
        {
            aliens()[i]->surface().put_rect(aliens()[i]->home().rect(), PINK);
        }
        
    }
}

inline
bool Fleet::all_dead()
{
    int lim = aliens().size();
    for (int i = 0; i < lim; ++i)
    {
        if ((aliens()[i]->is_alive()))
        {
            return false;
        }
    }

    is_alive() = false; // spawn new fleet
    return true;
}

inline
void Fleet::revive_all()
{
    int lim = aliens().size();
    ++count();
    for (int i = 0; i < lim; ++i)
    {
        aliens()[i]->is_alive() = true;
        aliens()[i]->state() = SPAWNING;
    }
    purple_can_attack() = false;
    red_can_attack() = false;
    yellow_can_attack() = false;
}

inline
void Fleet::update_can_attack()
{
    if (yellow_can_attack())
        return;
    
    int lim = aliens().size();
    //=================================================
    // 1) if a blue alien of the top row has been killed,
    // then purples can attack
    // 2) if a purple alien has been killed,
    // then reds and yellows can attack
    //=================================================
    for (int i = 0; i < lim; ++i)
    {
        if (!(aliens()[i]->is_alive()))
        {
            if(aliens()[i]->home().y() == BLUE_BOTTOM_ROW_Y)
            {
                purple_can_attack() = true;
            }
            if(aliens()[i]->home().y() == PURPLE_BOTTOM_ROW_Y)
            {
                red_can_attack() = true;
                yellow_can_attack() = true;
            }
        }
    }
}

inline
void Fleet::update_left_most_and_right_most()
{
    //=========================================================
    // if there are no alive aliens, set_left_most_ to nullptr
    //=========================================================
    if (all_dead())
    {
        left_most() = nullptr;
        right_most() = nullptr;
        return;
    }

    //=============================================
    // iterate through the aliens to find  
    // the one with the lowest x-coordinate (left)
    // and greatest x-coordinate (right)
    //=============================================
    int i = 0;
    while (1)
    {
        if (aliens()[i]->is_alive())
        {
            break;
        }
        ++i;
    }
    if (left_most() == nullptr || right_most() == nullptr)
    {
        left_most() = aliens()[i];
        right_most() = aliens()[i];
    }

    int lim = aliens().size();
    while (i < lim)
    {
        if (aliens()[i]->is_alive())
        {
            if (aliens()[i]->home().x() < left_most()->home().x() || !(left_most()->is_alive()))
            {
                left_most() = aliens()[i];
            }
            if (aliens()[i]->home().x() > right_most()->home().x() || !(right_most()->is_alive()))
            {
                right_most() = aliens()[i];
            }
        }
        ++i;
    }
}

inline
void Fleet::update_velocity()
{
    int lim = aliens().size();
    for (int i = 0; i < lim; ++i)
    {
        aliens()[i]->home().move();
        aliens()[i]->GameObject::move();
    }
    if (left_most()->left_hit_left() || right_most()->right_hit_right())
    {
        for (int i = 0; i < lim; ++i)
        {
            aliens()[i]->dx() = -dx();
        }
    }
    if (left_most()->home().left_hit_left() || right_most()->home().right_hit_right())
    {
        for (int i = 0; i < lim; ++i)
        {
            aliens()[i]->home().dx() = -aliens()[i]->home().dx();
        }
    }
}

inline
void Fleet::update_collisions(std::vector < Laser > & lasers, Player & player)
{  
    
    //======================================================================
    // case 1: laser touches alien  - > alien and laser die
    // case 2: alien touches player - > alien dies and player loses one life
    //======================================================================
    int lim = aliens().size();
    for (int i = 0; i < lim; ++i)
    {
        aliens()[i]->find_collisions(lasers, player);
        if (aliens()[i]->collides(player))
        {
            player.take_damage();
            aliens()[i]->kill();
            //explosion_sound().play();
            // draw explosion
        }
    }
}

inline
bool Fleet::determine_parameter(const int id)
{
    switch (id)
    {
        case BLUES:
            return blue_can_attack();
            break;
        case PURPLES:
            return purple_can_attack();
            break;
        case REDS:
            return red_can_attack();
            break;
        case YELLOWS:
            return yellow_can_attack();
            break;
        default:
            return false;
            break;
    }
}

inline
void Fleet::update(std::vector < Laser > & lasers, Player & player)
{
    update_left_most_and_right_most();

    if (left_most() != nullptr)
    {
        // int lim = aliens().size();
        // for (int i = 0; i < lim; ++i)
        // {
        //     bool parameter = determine_parameter(aliens()[i]->type());
        //     aliens()[i]->update(lasers, parameter);
        // }

        // the reverse order of the loop
        // is so yellow aliens go first
        int lim = aliens().size();
        for (int i = lim - 1; i >= 0; --i)
        {
            //std::cout << i << std::endl;
            if (aliens()[i] != nullptr)
            {
                //std::cout << aliens()[i]->type() << std::endl;
                bool parameter = determine_parameter(aliens()[i]->id());
                aliens()[i]->update(lasers, parameter, player);               
            }
            
        }

        update_velocity();
        update_can_attack();

    }
    
    if (!is_alive())
    {
        revive_all();
        is_alive() = true;
    }
}

// inline
// void Fleet::set_default_positions()
// {
//     // if blue, go through blue set function, if purple, blah blah
//     // how to do bottoms and tops? Maybe I can just not move them offscreen when they die
//     // then go through normal spawn procedure? No, I probably just need to give alien objects
//     // an x and y position to model their spawn position
// }

#endif
