#ifndef YELLOWALIEN_H
#define YELLOWALIEN_H

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

class YellowAlien: public Alien
{
  public:
    //================== ...structors ====================//
    YellowAlien(Surface & surface, Rect rect = image().getRect(), int dx = SPEED, int dy = 0, bool is_alive = false,
                int state = 0, int attack_delay = 0, int points = 200)
        : Alien(surface, rect, dx, dy, is_alive, YELLOWS, state, attack_delay, points)
    {}
    virtual ~YellowAlien() {}
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

inline
void YellowAlien::draw()
{
    surface().put_image(image(), rect());
}

#endif
