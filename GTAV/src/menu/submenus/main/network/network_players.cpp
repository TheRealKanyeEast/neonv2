#include "pch.h"
#include "network_players.h"
#include "rage/invoker/natives.h"
#include "players/network_selected_player.h"
using namespace base::gui;
using namespace menu::players::vars;

namespace menu::players::vars {
	variables m_vars;
}

namespace menu {

	void network_players_menu::render() {
		renderer::add_submenu("Players", [](core* core) {
			for (uint32_t i = 0; i < 32; i++) {
				if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)) {
					if (ENTITY::DOES_ENTITY_EXIST(ped)) {
						core->add_option(submenu_option(PLAYER::GET_PLAYER_NAME(i))
							.add_click([&] { m_vars.m_selected_player = i; })
							.set_target(PLAYER::GET_PLAYER_NAME(i)));
					}
				}
			}
		});
	}

	void network_players_menu::update() {
		render();
		getNetworkSelectedPlayerMenu()->update();
	}

}