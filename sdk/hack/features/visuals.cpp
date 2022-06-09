//
// Created by pepej on 09.06.2022.
//

#include "visuals.h"
#include "../../game/entities.h"
#include "../../utils/vector/vector.h"
#include <algorithm>
// i dont wanna hear shit for this idc
renderer g_renderer;

visuals g_visuals;
void visuals::draw_entity_esp( )
{
    entity* local_player = g_game.get_local( );
    if( !g_utils.valid_ptr( local_player ) )
        return;

    world* world = g_game.get_world( );
    if( !g_utils.valid_ptr( world ) )
        return;

    world->get_dx_engine( )->set_fov( 20.f );

    auto watermark_string = "Pazel";
    auto watermark_size = g_renderer.smallest_pixel->CalcTextSizeA( 10.f, FLT_MAX, 0.0f, watermark_string );

    g_renderer.box<int>(0, 0, watermark_size.x + 11, 14, ImVec4( 0.23, 0.23, 0.23, 1 ), 1.f, true );
    g_renderer.rect( ImVec2( 0, 0 ), ImVec2( watermark_size.x + 10, 14 ), ImVec4( 0.45, 0.45, 0.45, 1 ) );
    g_renderer.text( ImVec2( 5, 0 ), "Pazel", ImVec4( 1, 1, 1, 1 ) );

    //please allah forgive of me for this you are our savior and only hope.
    std::vector<infected*> living = g_entities.get_living( );
    for( int i = 0; i < living.size( ); i++ )
    {
        // get player
        infected* entity = living[ i ];
        if( !entity ) continue;

        if( entity == local_player )
            continue;

        if( entity->is_dead( ) )
            continue;

        vector entity_position = entity->get_visual_state( )->get_position( );

        if( entity_position.is_zero( ) )
            continue;

        camera* camera = world->get_camera( );
        if( !g_utils.valid_ptr( camera ) )
            continue;

        vector screen_pos;
        if( !camera->screen_transform( entity_position, screen_pos ) )
            continue;

        vector zhead_pos{ };
        vector pForeHeadPos, pHeadPos, pNeckPos, pChestPos, pPelivsPos, pRhipPos, pRkneePos, pRanklePos, pRmidFootPos, pRfootPos, pLhipPos, pLkneePos, pLanklePos, pLmidFootPos, pLfootPos, pRShoulderPos, pRelbowPos, pRwristPos, pLShoulderPos, pLelbowPos, pLwristPos;

        ImColor color;
        if( entity->get_entity_type( )->get_type( )->get_object_name( )->get_str( ) == "dayzplayer" )
        {
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 49, &pForeHeadPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 24, &pHeadPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 21, &pNeckPos);

            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 20, &pChestPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 0, &pPelivsPos);

            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 9, &pRhipPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 12, &pRkneePos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 14, &pRanklePos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 15, &pRmidFootPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 16, &pRfootPos);

            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 1, &pLhipPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 4, &pLkneePos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 6, &pLanklePos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 7, &pLmidFootPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 8, &pLfootPos);

            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 94, &pRShoulderPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 97, &pRelbowPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 99, &pRwristPos);

            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 61, &pLShoulderPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 63, &pLelbowPos);
            ((player*)entity)->getBonePos(((player*)entity)->getSkeleton(), entity->get_visual_state(), 65, &pLwristPos);
            color = ImColor( 28, 255, 20);
        }
        else if( entity->get_entity_type( )->get_type( )->get_object_name( )->get_str( ) == "dayzinfected" )
        {
            zhead_pos = ( ( infected* )entity )->get_bone_pos( 17 );
            color = ImColor( 255, 59, 20 );
        }

        /* oh allah you shall be ashamed of me please forgive me once again : (*/
        vector sPforehead, sPhead, sPneck, sPchest, sPpelvis, sPrhip, sPrknee, sPrankle, sPrmidfoot, sPrfoot, sPlhip, sPlknee, sPlankle, sPlmidfoot, sPlfoot, sPrsho, sPrelbow, sPrwrist, sPlsho, sPlelbow, sPlwrist;
        vector screen_head_pos;
        if( !camera->screen_transform(zhead_pos + .2, screen_head_pos ) || !camera->screen_transform(pForeHeadPos, sPforehead) || !camera->screen_transform(pHeadPos, sPhead) || !camera->screen_transform(pNeckPos, sPneck) ||
            !camera->screen_transform(pChestPos, sPchest) || !camera->screen_transform(pPelivsPos, sPpelvis) ||
            !camera->screen_transform(pRhipPos, sPrhip) || !camera->screen_transform(pRkneePos, sPrknee) || !camera->screen_transform(pRanklePos, sPrankle) || !camera->screen_transform(pRmidFootPos, sPrmidfoot) ||
            !camera->screen_transform(pRfootPos, sPrfoot) || !camera->screen_transform(pLhipPos, sPlhip) ||
            !camera->screen_transform(pLkneePos, sPlknee) || !camera->screen_transform(pLanklePos, sPlankle) || !camera->screen_transform(pLmidFootPos, sPlmidfoot) || !camera->screen_transform(pLfootPos, sPlfoot) || !camera->screen_transform(pRShoulderPos, sPrsho) ||
            !camera->screen_transform(pRelbowPos, sPrelbow) || !camera->screen_transform(pRwristPos, sPrwrist) ||
            !camera->screen_transform(pLShoulderPos, sPlsho) || !camera->screen_transform(pLelbowPos, sPlelbow) || !camera->screen_transform(pLwristPos, sPlwrist))
            continue;

        // o allah will you forgive me of my sins and my sins will be forgiven.


        auto local_pos = local_player->get_visual_state( )->get_position( );
        auto zmbi_pos = entity->get_visual_state( )->get_position( );

        auto distance = static_cast< int >( local_pos.dist_to( zmbi_pos ) );

        static int alpha = 255;
        alpha += distance > 300 ? -1 : 25;

        std::clamp( alpha, 0, 255 );
        if( entity->get_entity_type( )->get_type( )->get_object_name( )->get_str( ) == "dayzplayer" )
        {
            auto box_h = fabs( sPforehead.y - screen_pos.y );
            auto box_w = box_h / 1.65f;

            auto left = screen_pos.x - box_w * 0.5f;
            auto right = left + box_w;
            auto bottom = screen_pos.y;
            auto top = sPforehead.y;
            // name esp
            {
                auto name = entity->get_entity_type( )->get_clean_name( )->get_str( );

                auto sz = g_renderer.smallest_pixel->CalcTextSizeA( 10.f, FLT_MAX, 0.0f, name.c_str( ) );

                ImGui::PushFont( g_renderer.smallest_pixel );
                g_renderer.text( ImVec2( ( left + box_w / 2 ) - sz.x / 2, top - sz.y - 1 ), name, ImColor( 255, 255, 255, alpha ) );
                ImGui::PopFont( );

            }
            // distance esp
            {
                auto dist_str = std::string( std::to_string( distance ) + "m" );

                auto dist_sz = g_renderer.smallest_pixel->CalcTextSizeA( 10.f, FLT_MAX, 0.0f, dist_str.c_str( ) );

                ImGui::PushFont( g_renderer.smallest_pixel );
                g_renderer.text( ImVec2( ( left + box_w / 2 ) - dist_sz.x / 2, top + box_h + 1.f ), dist_str, ImColor(255,255,255, alpha) );
                ImGui::PopFont( );
            }
            // box :skull:
            {
                g_renderer.circle(ImVec2(sPhead.x, sPhead.y), 75.f / sPhead.z, ImColor(1.f, 1.f, 1.f), 1.f, true, false);
                g_renderer.line(ImVec2(sPhead.x, sPhead.y), ImVec2(sPneck.x, sPneck.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPneck.x, sPneck.y), ImVec2(sPpelvis.x, sPpelvis.y), ImColor(1.f, 1.f, 1.f), 1.f, true);

                // Right Shoulder to Right wrist
                g_renderer.line(ImVec2(sPneck.x, sPneck.y), ImVec2(sPrsho.x, sPrsho.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPrsho.x, sPrsho.y), ImVec2(sPrelbow.x, sPrelbow.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPrelbow.x, sPrelbow.y), ImVec2(sPrwrist.x, sPrwrist.y), ImColor(1.f, 1.f, 1.f), 1.f, true);

                // Right Hip to Right foot
                g_renderer.line(ImVec2(sPpelvis.x, sPpelvis.y), ImVec2(sPrhip.x, sPrhip.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPrhip.x, sPrhip.y), ImVec2(sPrknee.x, sPrknee.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPrknee.x, sPrknee.y), ImVec2(sPrankle.x, sPrankle.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPrankle.x, sPrankle.y), ImVec2(sPrmidfoot.x, sPrmidfoot.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPrmidfoot.x, sPrmidfoot.y), ImVec2(sPrfoot.x, sPrfoot.y), ImColor(1.f, 1.f, 1.f), 1.f, true);

                // Left Shoulder to left wrist
                g_renderer.line(ImVec2(sPneck.x, sPneck.y), ImVec2(sPlsho.x, sPlsho.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPlsho.x, sPlsho.y), ImVec2(sPlelbow.x, sPlelbow.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPlelbow.x, sPlelbow.y), ImVec2(sPlwrist.x, sPlwrist.y), ImColor(1.f, 1.f, 1.f), 1.f, true);

                // Left Hip to left foot
                g_renderer.line(ImVec2(sPpelvis.x, sPpelvis.y), ImVec2(sPlhip.x, sPlhip.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPlhip.x, sPlhip.y), ImVec2(sPlknee.x, sPlknee.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPlknee.x, sPlknee.y), ImVec2(sPlankle.x, sPlankle.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPlankle.x, sPlankle.y), ImVec2(sPlmidfoot.x, sPlmidfoot.y), ImColor(1.f, 1.f, 1.f), 1.f, true);
                g_renderer.line(ImVec2(sPlmidfoot.x, sPlmidfoot.y), ImVec2(sPlfoot.x, sPlfoot.y), ImColor(1.f, 1.f, 1.f), 1.f, true);



            }
        }else if(entity->get_entity_type()->get_type()->get_object_name()->get_str() == "dayzinfected"){
            auto box_h = fabs( screen_head_pos.y - screen_pos.y );
            auto box_w = box_h / 1.65f;

            auto left = screen_pos.x - box_w * 0.5f;
            auto right = left + box_w;
            auto bottom = screen_pos.y;
            auto top = screen_head_pos.y;
            // name esp
            {
                auto name = entity->get_entity_type( )->get_clean_name( )->get_str( );

                auto sz = g_renderer.smallest_pixel->CalcTextSizeA( 10.f, FLT_MAX, 0.0f, name.c_str( ) );

                ImGui::PushFont( g_renderer.smallest_pixel );
                g_renderer.text( ImVec2( ( left + box_w / 2 ) - sz.x / 2, top - sz.y - 1 ), name, ImColor( 255, 255, 255, alpha ) );
                ImGui::PopFont( );

            }
            // distance esp
            {
                auto dist_str = std::string( std::to_string( distance ) + "m" );

                auto dist_sz = g_renderer.smallest_pixel->CalcTextSizeA( 10.f, FLT_MAX, 0.0f, dist_str.c_str( ) );

                ImGui::PushFont( g_renderer.smallest_pixel );
                g_renderer.text( ImVec2( ( left + box_w / 2 ) - dist_sz.x / 2, top + box_h + 1.f ), dist_str, ImColor(255,255,255, alpha) );
                ImGui::PopFont( );
            }
            // healthbar
            {
                int health = entity->get_health( );
                float health_box_h = ( float )fabs( bottom - top );
                float off = 6;

                int height = ( health_box_h * health ) / 100;

                int green = int( health * 2.55f );
                int red = 255 - green;

                int x = left - off;
                int y = bottom;
                int w = 4;

                g_renderer.filled_box<int>( x, y, x + w, y + health_box_h, ImColor( 0, 0, 0, 255 ), 1, 1 );
                g_renderer.filled_box<int>( x + 1, y + 1, x + w - 1, y + height - 2, ImColor( red, green, 0, 255 ), 1.f, true );
            }
            // box :skull:
            {
                g_renderer.box<int>( left - 1, top - 1, right + 1, bottom + 1, ImColor( 0, 0, 0, alpha ), 1, 0, 1 );
                g_renderer.box<int>( left + 1, top + 1, right - 1, bottom - 1, ImColor( 0, 0, 0, alpha ), 1, 0, 1 );
                g_renderer.box<int>( left, top, right, bottom, ImColor(color.Value.x, color.Value.y, color.Value.z, (float)alpha ), 1, 0, 1 );

            }
        }
    }
}
