#pragma once
#include "option.h"

namespace base::gui {
	class button_option : public base_option<button_option> {
	private:
		std::function<void()> m_function;
	public:
		explicit button_option(const char* text) {
			set_left_text(text);
		}

		button_option& add_tooltip(const char* description)
		{
			base_option::set_tooltip(description);
			return *this;
		}

		button_option& add_right_text(const char* const text) {
			base_option::set_right_text(text);
			return *this;
		}

		button_option& add_click(std::function<void()> function) {
			set_action(std::move(function));
			return *this;
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::simple_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};
}