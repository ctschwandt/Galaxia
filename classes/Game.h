#ifndef GAME_H
#define GAME_H

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
#include "Explosion.h"

enum GameState
{
    MENU,
    PLAY,
    HIGHSCORE,
    EXIT,
    RULES,
    GAMEOVER
};

class Game
{
public:
    //================== ...structors ====================//
    // Game();
    // ~Game();
   
    //====================================================//
    
    //================ getters and setters ================//
    int & state() { return state_; }
    int state() const { return state_; }
    std::vector < Laser * > & lasers() { return lasers_; }
    std::vector < Laser * > lasers() const { return lasers_; }
    std::vector < Explosion * > & explosions() { return explosions_; }
    std::vector < Explosion * > explosions() const { return explosions_; }
    std::vector < Alien * > & aliens() { return aliens_; }
    std::vector < Alien * > aliens() const { return aliens_; }
    Player *& player() { return player_; }
    Player * player() const { return player_; }
    static Music & gameplay_music() { return gameplay_music_; }
    static Music & menu_music() { return menu_music_; }
    //=====================================================//

    //====================== methods ======================//
    void build(std::vector < Laser > *, std::vector < Explosion > *,
               std::vector < Alien * > *, Player *);
    void draw_explosions();
    void play_gameplay_music();
    void play_menu_music();
    void find_collisions();
    Explosion * find_dead_explosion();
    void update();
    //=====================================================//
    
private:
    int state_;

    static std::vector < Laser * > lasers_;
    static std::vector < Explosion * > explosions_;
    static std::vector < Alien * > aliens_;
    static Player * player_;

    static Music gameplay_music_;
    static Music menu_music_;
};

inline
void Game::build(std::vector < Laser > * a_lasers,
                 std::vector < Explosion > * a_explosions,
                 std::vector < Alien * > * a_aliens, Player * a_player)
{
    lasers().clear();
    explosions().clear();
    aliens().clear();
    
    int lim = a_lasers->size();
    for (int i = 0; i < lim; ++i)
    {
        lasers().push_back(&(*a_lasers)[i]);
    }
    lim = a_explosions->size();
    for (int i = 0; i < lim; ++i)
    {
        explosions().push_back(&(*a_explosions)[i]);
    }
    lim = a_aliens->size();
    for (int i = 0; i < lim; ++i)
    {
        aliens().push_back((*a_aliens)[i]);
    }
    player() = a_player;
}

inline
void Game::draw_explosions()
{
    int lim = explosions().size();
    for (int i = 0; i < lim; ++i)
    {
        explosions()[i]->draw();
    }
}

inline
void Game::play_gameplay_music()
{
    gameplay_music().play();
}

inline
void Game::play_menu_music()
{
    menu_music().play();
}

inline
Explosion * Game::find_dead_explosion()
{
    int lim = explosions().size();
    for (int i = 0; i < lim; ++i)
    {
        if (!explosions()[i]->is_alive())
        {
            return explosions()[i];
        }
    }

    std::cout << "throwing null" << std::endl;
    return nullptr;
}

inline
void Game::find_collisions()
{
    int laser_lim = lasers().size();
    int explosion_lim = explosions().size();
    int alien_lim = aliens().size();
    
    //================================================
    // test lasers for collision with alien or player
    //================================================
    for (int i = 0; i < laser_lim; ++i)
    {
        if (lasers()[i]->is_alive())
        {
            if (!lasers()[i]->player())
            {            
                if (lasers()[i]->collides(*player()) && player()->iv_frames() == 0 && player()->is_alive())
                {
                    lasers()[i]->kill();
                    Explosion * e = find_dead_explosion();
                    e->explode(player()->x(), player()->y());
                    ++player()->iv_frames();
                    player()->take_damage();
                }
            }
            else // if player laser
            {
                for (int j = 0; j < alien_lim; ++j)
                {
                    if (aliens()[j]->collides((*lasers()[i])) && aliens()[j]->is_alive() == true)
                    {
                        Explosion * e = find_dead_explosion();
                        e->explode(aliens()[j]->x(), aliens()[j]->y());
                        lasers()[i]->kill();
                        aliens()[j]->kill();
                        player()->score() += aliens()[j]->points();
                    }
                }
            }
        }
    }

    //===================================
    // see if alien collided with player
    //===================================
    for (int i = 0; i < alien_lim; ++i)
    {
        if (aliens()[i]->is_alive() && aliens()[i]->collides(*player()) && player()->iv_frames() == 0 && player()->is_alive())
        {
            Explosion * e = find_dead_explosion();
            e->explode(aliens()[i]->x(), aliens()[i]->y());
            e = find_dead_explosion();
            e->explode(player()->x(), player()->y());
            aliens()[i]->kill();
            player()->take_damage();
        }
    }
}

inline
void Game::update()
{
    find_collisions();
    int lim = explosions().size();
    for (int i = 0; i < lim; ++i)
    {
        explosions()[i]->Explosion::update();
    }
}

#endif
