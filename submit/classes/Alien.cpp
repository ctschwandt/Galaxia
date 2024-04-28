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
#include "Alien.h"
#include "Explosion.h"

int Alien::attack_rate_(ATTACK_RATE);
int Alien::d_aggression_(8);
