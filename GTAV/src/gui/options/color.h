#pragma once
#include "option.h"
#include "util/util.h"
#include "util/log.h"
#include "gui/renderer.h"
#include "gui/util/translate.h"

namespace base::gui {
	class color_option : public base_option<color_option> {
	private:
		std::uint32_t m_sub_id{};
	public:
		explicit color_option(const char* text, color color) {
			set_left_text(text);
			set_color(color);
		}

		color_option& set_target(const const char* id) {
			m_sub_id = rage::joaat(id);
			return *this;
		}

		color_option& add_translate() {
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
			if (flag == eOptionFlag::color_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};

}