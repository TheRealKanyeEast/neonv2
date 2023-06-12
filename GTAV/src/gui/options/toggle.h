#pragma once
#include "pch.h"
#include "option.h"
#include "gui/renderer.h"
namespace base::gui {
	class toggle_option : public base_option<toggle_option> {
	private:
		bool* m_Bool = nullptr;
		bool m_DisplayInverted = false;
		std::function<void()> m_action = [] {};
		std::string m_name = "";
	public:
		explicit toggle_option(const char* const text) {
			m_name = text;
			base_option::set_left_text(m_name.c_str());
		}

		toggle_option& add_tooltip(const char* const text) {
			base_option::set_tooltip(text);
			return *this;
		}

		toggle_option& add_click(std::function<void()> action = [] {}) {
			m_action = action;
			base_option::set_action(std::move(m_action));
			return *this;
		}

		toggle_option& add_toggle(bool* const b00l) {
			m_Bool = b00l;
			return *this;
		}

		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::click) {
				*m_Bool = !*m_Bool;
			}
			base_option::handle_action(action);
		}

		bool* get_bool_pointer() override {
			return m_Bool;
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::toggle_option) {
				menu::renderer::getRenderer()->m_toggled_on = *m_Bool;
				return true;
			}
			return base_option::get_flag(flag);
		}
	};
}