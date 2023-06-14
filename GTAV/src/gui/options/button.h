#pragma once
#include "option.h"
#include "util/util.h"
#include "util/log.h"
#include "gui/renderer.h"
#include "gui/util/translate.h"

namespace base::gui {
	class button_option : public base_option<button_option> {
	private:
		std::function<void()> m_function;
		struct Keyboard {
			bool m_enabled = false;
			bool m_is_active = false;
			int m_max_chars = 0;
			std::function<void(button_option*, const char*)> m_callback = {};
			std::string m_title = "";
			std::string m_default_text = "";
		};

		Keyboard m_keyboard;
	public:

		explicit button_option(const char* text) {
			set_left_text(text);
		}

		button_option& add_tooltip(const char* description) {
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

		button_option& add_hotkey() {
			add_tooltip("Hotkeys Supported. Press F8 to bind");
			return *this;
		}

		button_option& add_translate() {
			const char* translation = TRANSLATE(base_option::get_left_text());
			//set_left_text(translation);
			return *this;
		}


		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::simple_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};

	class keyboard_option : public base_option<keyboard_option> {
	private:
		std::function<void()> m_function;
	public:
		explicit keyboard_option(const char* text) {
			set_left_text(text);
		}

		keyboard_option& add_tooltip(const char* description) {
			base_option::set_tooltip(description);
			return *this;
		}

		keyboard_option& add_right_text(const char* text) {
			base_option::set_right_text(text);
			return *this;
		}

		keyboard_option& add_click(std::function<void()>&& function) {
			set_action(std::move(function));
			return *this;
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::keyboard_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};
}