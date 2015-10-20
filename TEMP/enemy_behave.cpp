#include "enemy.h"
#include "bullets.h"
#include <cmath>



void Enemies::behave(void){ // AND HANDLE
///BEHAVE
Enemy *ienemy;

for( ienemy = FirstEnemy->next; ienemy != LastEnemy; ienemy = ienemy->next )
{
    if( ienemy->behavior == 1 )
    {
        //Miscare

        if( ienemy->timer + 20 < SDL_GetTicks() )
        {
            ienemy->timer = SDL_GetTicks();
            //ienemy->x + 1;
            ienemy->y += 4;
        }
        /**/

        //Shoot
        /*
        if( ienemy->timer2 + 1000 < SDL_GetTicks() )
        {
            //Reseteaza timer-ul
            ienemy->timer2 = SDL_GetTicks();
            //Trage un glont

            GAME_BULLETS.shoot_unghi( FACTION_ENEMY,3,ienemy->x + ienemy->rCenter.x + ienemy->rCenter.w/2 - 10 ,
                                            ienemy->y + ienemy->rCenter.y,0 );
        }
        */


    }
    else
    if( ienemy->behavior == 2 )
    {
        //Miscare

        if( ienemy->timer + 20 < SDL_GetTicks() )
        {
            ienemy->timer = SDL_GetTicks();
            //ienemy->x + 1;
            ienemy->y += 3;
        }

        //Shoot

        if( ienemy->phase == 0 && ienemy->timer2 + 100 < SDL_GetTicks() )
        {
            //Reseteaza timer-ul
            ienemy->timer2 = SDL_GetTicks();
            //Trage un glont

            GAME_BULLETS.shoot_unghi( FACTION_ENEMY,3,ienemy->x + ienemy->rCenter.x + ienemy->rCenter.w/2 - 10 ,
                                            ienemy->y + ienemy->rCenter.y,0 );

            GAME_BULLETS.shoot_unghi( FACTION_ENEMY,1,ienemy->x + ienemy->rCenter.x + ienemy->rCenter.w/2 - 10 ,
                                            ienemy->y + ienemy->rCenter.y,-pi/6 );
            GAME_BULLETS.shoot_unghi( FACTION_ENEMY,1,ienemy->x + ienemy->rCenter.x + ienemy->rCenter.w/2 - 10 ,
                                            ienemy->y + ienemy->rCenter.y, pi/6 );
        }

        if( ienemy->timer3 + 300 < SDL_GetTicks() )
        {
            //Reseteaza timer-ul
            ienemy->timer3 = SDL_GetTicks();
            //Schimba Phase
            ienemy->phase = !ienemy->phase;

        }



    }
    else
    if( ienemy->behavior == 3 )
    {
        //Miscare

        if( ienemy->timer + 20 < SDL_GetTicks() )
        {
            ienemy->timer = SDL_GetTicks();
            //ienemy->x + 1;
            ienemy->y += 3;
        }

        //Shoot


        if( ienemy->timer3 + 750 < SDL_GetTicks() )
        {
            //Fire
            GAME_BULLETS.shoot_unghi( FACTION_ENEMY,3,ienemy->x + ienemy->rCenter.x + ienemy->rCenter.w/2 - 10 ,
                                            ienemy->y + ienemy->rCenter.y,0 );

            //Reseteaza timer-ul
            ienemy->timer3 = SDL_GetTicks();
            //Schimba Phase
            ienemy->phase = !ienemy->phase;

        }

    }




}

///HANDLE
if( SDL_GetTicks() - timeAnimFlame >= 100  )
{
    bCFlame = !bCFlame;
    timeAnimFlame = SDL_GetTicks();
}

}
