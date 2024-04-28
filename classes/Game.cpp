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
#include "Game.h"

Music Game::gameplay_music_("sounds/moonlight_sonata.wav");
Music Game::menu_music_("sounds/clair_de_lune.wav");

std::vector< Laser * > Game::lasers_ = {};
std::vector< Explosion * > Game::explosions_ = {};
std::vector< Alien * > Game::aliens_ = {};
Player * Game::player_ = {};
