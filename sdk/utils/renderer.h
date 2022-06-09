//
// Created by pepej on 09.06.2022.
//

#ifndef PAZEL_RENDERER_H
#define PAZEL_RENDERER_H


#include "../hack/hooks/hooks.h"

class renderer
{
public:
    // Oh Allah, help me make correct choices

    void text( const ImVec2 v2_pos, std::string str_text, ImVec4 v4_col )
    {
        const char* text = str_text.c_str( );

        ImGui::GetWindowDrawList( )->AddText( ImVec2( v2_pos.x - 1, v2_pos.y - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 * v4_col.w ) ), text );
        ImGui::GetWindowDrawList( )->AddText( ImVec2( v2_pos.x + 1, v2_pos.y - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 * v4_col.w ) ), text );
        ImGui::GetWindowDrawList( )->AddText( ImVec2( v2_pos.x - 1, v2_pos.y + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 * v4_col.w ) ), text );
        ImGui::GetWindowDrawList( )->AddText( ImVec2( v2_pos.x + 1, v2_pos.y + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 * v4_col.w ) ), text );

        ImGui::GetWindowDrawList( ) ->AddText( v2_pos, ImGui::GetColorU32( v4_col ), text );
    }

    auto line(ImVec2 v2_pos, ImVec2 v2_pos2, ImVec4 v4_col, float f_thickness, bool b_outline = false)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();

        if (b_outline) {
            window->DrawList->AddLine(v2_pos, v2_pos2, ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), f_thickness + 1.f);
        }

        window->DrawList->AddLine(v2_pos, v2_pos2, ImGui::GetColorU32(v4_col), f_thickness);

    }
    auto line(int x, int y, int w, int h, ImVec4 v4_col, float f_thickness)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;

        const ImRect line_bb(ImVec2(x, y), ImVec2(x + w, y + h));

        window->DrawList->AddLine(ImVec2(line_bb.Min.x, line_bb.Min.y), ImVec2(line_bb.Max.x, line_bb.Max.y), ImGui::GetColorU32(v4_col), f_thickness);
    }
    void circle(ImVec2 v2_pos, float f_radius, ImVec4 v4_col, float f_thickness, bool b_outline, bool b_inline, float indicies = 50)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;

        if (b_outline) {
            window->DrawList->AddCircle(v2_pos, f_radius + 1.0f, ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), (int)f_radius, f_thickness);
        }
        if (b_inline) {
            window->DrawList->AddCircle(v2_pos, f_radius - 1.0f, ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), (int)f_radius, f_thickness);
        }
        window->DrawList->AddCircle(v2_pos, f_radius, ImGui::GetColorU32(v4_col), indicies, f_thickness);
    }

    void rect( ImVec2 v2_pos, ImVec2 v2_size, ImVec4 v4_col )
    {
        ImGui::GetWindowDrawList( )->AddRect( ImVec2( v2_pos.x - 1, v2_pos.y - 1 ), ImVec2( v2_pos.x + v2_size.x + 1, v2_pos.y + v2_size.y + 1 ), ImColor( 0, 0, 0, 255 ), 0.0f, 15, 1 );
        ImGui::GetWindowDrawList( )->AddRect( ImVec2( v2_pos.x, v2_pos.y ), ImVec2( v2_pos.x + v2_size.x, v2_pos.y + v2_size.y ), ImGui::GetColorU32( v4_col ), 0.0f, 15, 1 );
        ImGui::GetWindowDrawList( )->AddRect( ImVec2( v2_pos.x + 1, v2_pos.y + 1 ), ImVec2( v2_pos.x + v2_size.x - 1, v2_pos.y + v2_size.y - 1 ), ImColor( 0, 0, 0, 255 ), 0.0f, 15, 1 );
    }

    template <class T>
    void box( T x1, T y1, T x2, T y2, ImColor color, float thickness = 1.f, float rounding = 0.f, bool outline = false ) {

        ImGui::GetWindowDrawList( )->AddRect( ImVec2( x1, y1 ), ImVec2( x2, y2 ), ImColor( color ), rounding);
    }

    template <class T>
    void filled_box( T x1, T y1, T x2, T y2, ImColor color, float thickness = 1.f, float rounding = 0.f, bool outline = false ) {

        ImGui::GetWindowDrawList( )->AddRectFilled( ImVec2( x1, y1 ), ImVec2( x2, y2 ), ImColor( color ), rounding );
    }

    void gradient(ImVec2 v2_pos, ImVec2 v2_size, ImVec4 v4_col, ImColor v4_col2 )
    {
        const ImRect rect_bb( v2_pos, ImVec2( v2_pos.x + v2_size.x, v2_pos.y + v2_size.y ) );

        auto gradient = ImGui::GetColorU32( v4_col ) - v4_col2;
        ImGui::GetWindowDrawList( )->AddRectFilledMultiColor( rect_bb.Min, rect_bb.Max, ImGui::GetColorU32( v4_col ), ImGui::GetColorU32( v4_col ), gradient, gradient );
    }

private:
    //ImGuiWindow* window = ImGui::GetCurrentWindow( );

public:
    ImFont* smallest_pixel;
    ImFont* verdana;
};

extern renderer g_renderer;

#endif //PAZEL_RENDERER_H
