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
#include "mainFunctions.h"
#include "Game.h"
#include "Explosion.h"
#include "Star.h"
#include "HUD.h"

int main()
{
    srand((unsigned int) time(NULL));
    
    //===========================
    // create objects
    //===========================
    Surface surface(W, H);
    Event event;
    Game game;
    KeyPressed keypressed = get_keypressed();
    Galaxy galaxy;
    galaxy.build(surface);
    HUD hud(surface);

    static Player player(surface);
    player.build();

    static std::vector < Laser > lasers;
    build_lasers(surface, lasers);

    static std::vector < Explosion > explosions;
    build_explosions(surface, explosions);

    static std::vector < BlueAlien > blues;
    static std::vector < PurpleAlien > purples;
    static std::vector < RedAlien > reds;
    static std::vector < YellowAlien > yellows;  // should pass into play?
    static Fleet fleet(surface);
    fleet.build(blues, purples, reds, yellows);

    game.build(&lasers, &explosions, &fleet.aliens(), &player);
    
    //==========================
    // launch game
    //==========================
    game.state() = MENU;
    while (game.state() != EXIT)
    {
        if (event.poll() && event.type() == QUIT) break;
        if (keypressed[TAB]) continue;
        
        switch (game.state())
        {
            case MENU:
                main_menu(surface, event, game, keypressed, galaxy, hud);
                break;
            case PLAY:
                play(surface, event, game, keypressed, galaxy, hud,
                     player, lasers, explosions, fleet);
                break;
            /// TO DO
            // case HIGHSCORE:
            //     break;
            // case RULES:
            //     break;
            case EXIT:
                return 0;
                break;
            case GAMEOVER:
                gameover(surface, event, game, keypressed, galaxy, hud);
                break;
            default:
                game.state() = MENU;
                break;
        }
    }

    return 0;
}
