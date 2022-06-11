//
// Created by pepej on 11.06.2022.
//

#include "remove_grass.h"
#include "../../game/classes/entity.h"
#include "../../game/classes/game.h"

remove_grass g_remove_grass;
void remove_grass::remove( )
{
    entity* lp = g_game.get_local( );
    if( !g_utils.valid_ptr( lp ) )
        return;

    world *world = g_game.get_world( );
    world->set_terrain_grid(0);
}