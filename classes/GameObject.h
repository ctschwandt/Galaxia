#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"

#include "vec2.h"

enum ID
{
    GAMEOBJECTS,
    PLAYERS,
    ALIENS,
    BLUES,
    PURPLES,
    REDS,
    YELLOWS,
    LASERS,
    SHRAPNELS,
    EXPLOSIONS,
    STARS
};

class GameObject
{
public:
    //============ ...structors ============//
    GameObject(Surface & surface, Rect rect = {0, 0, 0, 0}, vec2i velocity = {0, 0}, bool is_alive = false,
        int id = GAMEOBJECTS)
        : surface_(surface), rect_(rect), velocity_(velocity), is_alive_(is_alive), id_(id)
    {}
    GameObject(const GameObject & other)
        : surface_(other.surface_)
    {
        if (this != &other)
        {
            rect() = other.rect();
            velocity() = other.velocity();
            is_alive() = other.is_alive();
            id() = other.id();
        }
    }
    virtual ~GameObject() {}
    //======================================//
               
    //================ getters and setters ================//
    Surface & surface() { return surface_; }
    Surface surface() const { return surface_; }
    Rect & rect() { return rect_; }
    Rect rect() const { return rect_; }
    int & x() { return rect_.x; }
    int x() const { return rect_.x; }
    int & y() { return rect_.y; }
    int y() const { return rect_.y; }
    int & w() { return rect_.w; }
    int w() const { return rect_.w; }
    int & h() { return rect_.h; }
    int h() const { return rect_.h; }
    vec2i & velocity() { return velocity_; }
    vec2i velocity() const { return velocity_; }
    int & dx() { return velocity_.get_x(); }
    int dx() const { return velocity_.get_x(); }
    int & dy() { return velocity_.get_y(); }
    int dy() const { return velocity_.get_y(); }
    bool & is_alive() { return is_alive_; }
    bool is_alive() const { return is_alive_; }
    int & id() { return id_; }
    int id() const { return id_; }
    //=====================================================//

    //====================== functions ======================//
    void move();
    void move(int d_x, int d_y = 0);
    void kill();
    bool left_hit_left();
    bool left_hit_right();
    bool right_hit_right();
    bool top_hit_top();
    bool bottom_hit_bottom();
    bool top_hit_bottom();
    bool collides(const GameObject &);
    bool is_alien();
    void place(const int, const int);
    //=====================================================//

    //===================== operators =====================//
    GameObject & operator=(const GameObject &);
    //=====================================================//
    
protected:
    Surface & surface_;
    Rect rect_;
    vec2i velocity_;
    bool is_alive_;
    int id_; // should be static

};

inline
std::ostream & operator<<(std::ostream & cout, const GameObject & game_object)
{
    cout << "<GameObject: ";
    cout << "Rect: (" << game_object.x() << ", " << game_object.y() << ", "
         << game_object.w() << ", " << game_object.h() << "), ";
    cout << "Velocity: (" << game_object.dx() << ", " << game_object.dy() << "), ";
    cout << "Is Alive: " << (game_object.is_alive() ? "true" : "false") << '>';
    return cout;
}

inline
void GameObject::move()
{
    if (is_alive())
    {
        x() += dx();
        y() += dy();
    }
}

inline
void GameObject::move(int d_x, int d_y)
{
    if (is_alive())
    {
        x() += d_x;
        y() += d_y;
    }
}

inline
void GameObject::kill()
{
    is_alive() = false;
    x() = -1;
    y() = -1;
}

inline
bool GameObject::left_hit_left()
{
    return (x() <= 0);
}

inline
bool GameObject::left_hit_right()
{
    return (x() >= W);
}

inline
bool GameObject::right_hit_right()
{
    return (x() + w() >= W);
}

inline
bool GameObject::bottom_hit_bottom()
{
    return (y() + h() >= H);
}

inline
bool GameObject::top_hit_top()
{
    return (y() <= 0);
}

inline
bool GameObject::top_hit_bottom()
{
    return (y() >= H);
}

inline
bool GameObject::collides(const GameObject & other)
{
    bool x_projection_overlap = x() <= other.x() + other.w()
        && x() + w() >= other.x();
    bool y_projection_overlap = y() <= other.y() + other.h()
        && y() + h() >= other.y();
    
    return (x_projection_overlap && y_projection_overlap);
}

inline
bool GameObject::is_alien()
{
    return (ALIENS <= id() && id() <= YELLOWS);
}

inline
void GameObject::place(const int x_, const int y_)
{
    x() = x_;
    y() = y_;
}

inline
GameObject & GameObject::operator=(const GameObject & other)
{
    if (this != &other)
    {
        surface() = other.surface();
        rect() = other.rect();
        velocity() = other.velocity();
        is_alive() = other.is_alive();
    }

    return (*this);
}

#endif
