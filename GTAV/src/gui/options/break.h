#pragma once
#include "option.h"
#include "gui/render.h"

namespace base::gui {
	class break_option : public base_option<break_option> {
	public:
		explicit break_option(const char* text) {
			set_left_text(text);
		}
		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::break_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};
}