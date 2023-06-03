#include "pch.h"
#include "renderer.h"
#include "rage/invoker/natives.h"
#include "render.h"
#include "rage/classes/enums.h"
#include "util/timer.h"

namespace menu::renderer {

	bool is_key_pressed(std::uint16_t key) {
		if (GetForegroundWindow() == g_window) {
			if (GetAsyncKeyState(key) & 0x8000) {
				return true;
			}
		}
		return false;
	}

	bool is_key_held(bool keyState, bool& keyHeld, Timer& holdTimer, Timer& scrollTimer, std::chrono::milliseconds initialDelay, std::chrono::milliseconds accelerationDelay)
	{
		if (keyState) {
			if (!keyHeld) {
				if (holdTimer.Update()) {
					keyHeld = true;
					scrollTimer.SetDelay(initialDelay);
					return true;
				}
			}
			else {
				if (scrollTimer.Update()) {
					scrollTimer.SetDelay(accelerationDelay);
					return true;
				}
			}
		}
		else {
			keyHeld = false;
			holdTimer.Reset();
			scrollTimer.SetDelay(initialDelay);
		}

		return false;
	}


	void renderer::render() {
		//fonts::gfx::load();
		check_keys();
		handle_keys();
		if (m_opened) {
			PAD::DISABLE_CONTROL_ACTION(0, 27, true);
			m_draw_base_y = m_position.y;
			if (!m_submenu_stack.empty()) {
				auto sub = m_submenu_stack.top();
				sub->reset();
				sub->execute();
				draw_header();
				draw_title(sub);
				draw_background(sub);
				if (sub->get_options_size() != 0) {
					std::size_t startPoint = 0;
					std::size_t endPoint = sub->get_options_size() > m_max_vis_options ? m_max_vis_options : sub->get_options_size();
					if (sub->get_options_size() > m_max_vis_options && sub->get_selected_option() >= m_max_vis_options) {
						startPoint = sub->get_selected_option() - m_max_vis_options + 1;
						endPoint = sub->get_selected_option() + 1;
					}
					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j) {
						draw_option(sub->get_option(i), i == sub->get_selected_option());
					}
				}
				update_scroller();
				draw_footer();
				render_tooltip();
			}
		}
	}

	void renderer::update_scroller() {
		if (m_current != m_target)
			m_current = m_current * (1 - m_speed) + m_target * m_speed;
		if ((m_current > m_target - 0.0005) && (m_current < m_target + 0.0005))
			m_current = m_target;
	}

	void renderer::reset_keys() {
		m_open_key = false, m_back_key = false, m_enter_key = false, m_up_key = false; m_down_key = false,
			m_left_key = false, m_right_key = false;
	}
	void renderer::check_keys() {
		reset_keys();
		m_open_key = is_key_pressed(VK_F4) || (PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendX)), m_back_key = is_key_pressed(VK_BACK) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel), m_enter_key = is_key_pressed(VK_RETURN) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept),
			m_up_key = is_key_pressed(VK_UP) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp), m_down_key = is_key_pressed(VK_DOWN) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown), m_left_key = is_key_pressed(VK_LEFT) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendLeft),
			m_right_key = is_key_pressed(VK_RIGHT) || PAD::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendRight);
	}
	void renderer::handle_keys() {
		static auto openTicker = GetTickCount();
		if (m_open_key && GetTickCount() - openTicker >= static_cast<std::uint32_t>(m_open_delay))
		{
			openTicker = GetTickCount();
			m_opened ^= true;

			AUDIO::PLAY_SOUND_FRONTEND(-1, m_opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		}

		static Timer backTimer(0ms);
		backTimer.SetDelay(std::chrono::milliseconds(m_back_delay));
		if (m_opened && m_back_key && backTimer.Update())
		{

			AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

			if (m_submenu_stack.size() <= 1)
			{
				m_opened = false;
			}
			else
			{
				m_submenu_stack.pop();
			}
		}

		if (m_opened && !m_submenu_stack.empty())
		{
			auto sub = m_submenu_stack.top();

			static Timer enterTimer(0ms);
			enterTimer.SetDelay(std::chrono::milliseconds(m_enter_delay));
			if (m_enter_key && sub->get_options_size() != 0 && enterTimer.Update())
			{

				AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->get_option(sub->get_selected_option()))
				{
					opt->handle_action(eOptionAction::click);
				}
			}

			static Timer upTimer(0ms);
			upTimer.SetDelay(std::chrono::milliseconds(m_vertical_delay));
			if (m_up_key && sub->get_options_size() != 0 && upTimer.Update())
			{

				AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->scroll_backward();
			}

			static Timer downTimer(0ms);
			downTimer.SetDelay(std::chrono::milliseconds(m_vertical_delay));
			if (m_down_key && sub->get_options_size() != 0 && downTimer.Update())
			{

				AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->scroll_forward();
			}

			static Timer leftTimer(0ms);
			leftTimer.SetDelay(std::chrono::milliseconds(m_horizontal_delay));
			if (m_left_key && sub->get_options_size() != 0 && leftTimer.Update())
			{

				AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->get_option(sub->get_selected_option()))
				{
					opt->handle_action(eOptionAction::left_click);
				}
			}

			static Timer rightTimer(0ms);
			rightTimer.SetDelay(std::chrono::milliseconds(m_horizontal_delay));
			if (m_right_key && sub->get_options_size() != 0 && rightTimer.Update())
			{

				AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->get_option(sub->get_selected_option()))
				{
					opt->handle_action(eOptionAction::right_click);
				}
			}
		}
	}

	void renderer::draw_scroller() {
		m_target = render::get_rect_base(m_option.m_height);

		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(2);
		render::draw_rect({ m_position.x, m_current }, { m_width, m_option.m_height }, m_scroller_color);
	}

	void renderer::draw_header() {
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(1);
		render::draw_rect({ m_position.x, render::get_rect_base(m_header.m_height) }, { m_width, m_header.m_height }, m_header.m_color);
		render::draw_text("NEON", JUSTIFY_LEFT, { m_position.x, render::get_rect_base(m_header.m_height) }, m_header.m_font_scale, m_header.m_font, { 2.1f, 2.1f }, m_header.m_text_color, true);
		m_draw_base_y += m_header.m_height;
	}

	void renderer::draw_title(base::gui::abstract_submenu* sub) {
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(1);
		render::draw_rect({ m_position.x, render::get_rect_base(m_title.m_height) }, { m_width, m_title.m_height }, m_title.m_color);
		render::draw_text(sub->get_name(), JUSTIFY_LEFT, { m_position.x, render::get_rect_base(m_title.m_height) }, m_title.m_font_scale, m_title.m_font, m_title.m_padding);
		char rightText[32] = {};
		std::snprintf(rightText, sizeof(rightText) - 1, "%zu / %zu", sub->get_selected_option() + 1, sub->get_options_size());

		render::draw_text(rightText, JUSTIFY_RIGHT, { m_position.x + (m_width / m_title.m_padding.x), render::get_rect_base(m_title.m_height)}, m_title.m_font_scale, m_title.m_font, m_title.m_padding);

		m_draw_base_y += m_title.m_height;
	}

	void renderer::draw_background(base::gui::abstract_submenu* sub) {
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(1);
		int visible_options = sub->get_options_size() > m_max_vis_options ? m_max_vis_options : sub->get_options_size();
		render::draw_rect({ m_position.x, m_draw_base_y + ((m_option.m_height * visible_options) / 2.f) }, { m_width, m_option.m_height * visible_options }, m_option.m_color);
	}

	void renderer::draw_option(base::gui::abstract_option* option, bool selected) {
		if (selected) {
			draw_scroller();
		}
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(4);
		auto y_pos = selected ? m_current : render::get_rect_base(m_option.m_height);
		render::draw_text(option->get_left_text(), JUSTIFY_LEFT, { m_position.x, y_pos }, m_option.m_font_scale, m_option.m_font, m_option.m_padding, selected ? m_option.m_selected_text_color : m_option.m_text_color);

		if (option->get_flag(eOptionFlag::indicator)) {
			render::draw_right_text(">", m_position.x + (m_width / m_option.m_padding.x), m_draw_base_y + (m_option.m_height / 2.f)
				- (render::get_text_height(2, 0.4) / 1.725f), 0.4, 2,
				selected ? m_option.m_selected_text_color : m_option.m_text_color, false, false);
		}

		if (option->get_flag(eOptionFlag::toggle_option)) {
			auto size = render::get_sprite_scale(0.028);
			if (m_toggled_on) {
				render::draw_sprite({ "commonmenu", "common_medal" }, { m_position.x + (m_width / m_option.m_padding.x - 0.0045f),
					m_draw_base_y + (m_option.m_height / 2.f), }, { size.x, size.y }, { 130, 214, 157, 255 }, 0.0f);
			}
			else {
				render::draw_sprite({ "commonmenu", "common_medal" }, { m_position.x + (m_width / m_option.m_padding.x - 0.0045f),
					m_draw_base_y + (m_option.m_height / 2.f), }, { size.x, size.y }, { 200, 55, 80, 255 }, 0.0f);
			}
		}

		if (option->get_flag(eOptionFlag::number_option)) {
			render::draw_right_text(option->get_right_text(), m_position.x + (m_width / m_option.m_padding.x),
				m_draw_base_y + (m_option.m_height / 2.f) - (render::get_text_height(m_option.m_font, m_option.m_font_scale) / 1.5f) - 0.00007,
				m_option.m_font_scale, m_option.m_font, selected ? m_option.m_selected_text_color : m_option.m_text_color, false, false);


		}

		m_draw_base_y += m_option.m_height;
	}

	void renderer::render_tooltip() {
		

	}

	void renderer::draw_footer() {
		render::draw_rect({ m_position.x, m_draw_base_y + (m_footer.m_height / 2.f) }, { m_width, m_footer.m_height }, m_footer.m_color);;
		float size = 0.025f;
		auto sizee = render::get_sprite_scale(size);
		
		render::draw_sprite({ "commonmenu", "shop_arrows_upanddown" }, { m_position.x, m_draw_base_y + (m_footer.m_height / 2.f) }, { sizee.x, sizee.y }, { 255,255,255,255 }, 0.f);
		m_draw_base_y += m_footer.m_height;
	}
}