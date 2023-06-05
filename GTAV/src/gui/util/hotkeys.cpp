#include "pch.h"
#include "hotkeys.h"
#include "util/util.h"
#include "util/log.h"
#include "rage/invoker/natives.h"
#include "gui/util/notify.h"
namespace menu {
	void hotkey::update() {
		for (hotkey_context& key : m_hotkeys) {
			if (Util::is_key_pressed(key.m_key)) {
				
			}		
		}
	}

    void hotkey::read_hotkey() {
        bool registerMode = false;
        bool keyPressed = false;
        int key = -1;

        if (Util::is_key_pressed(VK_F12)) {
            PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
            HUD::SET_TEXT_CENTRE(TRUE);
            HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
            HUD::SET_TEXT_FONT(0);
            HUD::SET_TEXT_SCALE(1.f, 1.f);
            HUD::SET_TEXT_OUTLINE();
            HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
            HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("PRESS ANY KEY...");
            HUD::END_TEXT_COMMAND_DISPLAY_TEXT({ 0.5f, 0.5f }, 0);
            registerMode = true;
        }

        if (registerMode) {
            while (Util::is_key_pressed(VK_F12)) {}

            while (!keyPressed) {
                for (int i = 0; i < 256; ++i) {
                    if (Util::is_key_pressed(i)) {
                        key = i;
                        keyPressed = true;
                        break;
                    }
                }
            }
        }

        if (key != -1) {
            register_hotkey(key);
        }
    }

	void hotkey::register_hotkey(int key) {

        notify::stacked("Hotkey", "Registered Hotkey");
		m_hotkeys.push_back({ key });
	}

	void hotkey::unregister_hotkey() {
		for (std::size_t i = 0; i < m_hotkeys.size(); i++) {
			hotkey_context& hotkey = m_hotkeys[i];
			m_hotkeys.erase(begin(m_hotkeys) + i);
			
		}
	}

	hotkey* get_hotkey() {
		static hotkey instance;
		return &instance;
	}
}