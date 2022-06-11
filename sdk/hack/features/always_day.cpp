//
// Created by pepej on 11.06.2022.
//

#include "always_day.h"
#include "../../game/classes/game.h"

always_day g_always_day;

void always_day::enable() {
    entity *local_player = g_game.get_local();
    if (!g_utils.valid_ptr(local_player))
        return;
    world* world = g_game.get_world( );
    *reinterpret_cast< float* >( world + 0x28A8 ) = 2.0f;

}

