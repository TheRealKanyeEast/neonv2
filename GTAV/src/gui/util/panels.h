#pragma once
#include "util/math.h"
#include "gui/util/flags.h"
#include "gui/types.h"
#include "gui/renderer.h"
namespace menu {
    class panel {
    public:
        panel(float width, float title_height, float item_height) :
            m_width(width), m_title_height(title_height), m_item_height(item_height)
        {
        }
    public:
        void start_panel(std::string title);
        void push(std::string left, std::string right);
        void end_panel();
        void set_next();

    private:
        float m_width;
        float m_title_height;
        float m_item_height;
        bool m_next_to;
        eFont m_title_font = eFont::HouseScript;
        eFont m_item_font = eFont::ChaletLondon;
        color m_back_ground = { 0, 0, 0, 180 };
        float m_title_font_scale = 0.3f;
        float m_font_scale = 0.2f;
        math::vector2<float> m_padding = { 3.1f, 2.1f };
    };


    inline math::vector2<float> g_panel_pos = { renderer::getRenderer()->m_position.x, renderer::getRenderer()->m_position.y - 0.006f };
    inline float g_panel_base = 0.f;
    inline float g_panel_base_2 = 0.f;
    inline float g_panel_spacing = 0.065f;

    inline void playerinfo() {
        panel player_info(0.14f, 0.02f, 0.02f);
        player_info.start_panel("Example Panel");
        player_info.push("Gay", "False");
        player_info.push("Yesterday", "True");
        player_info.push("Tomorrow", "False");
        player_info.push("Running", "True");
        player_info.push("Walking", "False");
        player_info.push("Spinning", "False");
        player_info.push("Diving", "False");
        player_info.end_panel();
    }
}