#ifndef STAR_H
#define STAR_H

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
#include "RedAlien.h"
#include "YellowAlien.h"
#include "Fleet.h"
#include "Game.h"

// enum STAR_TYPE
// {
//     DIM,
//     BRIGHT,
//     RED_GIANT,
//     BLUE_GIANT,
//     RED_DWARF,
//     WHITE_DWARF
// };

enum STAR_TYPE
{
    O5_V,
    B1_V,
    B3_V,
    B5_V,
    B8_V,
    A1_V,
    A3_V,
    A5_V,
    F0_V,
    F2_V,
    F5_V,
    F8_V,
    G2_V,
    G5_V,
    G8_V,
    K0_V,
    K4_V,
    K7_V,
    M2_V,
    M4_V,
    M6_V,
    NUM_STAR_TYPES
};
    
class Star: public GameObject
{
    
public:
     //================== ...structors ====================//
    Star(Surface & surface, Rect rect = {0, 0, 0, 0}, int dx = 0, int dy = 0,
         bool is_alive = false, int id = STARS, int type = -1)
        : GameObject(surface, rect, {dx, dy}, is_alive, id), type_(type)
    {}
     //====================================================//
    
    //================ getters and setters ================//
    int & type() { return type_; }
    int type() const { return type_; }
    Color & color() { return color_; }
    Color color() const { return color_; }
    //=====================================================//

    //====================== methods ======================//
    void draw();
    void set_color();
    void set_size();
    void set_speed();
    void build();
    void update();
    //=====================================================//
    
private:
    int type_;
    Color color_;
};

inline
void Star::draw()
{
    if (is_alive())
        surface().put_rect(rect(), color());
}

inline
void Star::set_color()
{
    static const Color star_colors[] =
        {
            {157, 180, 255}, // O5(V)
            {162, 185, 255}, // B1(V)
            {167, 188, 255}, // B3(V)
            {170, 191, 255}, // B5(V)
            {175, 195, 255}, // B8(V)
            {186, 204, 255}, // A1(V)
            {192, 209, 255}, // A3(V)
            {202, 216, 255}, // A5(V)
            {228, 232, 255}, // F0(V)
            {237, 238, 255}, // F2(V)
            {251, 248, 255}, // F5(V)
            {255, 249, 249}, // F8(V)
            {255, 245, 236}, // G2(V)
            {255, 244, 232}, // G5(V)
            {255, 241, 223}, // G8(V)
            {255, 235, 209}, // K0(V)
            {255, 215, 174}, // K4(V)
            {255, 198, 144}, // K7(V)
            {255, 190, 127}, // M2(V)
            {255, 187, 123}, // M4(V)
            {255, 187, 123}  // M6(V)
        };

    color() = star_colors[type()];
}

inline
void Star::set_size()
{
    static const int size[] =
        {
            4, // O5(V)
            4, // B1(V)
            3, // B3(V)
            3, // B5(V)
            3, // B8(V)
            3, // A1(V)
            2, // A3(V)
            2, // A5(V)
            2, // F0(V)
            2, // F2(V)
            2, // F5(V)
            2, // F8(V)
            2, // G2(V)
            2, // G5(V)
            2, // G8(V)
            2, // K0(V)
            2, // K4(V)
            2, // K7(V)
            1, // M2(V)
            1, // M4(V)
            1  // M6(V)
        };

    w() = size[type()];
    h() = size[type()];
}

inline
void Star::set_speed()
{
    static const int speeds[] =
        {
            1, // O5(V)
            1, // B1(V)
            1, // B3(V)
            1, // B5(V)
            1, // B8(V)
            1, // A1(V)
            1, // A3(V)
            1, // A5(V)
            1, // F0(V)
            2, // F2(V)
            2, // F5(V)
            2, // F8(V)
            2, // G2(V)
            1, // G5(V)
            2, // G8(V)
            2, // K0(V)
            3, // K4(V)
            3, // K7(V)
            3, // M2(V)
            3, // M4(V)
            4  // M6(V)
        };

    dy() = speeds[type()];
}

inline
void Star::build()
{
    is_alive() = true;
    x() = rand() % (W - 1);
    y() = rand() % (H - 51);
    type() = rand() % NUM_STAR_TYPES;
    set_color();
    set_size();
    set_speed();
}

inline
void Star::update()
{
    move();
    if (y() >= H - BOTTOM_OFFSET)
    {
        y() = 0;
    }
}

class Galaxy
{
public:
     //================== ...structors ====================//
    
     //====================================================//
    
    //================ getters and setters ================//
    std::vector < Star > & stars() { return stars_; }
    std::vector < Star > stars() const { return stars_; }
    //=====================================================//

    //====================== methods ======================//
    void draw();
    void build(Surface &);
    void update();
    //=====================================================//
    
    
private:
    std::vector < Star > stars_;
};

inline
void Galaxy::draw()
{
    int lim = stars().size();
    for (int i = 0; i < lim; ++i)
    {
        stars()[i].draw();
    }
}

inline
void Galaxy::build(Surface & surface)
{   
    const int STAR_AMOUNT = 200;
    for (int i = 0; i < STAR_AMOUNT; ++i)
    {
        Star star(surface);
        star.build();
        stars().push_back(star);
    }
}

inline
void Galaxy::update()
{
    int lim = stars().size();
    for (int i = 0; i < lim; ++i)
    {
        stars()[i].update();
    }
}

#endif

