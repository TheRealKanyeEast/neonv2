#include "pch.h"
#include "network_selected_player.h"
#include "rage/invoker/natives.h"
#include "../network_players.h"
#include "gui/util/panels.h"
using namespace base::gui;
using namespace menu::players::selected::vars;

namespace menu::players::selected::vars {
	variables m_vars;
}

namespace menu {
	void network_selected_player_menu::render() {
		renderer::addPlayerSubmenu(&players::vars::m_vars.m_selected_player, rage::joaat("selected_player"), [](pcore* core) {
			menu::g_panel_spacing = 0.06;
			player_info_panel(players::vars::m_vars.m_selected_player);

			core->add_option(button_option(PLAYER::GET_PLAYER_NAME(players::vars::m_vars.m_selected_player)));	

			core->add_option(toggle_option("Spectate")
				.add_toggle(&m_vars.m_spectate));
		});
	}

	void network_selected_player_menu::update() {
		render();

		if (m_vars.m_spectate) {
			const auto target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(players::vars::m_vars.m_selected_player);

			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, target);
			HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, target);

			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);
			ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true), true);

			STREAMING::SET_FOCUS_ENTITY(target);
		}
		else {
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, -1);
			HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, -1);

			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);

			STREAMING::SET_FOCUS_ENTITY(PLAYER::PLAYER_PED_ID());
		}
	}
}