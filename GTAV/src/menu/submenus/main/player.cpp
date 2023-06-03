#include "pch.h"
#include "player.h"
#include "features/manager/manager.h"

using namespace base::gui;
using namespace menu::player::vars;

namespace menu::player::vars {
	variables m_vars;
}

namespace menu {
	
	void suicide(features::actionFeature* feature) {
		ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, 0);
	}

	void player_menu::render() {
		renderer::add_submenu("Player", [](core* core) {

			core->add_option(toggle_option("Godmode")
				.add_toggle(&m_vars.m_godmode).add_click([] {
					if (!m_vars.m_godmode) {
						ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
					}
				}));

			core->add_option(button_option("Suicide")
				.add_click([] { suicide(0); }));
		});
	}

	void player_menu::update() {
		render();	

		if (m_vars.m_godmode) {
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
		}
	}
}