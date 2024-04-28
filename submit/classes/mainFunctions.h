#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

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
#include "Explosion.h"
#include "Star.h"
#include "HUD.h"

class Fleet;
class Galaxy;

void main_menu(Surface & surface, Event & event, Game & game,
               KeyPressed & keypressed, Galaxy & galaxy, HUD & hud);
void gameover(Surface & surface, Event & event, Game & game,
              KeyPressed & keypressed, Galaxy & galaxy, HUD & hud);
void play(Surface & surface, Event & event, Game & game,
          KeyPressed & keypressed, Galaxy & galaxy, HUD & hud,
          Player & player, std::vector < Laser > & lasers,
          std::vector < Explosion > & explosion, Fleet & fleet);

void build_blues(Surface & surface, std::vector < BlueAlien >  & blues);
void prepare_blues(Surface & surface, std::vector < BlueAlien > & blues);
void build_purples(Surface & surface, std::vector < PurpleAlien >  & purples);
void build_reds(Surface & surface, std::vector < RedAlien > & reds, std::vector < YellowAlien > & yellows);
void build_yellows(Surface & surface, std::vector < YellowAlien > & yellows);

inline
void build_lasers(Surface & surface, std::vector < Laser > & lasers)
{
    const int laser_amt = 100;
    for (int i = 0; i < laser_amt; ++i)
    {
        lasers.push_back(Laser(surface));
    }
}

inline
void build_explosions(Surface & surface, std::vector < Explosion > & explosions)
{
    const int explosion_amt = 100;
    for (int i = 0; i < explosion_amt; ++i)
    {
        explosions.push_back(Explosion(surface));
    }
}
               
#endif
