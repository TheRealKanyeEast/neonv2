#pragma once

#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"

namespace menu {
	class player_menu {
	public:
		void render();
		void update();
	};

	static player_menu* getPlayerMenu() {
		static player_menu instance;
		return &instance;
	}


	namespace player::vars {
		struct variables {
			bool m_godmode;
			bool m_cops_turn_blind_eye;
			bool m_off_the_radar;
			bool m_reveal_hidden_players;
		};

		extern variables m_vars;
	}
}