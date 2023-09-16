#pragma once
#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"
#include "menu/util/players.h"

namespace menu {
	class network_players_removals_menu {
	public:
		void render();
		void update();
	};

	static network_players_removals_menu* getNetworkPlayersRemovalsMenu() {
		static network_players_removals_menu instance;
		return &instance;
	}

	namespace players::selected::removals::vars {
		struct variables {
			bool m_session_crash = false;
			bool m_break_nodes = false;
			int m_crash_type = 2;
			uint32_t m_break_node_threads[2] = { 0, 0 };
			uint32_t m_session_crash_timeout = 0;
		};

		extern variables m_vars;
	}
}