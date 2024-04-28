#ifndef BLUEALIEN_H
#define BLUEALIEN_H

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"

#include "vec2.h"
#include "GameObject.h"
#include "Alien.h"

class BlueAlien: public Alien
{
public:
     //================== ...structors ====================//
    BlueAlien(Surface & surface, Rect rect = image().getRect(), int dx = SPEED, int dy = 0, bool is_alive = false,
              int state = 0, int attack_delay = 0, int points = 60)
        : Alien(surface, rect, dx, dy, is_alive, BLUES, state, attack_delay, points)
    {}
     //====================================================//
    
    //================ getters and setters ================//
    //virtual int & id() { return id_; }
    //virtual int id() const { return id_; }
    static Image & image() { return image_; }
    //=====================================================//

    //====================== methods ======================//
    void build();
    // void move(); // inherited
    // void kill(); // inherited
    void draw();
    void update();
    //=====================================================//

private:

    static Image image_;
};

inline
void BlueAlien::build()
{
    is_alive() = true;
    x() = W / 4; y() = H / 4;

    home() = GameObject(*this);
}

inline
void BlueAlien::draw()
{
    surface().put_image(image(), rect());
}

#endif
