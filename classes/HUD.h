#ifndef HUD_H
#define HUD_H

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

class HUD
{
  public:

     //================== ...structors ====================//
     HUD(Surface & surface)
        : surface_(surface)
    {
        box() = {0, H - BOTTOM_OFFSET, W, BOTTOM_OFFSET};
        hud_line() = {0, H - BOTTOM_OFFSET, W, 3};
        bottom_left() = lives().getRect();
        bottom_left().x = 7;
        bottom_left().y = H - 35;
        top_left().x = bottom_left().x;
        top_left().y = 19;
    } 
     //====================================================//
    
    //================ getters and setters ================//
    Surface & surface() { return surface_; }
    Surface surface() const { return surface_; }
    Rect & box() { return box_; }
    Rect box() const { return box_; }
    Rect & top_left() { return top_left_; }
    Rect top_left() const { return top_left_; }
    Rect & hud_line() { return hud_line_; }
    Rect hud_line() const { return hud_line_; }
    Rect & bottom_left() { return bottom_left_; }
    Rect bottom_left() const { return bottom_left_; }
    Rect & bottom_right() { return bottom_right_; }
    Rect bottom_right() const { return bottom_right_; }
    Rect & left_of_bottom_right() { return left_of_bottom_right_; }
    Rect left_of_bottom_right() const { return left_of_bottom_right_; }
    static Font & font0() { return font0_; }
    static Image & lives() { return lives_; }
    static Image & ship() { return ship_; }
    static Image & score() { return score_; }
    //=====================================================//

    //====================== methods ======================//
    void draw_menu();
    void draw_play(const int, const int, const int);
    // void draw_rules();
    // void draw_highscores();
    //=====================================================//
    
  private:
    Surface & surface_;

    Rect box_;
    Rect hud_line_;
    Rect top_left_;
    Rect bottom_left_;
    Rect bottom_right_;
    Rect left_of_bottom_right_;

    static Font font0_;
    
    static Image name_;
    // static Image highscore_;
    static Image lives_;
    static Image ship_;
    static Image score_;
    // game over
    
};

inline
void HUD::draw_menu()
{
    surface().put_rect(box(), BLACK);
    surface().put_rect(hud_line(), CYAN);

    // signature
    Image name = font0().render("Cole Schwandt 2024", CYAN);
    surface().put_image(name, bottom_left());
}

inline
void HUD::draw_play(const int lives_amt, const int score_amt, const int fleet_amt)
{
    surface().put_rect(box(), BLACK);    
    surface().put_rect(hud_line(), CYAN);
    surface().put_image(lives(), bottom_left());

    // fleet text
    Image fleet = font0().render("FLEET:", {255, 249, 249});
    surface().put_image(fleet, top_left()); // dif font size?

    // fleet count
    int digits = (0 != fleet_amt ? 0 : 1);
    int t = fleet_amt;
    while (t != 0)
    {
        t /= 10;
        ++digits;
    }
    
    char fleet_chars[digits + 1]; 
    for (int i = 0; i < digits; ++i)
    {
        fleet_chars[digits - 1 - i] = '0' + char(fleet_amt / int(pow(10, i)) % 10);
    }
    fleet_chars[digits] = '\0';

    Image fleet_count_image = font0().render(fleet_chars, CYAN);
    Rect fleet_rect = fleet_count_image.getRect();
    fleet_rect.x = top_left().w + 178;
    fleet_rect.y = top_left().y;    
    surface().put_image(fleet_count_image, fleet_rect);  

    // ships
    Rect ship_rect = ship().getRect();
    ship_rect.y = bottom_left().y - 4;
    if (lives_amt >= 1)
    {
        ship_rect.x = bottom_left().x + bottom_left().w + 5 + ship_rect.w;
        surface().put_image(ship(), ship_rect);
    }
    if (lives_amt >= 2)
    {
        ship_rect.x += (5 + ship_rect.w);
        surface().put_image(ship(), ship_rect);
    }
    if (lives_amt == 3)
    {
        ship_rect.x += (5 + ship_rect.w);
        surface().put_image(ship(), ship_rect);
    }
    
    // score count
    digits = (0 != score_amt ? 0 : 1);
    t = score_amt;
    while (t != 0)
    {
        t /= 10;
        ++digits;
    }
    
    char score_chars[digits + 1]; 
    for (int i = 0; i < digits; ++i)
    {
        score_chars[digits - 1 - i] = '0' + char(score_amt / int(pow(10, i)) % 10);
    }
    score_chars[digits] = '\0';

    Image score_image = font0().render(score_chars, CYAN);
    Rect score_rect = score_image.getRect();
    score_rect.x = W - score_rect.w;
    score_rect.y = bottom_left().y;    
    surface().put_image(score_image, score_rect);

    // score text
    Image score_text_image = font0().render("SCORE:", {255, 249, 249});
    Rect score_text_rect = score_text_image.getRect();
    score_text_rect.x = score_rect.x - score_text_rect.w - 5;
    score_text_rect.y = bottom_left().y;
    surface().put_image(score_text_image, score_text_rect);
}


#endif
