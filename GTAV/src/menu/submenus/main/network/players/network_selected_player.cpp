#include "pch.h"
#include "network_selected_player.h"
#include "rage/invoker/natives.h"
#include "../network_players.h"
using namespace base::gui;

namespace menu {
	void network_selected_player_menu::render() {
		renderer::add_submenu(PLAYER::GET_PLAYER_NAME(players::vars::m_vars.m_selected_player), [](core* core) {
			core->add_option(button_option(PLAYER::GET_PLAYER_NAME(players::vars::m_vars.m_selected_player)));
		});
	}

	void network_selected_player_menu::update() {
		render();
	}
}