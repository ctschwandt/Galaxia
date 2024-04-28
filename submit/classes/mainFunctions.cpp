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

void main_menu(Surface & surface, Event & event, Game & game, KeyPressed & keypressed, Galaxy & galaxy, HUD & hud)
{   
    static int r = 0;
    static int g = 0;
    static int b = 0;
    static Font font_title("fonts/Dune_Rise.ttf", 100);

    static bool trigger = false; // used to skip the intro fade

    //=============== opening fade ===================//
    // the way it works is the color starts at 0, and
    // increases by 1 every iteration until it reaches
    // its desired color value (CYAN: (0,255,255))

    if (g != 255)
    {
        for (int i = 0; i < 255; ++i)
        {
            int start = getTicks();
            if (event.poll() && event.type() == QUIT || keypressed[ESC])
            {
                game.state() = EXIT;
                return;
            }
        
            keypressed = get_keypressed();
            if ((keypressed[SPACE] || keypressed[ENTER]) && event.type() == KEYDOWN)
            {
                trigger = true;
            }

            if (event.type() == KEYUP && trigger)
            {
                g = 255;
                b = 255;
                break;
            }

            // fade in color of the title card
            ++g;
            ++b;
        
            Image title(font_title.render("GALAXIA", r, g, b));
            Rect title_rect = title.getRect();
            title_rect.y = H / 2 - (title_rect.h / 2) - 100;
            title_rect.x = W / 2 - (title_rect.w / 2);

            galaxy.update();

            //============
            // draw
            //============
            surface.lock();
            surface.fill(BLACK);

            galaxy.draw();
            hud.draw_menu();
            surface.put_image(title, title_rect);
        
            surface.unlock();
            surface.flip();

            int end = getTicks();
            int dt = RATE - end + start;
            if (dt > 0) delay(dt);
        }
    }
    //===============================================//

    game.play_menu_music(); 

    //===========
    // GALAXIA
    //===========
    Image title(font_title.render("GALAXIA", r, g, b));
    Rect title_rect = title.getRect();
    title_rect.y = H / 2 - (title_rect.h / 2) - 100;
    title_rect.x = W / 2 - (title_rect.w / 2);

    //=================
    // menu options
    //=================
    const Color options_color = {255, 249, 249};
    Font options("fonts/Dune_Rise.ttf", 30);
    Image play_w = options.render("Play", options_color);
    Image highscore_w = options.render("Highscore", options_color);
    Image exit_w = options.render("Exit", options_color);

    Image play_c = options.render("Play", CYAN);
    Image highscore_c = options.render("Highscore", CYAN);
    Image exit_c = options.render("Exit", CYAN);

    Rect play_rect = play_w.getRect();
    Rect highscore_rect = highscore_w.getRect();
    Rect exit_rect = exit_w.getRect();

    play_rect.x = W / 2 - (play_rect.w / 2);
    play_rect.y = title_rect.y + 175;
    highscore_rect.x = play_rect.x;
    highscore_rect.y = play_rect.y + 50;
    exit_rect.x = highscore_rect.x;
    exit_rect.y = highscore_rect.y + 50;

    int key_delay = 0;
    int option = PLAY;

    // //==========================
    // // alien flies along screen
    // //==========================
    // BlueAlien bluey(surface);
    // bluey.dx() = SPEED - 2;
    // bluey.dy() = 0;
    // bluey.x() = 0;
    // bluey.y() = title_rect.y - title_rect.h - 20;
    
    while (game.state() == MENU)
    {
        if (event.poll() && event.type() == QUIT)
        {
            game.state() = EXIT;
            break;
        }
        if (keypressed[TAB]) continue;
        
        int start = getTicks();

        galaxy.update();

        //=====================
        // where user goes
        // up and down menu
        //=====================
        if(key_delay < 10)        
            ++key_delay; 
        else
            key_delay = 0;

        if (key_delay == 0)
        {
            if ((keypressed[UPARROW] || keypressed[w]))
                --option;
            else if ((keypressed[DOWNARROW] || keypressed[s]))
                ++option;
        }

        if (option > EXIT)
            option = PLAY;
        else if (option < PLAY)
            option = EXIT;

        // user selects one of the options
        if (key_delay == 0 && (keypressed[SPACE] || keypressed[ENTER]))
            game.state() = option;

        // user quits out
        if (key_delay == 0 && (keypressed[ESC]))
            game.state() = EXIT;

        // //==============
        // // bluey flies
        // //==============
        // bluey.move();

        // if (bluey.left_hit_right())
        // {
        //     bluey.is_alive() = false;
        // }
        
        //============
        // draw
        //============
        surface.lock();
        surface.fill(BLACK);

        galaxy.draw();
        hud.draw_menu();
        surface.put_image(title, title_rect);
        
        switch (option) // menu options
        {
            case PLAY:
                surface.put_image(play_c, play_rect);
                surface.put_image(highscore_w, highscore_rect);
                surface.put_image(exit_w, exit_rect);
                break;
            case HIGHSCORE:
                surface.put_image(play_w, play_rect);
                surface.put_image(highscore_c, highscore_rect);
                surface.put_image(exit_w, exit_rect);
                break;
            case EXIT:
                surface.put_image(play_w, play_rect);
                surface.put_image(highscore_w, highscore_rect);
                surface.put_image(exit_c, exit_rect);
                break;
        }
        
        surface.unlock();
        surface.flip();

        int end = getTicks();
        int dt = RATE - end + start;
        if (dt > 0) delay(dt);
    }

    game.menu_music().stop();
    return;
}

void play(Surface & surface, Event & event, Game & game, KeyPressed & keypressed, Galaxy & galaxy, HUD & hud, Player & player, std::vector < Laser > & lasers, std::vector < Explosion > & explosions, Fleet & fleet)
{
    //================================
    // done for whenever the user
    // re-enters play
    //================================
    game.play_gameplay_music();
    fleet.revive_all();
    player.lives() = 3;
    player.is_alive() = true;
    fleet.count() = 0;
    player.score() = 0;

    for (int i = 0; i < lasers.size(); ++i)
    {
        lasers[i].kill();
    }
    for (int i = 0; i < explosions.size(); ++i)
    {
        explosions[i].is_alive() = false;
    }
          
    while (game.state() == PLAY)
    {
        if (event.poll() && event.type() == QUIT || keypressed[ESC])
        {
            game.state() = MENU;
            break;
        }
        if (keypressed[TAB]) continue;

        int start = getTicks();

        for (int i = 0; i < fleet.aliens().size(); ++i)
        {
            //std::cout << fleet.aliens()[0]->dx() << ' ' << fleet.aliens()[0]->dy() << std::endl;
        }
        // to have aliens target player, I should grab player position
        // then have a delay that changes where they're targeting

        //==========================================================
        // make sure player isn't firing when aliens are spawning
        //==========================================================
        if (fleet.aliens()[0]->state() == SPAWNING || fleet.aliens()[0]->state() == SPAWNED)
        {
            player.fired() = true;
            player.attack_delay() = PLAYER_ATTACK_DELAY - 1;
        }
        
        //==========================
        // update
        //=========================
        player.update(keypressed, lasers);
        fleet.update(lasers, player);
        game.update();
        galaxy.update();

        if (!player.is_alive()) // game over
        {
            // GAME OVER
            int r = 0;
            int g = 0;
            int b = 0;
            static Font font_title("fonts/Dune_Rise.ttf", 100);

            bool trigger = false; // used to skip the fade

            //=============== GAMEOVER fade ===================//
            // once fade is completed, screen turns black and it
            // goes to gameover state, then returns to menu

            for (int i = 0; i < 256; ++i)
            {
                int start_fade = getTicks();
                if (event.poll() && event.type() == QUIT)
                {
                    game.state() = EXIT;
                    return;
                }

                // prevent player from attacking
                player.attack_delay() = 1;
        
                keypressed = get_keypressed();
                if ((keypressed[ENTER]) && event.type() == KEYDOWN)
                {
                    trigger = true;
                }

                if (event.type() == KEYUP && trigger)
                {
                    g = 255;
                    b = 255;
                    break;
                }

                // fade in color of the title card
                g += 1;
                b += 1;
        
                Image title(font_title.render("GAME OVER", r, g, b));
                Rect title_rect = title.getRect();
                title_rect.y = H / 2 - (title_rect.h / 2) - 100;
                title_rect.x = W / 2 - (title_rect.w / 2);

                //============
                // draw
                //============
                surface.lock();
                surface.fill(BLACK);

                hud.draw_menu();
                fleet.draw_aliens();
                //fleet.draw_homes();
                galaxy.draw();
                hud.draw_menu();
          
                int lim = lasers.size();
                for (int i = 0; i < lim; ++i)
                {
                    lasers[i].draw();
                }

                game.draw_explosions();
                hud.draw_play(player.lives(), player.score(), fleet.count());
                surface.put_image(title, title_rect);
        
                surface.unlock();
                surface.flip();

                player.update(keypressed, lasers);
                fleet.update(lasers, player);
                game.update();
                galaxy.update();
                    
                int end_fade = getTicks();
                int dt_fade = RATE - end_fade + start_fade;
                if (dt_fade > 0) delay(dt_fade);
            }
            game.state() = GAMEOVER;
            return;
        }
        
        //=================
        // draw objects
        //=================
        surface.lock();
        surface.fill(BLACK);

        //========== ship ==========// 
        player.draw();

        //========= aliens =========//
        //fleet.draw_homes();
        fleet.draw_aliens();
        
        //========= lasers =========//
        int lim = lasers.size();
        for (int i = 0; i < lim; ++i)
        {
            lasers[i].draw();
        }

        //======= explosions =======//
        game.draw_explosions();

        //========= stars ==========//
        galaxy.draw();

        //========== hud ===========//
        hud.draw_play(player.lives(), player.score(), fleet.count());

        //==================
        // finish drawing
        //==================
        surface.unlock();
        surface.flip();

        int end = getTicks();
        int dt = RATE - end + start;
        if (dt > 0) delay(dt);
    }

    // free array of alien *?
    game.gameplay_music().stop();
    game.state() = MENU;
    
    return;
}

void gameover(Surface & surface, Event & event, Game & game, KeyPressed & keypressed, Galaxy & galaxy, HUD & hud)
{
    enum QUOTES
        {
            ICE_T,
            NUM_QUOTES
        };
    
    const Color color_text = {255, 249, 249};
    const int text_offset = 10;

    int quote = rand() % NUM_QUOTES;
    bool played = false;
    
    while (game.state() == GAMEOVER)
    {
        if (event.poll() && event.type() == QUIT)
        {
            game.state() = MENU;
            break;
        }
        if (keypressed[TAB]) continue;

        static Font font_title("fonts/Dune_Rise.ttf", 100);
        static Font font_text("fonts/FreeSansOblique.ttf", 40);
        static Font font_name("fonts/FreeSansBold.ttf", 40);
      
        Image title(font_title.render("GAME OVER", CYAN));
        Rect title_rect = title.getRect();
        title_rect.y = H / 2 - (title_rect.h / 2) - 100;
        title_rect.x = W / 2 - (title_rect.w / 2);
       
        if (event.poll() && event.type() == QUIT)
        {
            game.state() = MENU;
            break;
        }
        
        int start = getTicks();
       
        //============
        // draw
        //============
        surface.lock();
        surface.fill(BLACK);

        surface.put_image(title, title_rect);

        ///==================== TO DO =======================//
        /// Image class does not have a default constructor.
        /// Making one and initializing it with NULL leads
        /// to problems. Because these images are static,
        /// they need to be initialized with something
        /// upon their declaration
        // static bool initialized = false;
        // static Image text_images[NUM_QUOTES][3];
        // static Rect text_rects[NUM_QUOTES][3];
        // static Sound quote_sounds[NUM_QUOTES];

        // if (!initialized) {
        //     text_images[ICE_T][0] = font_text.render("\"Don't hate the player.", color_text);
        //     text_images[ICE_T][1] = font_text.render("Hate the game.\"", color_text);
        //     text_images[ICE_T][2] = font_name.render(" - Ice T.", color_text);

        //     for (int i = 0; i < 3; ++i) {
        //         text_rects[ICE_T][i] = text_images[ICE_T][i].getRect();
        //         text_rects[ICE_T][i].x = title_rect.x + 10;
        //         text_rects[ICE_T][i].y = title_rect.y + title_rect.h + i * (text_rects[ICE_T][0].h + text_offset);
        //     }

        //     quote_sounds[ICE_T] = Sound("sounds/ice_t.wav");
        //     initialized = true;
        // }
        ///=================================================//

        //=================================
        // place quote and play sound
        //=================================
        switch (quote)
        {
            case ICE_T:
                static Image ice_t0(font_text.render("\"Don't hate the player.", color_text)); // shld be an array
                static Image ice_t1(font_text.render("Hate the game.\"", color_text)); 
                static Image ice_t2(font_name.render(" - Ice T.", color_text));

                static Rect ice_r0(ice_t0.getRect()); // shld be an array
                static Rect ice_r1(ice_t1.getRect());
                static Rect ice_r2(ice_t2.getRect());

                static Sound ice_t("sounds/ice_t.wav");
                
                ice_r0.x = ice_r1.x = ice_r2.x = title_rect.x + 10;

                ice_r0.y = title_rect.y + title_rect.h + text_offset;
                ice_r1.y = ice_r0.y + ice_r0.h + text_offset;
                ice_r2.y = ice_r1.y + ice_r1.h + text_offset;

                surface.put_image(ice_t0, ice_r0);
                surface.put_image(ice_t1, ice_r1);
                surface.put_image(ice_t2, ice_r2);

                if (!played)
                {
                    ice_t.play();
                    played = true;
                }
                
                break;
        }
        
        surface.unlock();
        surface.flip();
                    
        int end = getTicks();
        int dt = RATE - end + start;
        if (dt > 0) delay(dt);

        game.gameplay_music().stop();

        delay(5000);
        game.state() = MENU;
    }
    
    game.state() = MENU;
    return;              
}

void build_blues(Surface & surface, std::vector < BlueAlien >  & blues)
{
    blues.clear();
    //============ bottom row ============//
    for (int i = 0; i < BLUE_NUM_PER_ROW; ++i)
    {
        BlueAlien blue(surface);
        blue.x() = BLUE_LEFT_W + blue.w() * i + OFFSET * i;
        blue.y() = BLUE_BOTTOM_ROW_Y;
        blue.velocity() = {SPEED, 0};
        blue.is_alive() = true;
        blue.home() = GameObject(blue);
        blue.state() = SPAWNING;
        blue.spawn_pos() = {blue.x(), blue.y() - SPAWN_OFFSET};
        blues.push_back(blue);
    }
    //============= top row ==============//
    for (int i = 0; i < BLUE_NUM_PER_ROW; ++i)
    {
        BlueAlien blue(surface);
        blue.x() = BLUE_LEFT_W + blue.w() * i + OFFSET * i;
        blue.y() = BLUE_BOTTOM_ROW_Y + blue.h();
        blue.velocity() = {SPEED, 0};
        blue.is_alive() = true;
        blue.home() = GameObject(blue);
        blue.state() = SPAWNING;
        blue.spawn_pos() = {blue.x(), blue.y() - SPAWN_OFFSET};
        blues.push_back(blue);
        //std::cout << blue.dx() << ' ' << blue.dy() << std::endl;
    }  
}

void prepare_blues(Surface & surface, std::vector < BlueAlien > & blues)
{
      //============ bottom row ============//
    for (int i = 0; i < BLUE_NUM_PER_ROW; ++i)
    {
        BlueAlien blue(surface);
        blue.x() = BLUE_LEFT_W + blue.w() * i + OFFSET * i;
        blue.y() = BLUE_BOTTOM_ROW_Y;
        blue.velocity() = {SPEED, 0};
        blue.is_alive() = true;
        blue.home() = GameObject(blue);
        blue.state() = SPAWNING;
        blue.spawn_pos() = {blue.x(), blue.y() - SPAWN_OFFSET};
        blues[i] = blue;
    }
    //============= top row ==============//
    for (int i = 0; i < BLUE_NUM_PER_ROW; ++i)
    {
        BlueAlien blue(surface);
        blue.x() = BLUE_LEFT_W + blue.w() * i + OFFSET * i;
        blue.y() = BLUE_BOTTOM_ROW_Y + blue.h();
        blue.velocity() = {SPEED, 0};
        blue.is_alive() = true;
        blue.home() = GameObject(blue);
        blue.state() = SPAWNING;
        blue.spawn_pos() = {blue.x(), blue.y() - SPAWN_OFFSET};
        blues.push_back(blue);
        //std::cout << blue.dx() << ' ' << blue.dy() << std::endl;
    }  
}

void build_purples(Surface & surface, std::vector < PurpleAlien >  & purples)
{    
    purples.clear();
    //============ bottom row ============//
    for (int i = 0; i < PURPLE_NUM_PER_ROW; ++i)
    {
        PurpleAlien purple(surface);
        purple.x() = PURPLE_LEFT_W + purple.w() * i + OFFSET * i;
        purple.y() = PURPLE_BOTTOM_ROW_Y;
        purple.velocity() = {SPEED, 0};
        purple.is_alive() = true;
        purple.home() = GameObject(purple);
        purple.state() = SPAWNING;
        purple.spawn_pos() = {purple.x(), purple.y() - SPAWN_OFFSET};
        purples.push_back(purple);
    }
}

void build_reds(Surface & surface, std::vector < RedAlien > & reds, std::vector < YellowAlien > & yellows)
{
    reds.clear();
    reds.reserve(RED_NUM_BOTTOM_ROW + RED_NUM_TOP_ROW); // crucial
    
    std::vector < RedAlien * > bottoms;
    //============ bottom row ============//
    for (int i = 0; i < RED_NUM_BOTTOM_ROW; ++i)
    {
        RedAlien red(surface);
        red.x() = RED_LEFT_W + red.w() * (i * 4) + OFFSET * i * 4;
        red.y() = RED_BOTTOM_ROW_Y;
        red.is_alive() = true;
        red.velocity() = {SPEED, 0};
        red.home() = GameObject(red);
        red.state() = SPAWNING;
        red.spawn_pos() = {red.x(), red.y() - SPAWN_OFFSET};
        reds.push_back(red);
        bottoms.push_back(&reds[i]);
    }
    std::vector < RedAlien * > tops;
    //============= top row ==============//
    for (int i = 0; i < RED_NUM_TOP_ROW; ++i)
    {
        RedAlien red(surface);
        red.x() = (RED_LEFT_W - red.w()) + red.w() * (i * 2) + OFFSET * i * 2 - OFFSET;
        red.y() = RED_BOTTOM_ROW_Y - red.h();
        red.velocity() = {SPEED, 0};
        red.is_alive() = true;
        red.home() = GameObject(red);
        red.state() = SPAWNING;
        red.spawn_pos() = {red.x(), red.y() - SPAWN_OFFSET};
        reds.push_back(red);
        tops.push_back(&reds[i + RED_NUM_BOTTOM_ROW]);
    }
    //========= set motherships ==========//
    int lim = yellows.size();
    int num_children = reds.size() / lim;
    int top_index = 0;
    int bottom_index = 0;
    for (int i = 0; i < lim; ++i)
    {
        for (int j = 0; j < num_children; ++j)
        {
            if (j % 2 == 0) // if even, top gets mothership 'i'
            {
                tops[top_index++]->mother_ship() = &yellows[i];
            }
            else // if odd, bottom gets mothership 'i'
            {
                bottoms[bottom_index++]->mother_ship() = &yellows[i];
            }
        }
    }
}

void build_yellows(Surface & surface, std::vector < YellowAlien > & yellows)
{
    yellows.clear();
    //============ bottom row ============//
    for (int i = 0; i < RED_NUM_BOTTOM_ROW; ++i)
    {
        YellowAlien yellow(surface);
        yellow.x() = YELLOW_LEFT_W + yellow.w() * (i * 4) + OFFSET * i * 4;
        yellow.y() = YELLOW_BOTTOM_ROW_Y;
        yellow.is_alive() = true;
        yellow.state() = SPAWNING;
        yellow.spawn_pos() = {yellow.x(), yellow.y() - SPAWN_OFFSET};
        yellow.home() = GameObject(yellow);
        yellows.push_back(yellow);
    }
}

