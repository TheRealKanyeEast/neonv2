#include "pch.h"
#include "player.h"
#include "features/manager/manager.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"

using namespace base::gui;
using namespace menu::player::vars;

namespace menu::player::vars {
	variables m_vars;

	void cops_turn_blind_eye() {
		if (m_vars.m_cops_turn_blind_eye) {
			*menu::script_global::script_global(2793046).at(4654).as<std::int32_t*>() = 1;
			*menu::script_global::script_global(2793046).at(4657).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME() + 638000;
		}
		else {
			*menu::script_global::script_global(2793046).at(4654).as<std::int32_t*>() = 0;
			*menu::script_global::script_global(2793046).at(4657).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME();
		}
	}

	void off_the_radar() {
		if (m_vars.m_off_the_radar) {
			*menu::script_global::script_global(2657589).at(PLAYER::PLAYER_ID(), 466).at(210).as<std::int32_t*>() = 1;
			*menu::script_global::script_global(2672505).at(57).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME() + 758000;
		}
		else {
			*menu::script_global::script_global(2657589).at(PLAYER::PLAYER_ID(), 466).at(210).as<std::int32_t*>() = 0;
			*menu::script_global::script_global(2672505).at(57).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME();
		}
	}

	void reveal_hidden_players() {
		if (m_vars.m_reveal_hidden_players) {
			*menu::script_global::script_global(2657589).at(PLAYER::PLAYER_ID(), 466).at(213).as<std::int32_t*>() = 1;
			*menu::script_global::script_global(2672505).at(58).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME() + 758000;
		}
		else {
			*menu::script_global::script_global(2657589).at(PLAYER::PLAYER_ID(), 466).at(213).as<std::int32_t*>() = 0;
			*menu::script_global::script_global(2672505).at(58).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME();
		}
	}

}

namespace menu {
	
	void suicide(features::actionFeature* feature) {
		ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, 0);
	}


	void player_menu::render() {
		renderer::addSubmenu("Player", [](core* core) {

			core->add_option(toggle_option("Godmode")
				.add_toggle(&"player_godmode"_TF->m_value.toggle).add_click([] {
					if (!"player_godmode"_TF->m_value.toggle) {
						ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
					}
				}));

			core->add_option(toggle_option("Disable Police")
				.add_toggle(&"player_disable_police"_TF->m_value.toggle));

			core->add_option(toggle_option("Off the Radar")
				.add_toggle(&m_vars.m_off_the_radar)
				.add_click(off_the_radar));

			core->add_option(toggle_option("Cops Turn Blind Eye")
				.add_toggle(&m_vars.m_cops_turn_blind_eye)
				.add_click(cops_turn_blind_eye));

			core->add_option(toggle_option("Reveal Hidden Players")
				.add_toggle(&m_vars.m_reveal_hidden_players)
				.add_click(reveal_hidden_players));

			core->add_option(button_option("Suicide")
				.add_click([] { suicide("player_suicide"_AF); }));
		});
	}

	void player_menu::update() {
		render();	

		if (m_vars.m_off_the_radar) {
			off_the_radar();
		}

		if (m_vars.m_reveal_hidden_players) {
			reveal_hidden_players();
		}

		if (m_vars.m_cops_turn_blind_eye) {
			cops_turn_blind_eye();
		}
	}
}