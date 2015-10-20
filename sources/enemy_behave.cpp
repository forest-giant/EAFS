#include "enemy.h"
#include "bullets.h"
#include "Player.h"
#include "effects.h"
//#include "Console.h"
#include <cmath>



void Enemies::behave(void){ // AND HANDLE AND COLLISION
///BEHAVE
Enemy *ienemy;

#define playerx PLAYER.getBody()->x + PLAYER.getBody()->w/2
#define playery PLAYER.getBody()->y + PLAYER.getBody()->h/2

#define px PLAYER.getBody()->x + PLAYER.getCenter()->x
#define py PLAYER.getBody()->y + PLAYER.getCenter()->y
#define pw PLAYER.getCenter()->w
#define ph PLAYER.getCenter()->h

#define ex ienemy->x + ienemy->rCenter.x
#define ey ienemy->y + ienemy->rCenter.y
#define ew ienemy->rCenter.w
#define eh ienemy->rCenter.h

#define enemyx ienemy->x + ienemy->w/2
#define enemyy ienemy->y + ienemy->h/2

#define move_after 10

for( ienemy = FirstEnemy->next; ienemy != LastEnemy; ienemy = ienemy->next )
if( ienemy->dying == false )
{



    #define f1(x) 100*sin(x/100)

    ///------ STAGE I ------
    ///------ PART I  -----

    ///------- DOWN ---
    if( ienemy->behavior      == 1 )
    {
        //Miscare
        if( ienemy->timer + 20 < SDL_GetTicks() )
        {
            ienemy->timer = SDL_GetTicks();
            ienemy->y += 4;//2
        }

    }
    /// ------ OBLIC-stanga -----
    else if( ienemy->behavior == 2 )
    {
        #define dist_2 0
        #define speed_2_x 3
        #define speed_2_y 2

        if( ienemy->timer + 16 < SDL_GetTicks() )
        {
            ienemy->y += speed_2_y;

            ienemy->x -= speed_2_x; //(double)dist_2/SCREEN_HEIGHT*speed_2_x;


            ienemy->timer = SDL_GetTicks();
        }
    }
    /// ------ OBLIC-dreapta -----
    else if( ienemy->behavior == 3 )
    {
        #define dist_3 2000
        #define speed_3 1

        if( ienemy->timer + 16 < SDL_GetTicks() )
        {
            ienemy->y += speed_3;

            ienemy->x += (double)dist_3/SCREEN_HEIGHT*speed_3;

            ienemy->timer = SDL_GetTicks();
        }
    }



    ///------ STAGE I ------
    ///------ PART II  -----
    else if( ienemy->behavior == 4 )
    {
        //Shoot
        if( ienemy->timer2 + 1000 < SDL_GetTicks() )
        {
            GAME_BULLETS.shoot_unghi( FACTION_ENEMY,1,ienemy->x + ienemy->w/2 - 5,
                                      ienemy->y + ienemy->h,0 );
            ienemy->timer2 = SDL_GetTicks();
        }

        //Miscare
        if( ienemy->timer + 20 < SDL_GetTicks() )
        {
            ienemy->timer = SDL_GetTicks();
            ienemy->y += 2;
        }
    }

    else if( ienemy->behavior == 5 )
    {
        //Oblic
        #define  dist_5 -400
        if( ienemy->timer + 20 < SDL_GetTicks() )
        {
            ienemy->y += 4;

            ienemy->x += (double)dist_5/SCREEN_HEIGHT*4;

            ienemy->timer = SDL_GetTicks();
        }
        //Shoot
        if( ienemy->timer2 + 1000 < SDL_GetTicks() )
        {
            GAME_BULLETS.shoot_unghi( FACTION_ENEMY,1,ienemy->x + ienemy->w/2 - 5,
                                      ienemy->y + ienemy->h,0 );
            ienemy->timer2 = SDL_GetTicks();
        }

    }
    else if( ienemy->behavior == 6 )
    {
        //Oblic
        #define  dist_6 400
        if( ienemy->timer + 20 < SDL_GetTicks() )
        {
            ienemy->y += 4;

            ienemy->x += (double)dist_6/SCREEN_HEIGHT*4;

            ienemy->timer = SDL_GetTicks();
        }
        //Shoot
        if( ienemy->timer2 + 1000 < SDL_GetTicks() )
        {
            GAME_BULLETS.shoot_unghi( FACTION_ENEMY,1,ienemy->x + ienemy->w/2 - 5,
                                      ienemy->y + ienemy->h,0 );
            ienemy->timer2 = SDL_GetTicks();
        }

    }
    else if( ienemy->behavior == 7 )
    {

        //Shoot
        if( ienemy->timer2 + 300 < SDL_GetTicks() )
        {
            GAME_BULLETS.shoot_unghi( FACTION_ENEMY,2,ienemy->x + ienemy->w/2 - 5,
                                      ienemy->y + ienemy->h,0 );
            ienemy->timer2 = SDL_GetTicks();
        }

        //Panou de contr
        #define ampy 100
        #define incx 2
        #define incy 2

        if( SDL_GetTicks() - ienemy->timer > 10 )
        {

        ienemy->y += incy;

        ///Miscare la Stanga
        if( ( (int)ienemy->y/ampy)%2 == 0 )
        {
            ienemy->x -= incx;
        }
        else
        ///Miscare la Dreapta
        if( ((int)ienemy->y/ampy)%2 == 1 )
        {
            ienemy->x += incx;
        }

        ienemy->timer = SDL_GetTicks();

        }

    }
    else if( ienemy->behavior == 8 )
    {

        //Shoot
        if( ienemy->timer2 + 250 < SDL_GetTicks() )
        {
            GAME_BULLETS.shoot_unghi( FACTION_ENEMY,2,ienemy->x + ienemy->w/2 - 5,
                                      ienemy->y + ienemy->h,0 );
            ienemy->timer2 = SDL_GetTicks();
        }

        //Move
         if( enemyx < playerx)
        {
            if( SDL_GetTicks() - ienemy->timer > 10 )
            {
                  ienemy->y+=1;
                   ienemy->x++;

                ienemy->timer = SDL_GetTicks();
            }
        }
        else
        if( enemyx > playerx)
        {
            if( SDL_GetTicks() - ienemy->timer > 10 )
            {
                  ienemy->y+=1;
                   ienemy->x--;

                ienemy->timer = SDL_GetTicks();
            }
       }
        else
        if( enemyx == playerx)
        {
            if( SDL_GetTicks() - ienemy->timer > 10 )
            {
                ienemy->y+=1;
                ienemy->timer = SDL_GetTicks();
            }
        }

    }







    ///-----  -TEMPLATE-  --


        ///------- DOWN ---
    if( ienemy->behavior == 900 )
    {
        //Miscare
        if( ienemy->timer + 20 < SDL_GetTicks() )
        {
            ienemy->timer = SDL_GetTicks();
            ienemy->y += 5;
        }

    }
    /// ------ OBLIC -----
    else if( ienemy->behavior == 901 )
    {
        #define  dist_n -300
        if( ienemy->timer + 20 < SDL_GetTicks() )
        {
            ienemy->y += 4;

            ienemy->x += (double)dist_n/SCREEN_HEIGHT*4;

            ienemy->timer = SDL_GetTicks();
        }
    }


    /// ------ ZIG-ZAG -------
    else if( ienemy->behavior == 901 )
    {
        //Panou de contr
        #define ampy 100
        #define incx 2
        #define incy 2

        if( SDL_GetTicks() - ienemy->timer > 10 )
        {

        ienemy->y += incy;

        ///Miscare la Stanga
        if( ( (int)ienemy->y/ampy)%2 == 0 )
        {
            ienemy->x -= incx;
        }
        else
        ///Miscare la Dreapta
        if( ((int)ienemy->y/ampy)%2 == 1 )
        {
            ienemy->x += incx;
        }

        ienemy->timer = SDL_GetTicks();


        }

    }
    ///------- DOWN: Follow Player ------
    else if( ienemy->behavior == 902 )
    {

         if( enemyx < playerx)
        {
            if( SDL_GetTicks() - ienemy->timer > 10 )
            {
                  ienemy->y+=1;
                   ienemy->x++;

                ienemy->timer = SDL_GetTicks();
            }
        }
        else
        if( enemyx > playerx)
        {
            if( SDL_GetTicks() - ienemy->timer > 10 )
            {
                  ienemy->y+=1;
                   ienemy->x--;

                ienemy->timer = SDL_GetTicks();
            }
       }
        else
        if( enemyx == playerx)
        {
            if( SDL_GetTicks() - ienemy->timer > 10 )
            {
                ienemy->y+=1;
                ienemy->timer = SDL_GetTicks();
            }
        }

    }
    ///------- SNAKE(dreapta->stanga) ----- BUGGY
    else if( ienemy->behavior == 904 ){

     /**
     -phase 1/0  SE MISCA IN JOS
     -phase 2  merge dreapta
     -phase 3  merge in jos
     -phase 4  revine in poz initiala
     **/

     #define speed   5
     #define time  250

    //Handle Phase
    if( SDL_GetTicks() - ienemy->timer >= time )
    {
        ienemy->phase ++;

        if( ienemy->phase >= 5 ) ienemy->phase = 1;

        ienemy->timer = SDL_GetTicks();
    }
    //Hasnle Movement
    if( SDL_GetTicks() - ienemy->timer2 >= move_after )
    {
        if( ienemy->phase == 1 || ienemy->phase == 3 || ienemy->phase == 0 )
        {
            ienemy->y += speed;
        }
        else
        if( ienemy->phase == 2 )
        {
            ienemy->x += speed;
        }
        else
        if( ienemy->phase == 4 )
        {
            ienemy->x -= speed;
        }

        ienemy->timer2 = SDL_GetTicks();
    }



     }



///COLLISION
if( px + pw > ex && px < ex + ew && py + ph > ey && py < ey + eh && PLAYER.getInvi() == false )
{
    PLAYER.damage();
    GAME_Enemies.attack( ienemy, 500 );
}





}
//Time to DIE!
else if( ienemy->timedie + 400 < SDL_GetTicks() )
{
    ienemy->dead = true;
}

///HANDLE
if( SDL_GetTicks() - timeAnimFlame >= 100  )
{
    bCFlame = !bCFlame;
    timeAnimFlame = SDL_GetTicks();
}

if( timePhaseDie + 100 < SDL_GetTicks() )
{
    bPhaseDie = !bPhaseDie;
    timePhaseDie = SDL_GetTicks();
}

}
