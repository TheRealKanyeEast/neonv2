#pragma once
#include "option.h"
#include "gui/renderer.h"
#include "gui/util/translate.h"

namespace base::gui {
	class submenu_option : public base_option<submenu_option> {
	private:
		std::uint32_t m_sub_id{};
	public:
		explicit submenu_option(const char* text) {
			set_left_text(text);
		}

		submenu_option& add_click(std::function<void()>&& function) {
			set_action(std::move(function));
			return *this;
		}

		submenu_option& set_target(const const char* id) {
			m_sub_id = rage::joaat(id);
			return *this;
		}

		submenu_option& add_tooltip(const char* const text) {
			base_option::set_tooltip(text);
			return *this;
		}

		submenu_option& add_translate() {
			const char* translation = TRANSLATE(base_option::get_left_text());
			//set_left_text(translation);
			return *this;
		}

		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::click) {
				menu::renderer::getRenderer()->switch_to_submenu(m_sub_id);
			}
			base_option::handle_action(action);
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::indicator) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};
}