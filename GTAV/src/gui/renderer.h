#pragma once
#include "pch.h"
#include "options/submenu.h"
#include "types.h"
#include "gui/options/core.h"

namespace menu::renderer {

	struct header {
		float m_height = 0.08f, m_font_scale = 1.f;
		int m_font = 7;

		color m_color = { 102, 51, 153 };
		color m_text_color = { 255, 255, 255 };
	};

	struct title {
		float m_height = 0.0295f, m_font_scale = 0.28f;
		int m_font = (int)eFont::ChaletLondon;
		math::vector2<float> m_padding = { 2.05f, 2.05f };

		color m_color = { 0, 0, 0, 255 };
		color m_text_color = { 255, 255, 255, 255 };
	};

	struct option {
		float m_height = 0.0315f, m_font_scale = 0.29f;
		int m_font = (int)eFont::ChaletLondon;
		math::vector2<float> m_padding = { 2.05f, 2.05f };


		color m_color = { 0, 0, 0, 160 };
		color m_text_color = { 255, 255, 255, 255 };
		color m_selected_text_color = { 0, 0, 0, 255 };
	};

	struct tooltip {
		int m_font = 4;
	};

	struct footer {
		float m_height = 0.0295, m_font_scale = 0.28f;
		int m_font = (int)eFont::ChaletLondon;
		math::vector2<float> m_padding = { 2.05f, 2.05f };

		color m_color = { 0,0,0,255 };
		color m_text_color = { 255,255,255,255 };
	};

	class renderer {
	public:
		void render();

		std::vector<std::unique_ptr<base::gui::abstract_submenu>>& get_all_subs() { return m_all_subs; }
		std::stack<base::gui::abstract_submenu*, std::vector<base::gui::abstract_submenu*>>& get_submenu_stack() { return m_submenu_stack; }

	public:
		bool m_opened{};
		bool m_toggled_on{};

		math::vector2<float> m_position = { 0.31f, 0.08f };
		float m_draw_base_y{};
		float m_width = 0.21f;

		std::size_t m_max_vis_options = 12;

		float m_target = { 0.f };
		float m_current = { 0.f };
		float m_speed = { 0.2281f };

		color m_scroller_color = { 255, 255, 255, 255 };

		header m_header;
		title m_title;
		option m_option;
		footer m_footer;
		tooltip m_tooltip;

		float m_delta = 0.f;
		float m_tooltip_x = 0.0985f;

		std::int32_t m_open_delay = 200, m_back_delay = 300, m_enter_delay = 300, m_vertical_delay = 120, m_horizontal_delay = 120;
		bool m_open_key; bool m_back_key; bool m_enter_key; bool m_up_key; bool m_down_key; bool m_left_key; bool m_right_key;
		void reset_keys();
		void check_keys();
		void handle_keys();

		void update_scroller();
		void draw_scroller();


		void render_tooltip();
		void draw_header();
		void draw_title(base::gui::abstract_submenu* sub);
		void draw_background(base::gui::abstract_submenu* sub);

		void draw_option(base::gui::abstract_option* option, bool selected);
		void draw_footer();
	private:
		std::vector<std::unique_ptr<base::gui::abstract_submenu>> m_all_subs;
		std::stack<base::gui::abstract_submenu*, std::vector<base::gui::abstract_submenu*>> m_submenu_stack;
	public:
		template <typename sub_type, typename ...TArgs>
		void add_submenu(TArgs&&... args) {
			auto sub = std::make_unique<sub_type>(std::forward<TArgs>(args)...);
			if (m_submenu_stack.empty()) {
				m_submenu_stack.push(sub.get());
			}
			m_all_subs.push_back(std::move(sub));
		}

		void switch_to_submenu(std::uint32_t id) {
			for (auto&& sub : m_all_subs) {
				if (sub->get_id() == id) {
					m_submenu_stack.push(sub.get());
					return;
				}
			}
		}
	};

	inline renderer* getRenderer() {
		static renderer instance;
		return &instance;
	}
	
	inline void add_submenu(const char* name, std::function<void(base::gui::core*)> action) {
		getRenderer()->add_submenu<base::gui::core>(name, action);
	}


}