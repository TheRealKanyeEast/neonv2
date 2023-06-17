#include "pch.h"
#include "panels.h"
#include "gui/render.h"
#include "gui/renderer.h"

namespace menu {

    void panel::start_panel(std::string title) {
        auto menu = renderer::getRenderer();

        g_panel_base_2 = g_panel_pos.y;

        if (!m_next_to) {
            if (menu->m_position.x > 0.5f) {
                g_panel_pos.x = menu->m_position.x - (menu->m_width / 2.f) + (m_width - g_panel_spacing);
            }
            else {
                g_panel_pos.x = menu->m_position.x + (menu->m_width / 2.f) - (m_width - g_panel_spacing);
            }
        }
        else {
            if (menu->m_position.x > 0.5f) {
                g_panel_pos.x = menu->m_position.x - (menu->m_width / 2.f) - (m_width - g_panel_spacing);
            }
            else {
                g_panel_pos.x = menu->m_position.x + (menu->m_width / 2.f) + (m_width - g_panel_spacing);
            }
            g_panel_base = g_panel_base_2;
        }

        g_panel_base = g_panel_pos.y;


        g_panel_pos.y = renderer::getRenderer()->m_position.y - 0.006f;

        render::draw_rect({ g_panel_pos.x, render::get_rect_base(m_title_height, g_panel_base) }, { m_width, 0.004f }, menu->m_header.m_color);
        g_panel_base += 0.004f;

        render::draw_rect({ g_panel_pos.x, render::get_rect_base(m_title_height, g_panel_base) }, { m_width, m_title_height }, m_back_ground);
     
        render::draw_text(title.c_str(), eJustify::JUSTIFY_LEFT, { g_panel_pos.x, render::get_rect_base(m_title_height, g_panel_base) }, m_title_font_scale, (int)m_title_font, m_padding);
        g_panel_base += m_title_height;
    }

    void panel::push(std::string left, std::string right) {
        render::draw_rect({ g_panel_pos.x, render::get_rect_base(m_item_height, g_panel_base) }, { m_width, m_title_height }, m_back_ground);
        render::draw_text(left.c_str(), eJustify::JUSTIFY_LEFT, { g_panel_pos.x, render::get_rect_base(m_item_height, g_panel_base ) }, m_font_scale, (int)m_item_font, m_padding);
        render::draw_text(right.c_str(), eJustify::JUSTIFY_RIGHT, { g_panel_pos.x + (m_width / 2.f) - 0.003f, render::get_rect_base(m_item_height, g_panel_base) }, m_font_scale, (int)m_item_font, m_padding);
        g_panel_base += m_item_height;
    }

    void panel::push_double(std::string left_left, std::string left_right, std::string right_left, std::string right_right) {

        render::draw_rect({ g_panel_pos.x, render::get_rect_base(m_item_height, g_panel_base) }, { m_width, m_title_height }, m_back_ground);
 /*     render::draw_text(left_left.c_str(), font_justify::left, { (panels::get()->m_panel_pos.x), renderer::get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);
        render::draw_text(left_right.c_str(), font_justify::right, { (panels::get()->m_panel_pos.x - (m_width / 2.f)), renderer::get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);
        render::draw_text(right_left.c_str(), font_justify::left, { (panels::get()->m_panel_pos.x + (m_width / 2.f)), renderer::get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);
        render::draw_text(right_right.c_str(), font_justify::right, { (panels::get()->m_panel_pos.x), renderer::get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);
        render::draw_text("~c~|", font_justify::center, { (panels::get()->m_panel_pos.x), renderer::get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale * 2.f, (int)m_item_font, m_padding, m_text_color, m_width);*/
       // panels::get()->m_panel_base += m_item_height;
    }

    void panel::end_panel() {
        g_panel_base += g_panel_spacing;
    }

    void panel::set_next() {
        m_next_to = true;
    }

}