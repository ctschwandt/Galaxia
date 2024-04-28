#ifndef PURPLEALIEN_H
#define PURPLEALIEN_H

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

class PurpleAlien: public Alien
{
public:
     //================== ...structors ====================//
    PurpleAlien(Surface & surface, Rect rect = image().getRect(), int dx = SPEED, int dy = 0, bool is_alive = false,
              int state = 0, int attack_delay = 0, int points = 80)
        : Alien(surface, rect, dx, dy, is_alive, PURPLES, state, attack_delay, points)
    {}
     //====================================================//
    
    //================ getters and setters ================//
    //virtual int & id() { return id_; }
    //virtual int id() const { return id_; }
    static Image & image() { return image_; }
    //=====================================================//

    //====================== methods ======================//
    //void build();
    // void move(); // inherited
    // void kill(); // inherited
    void draw();
    //void update();
    //=====================================================//

private:

    static Image image_;
};

// inline
// void PurpleAlien::build()
// {
//     is_alive() = true;
//     x() = W / 4; y() = H / 4;

//     home() = GameObject(*this);
// }

inline
void PurpleAlien::draw()
{
    surface().put_image(image(), rect());
}

// inline
// void draw_purples(std::vector < PurpleAlien >  & purples)
// {
//     int lim = purples.size();
//     for (int i = 0; i < lim; ++i)
//     {
//         if(purples[i].is_alive())
//         {
//             purples[i].draw();
//         }
//     }
// }

// inline
// void draw_purple_homes(std::vector < PurpleAlien > & purples)
// {
//     int lim = purples.size();
//     for (int i = 0; i < lim; ++i)
//     {
//         if(purples[i].is_alive())
//         {
//             purples[i].surface().put_rect(purples[i].home().rect(), PINK);
//         }
        
//     }
// }

#endif
