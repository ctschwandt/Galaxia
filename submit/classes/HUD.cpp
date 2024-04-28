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
#include "HUD.h"
#include "Star.h"

Font HUD::font0_("fonts/Dune_Rise.ttf", 30);

Image HUD::name_(font0_.render("Cole Schwandt 2024", CYAN));
Image HUD::ship_("images/galaxian/GalaxianGalaxip.gif");
Image HUD::lives_(font0_.render("LIVES:", {255, 249, 249}));
Image HUD::score_(font0_.render("0", CYAN));
//Image HUD::highscore_();
