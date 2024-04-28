#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"

#include "vec2.h"
#include "GameObject.h"
#include "Alien.h"
#include "BlueAlien.h"
#include "Laser.h"
#include "Fleet.h"

std::vector < Alien * > Fleet::aliens_({});
Alien * Fleet::left_most_(nullptr);
Alien * Fleet::right_most_(nullptr);
