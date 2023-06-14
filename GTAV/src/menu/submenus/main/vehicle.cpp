#include "pch.h"
#include "vehicle.h"

using namespace base::gui;
using namespace menu::vehicle::vars;

namespace menu::vehicle::vars {
	variables m_vars;

}

namespace menu {

	void vehicle_menu::render() {
		renderer::addSubmenu("Vehicle", [](core* core) {
			core->add_option(submenu_option("Vehicle Mods"));

			core->add_option(break_option("Quick Access"));

			core->add_option(toggle_option("Godmode")
				.add_hotkey().add_translate()
				.add_toggle(&m_vars.m_godmode)
				.add_click([] { if (!m_vars.m_godmode) ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false); }));

			core->add_option(toggle_option("Invisibility")
				.add_hotkey().add_translate()
				.add_toggle(&m_vars.m_invisibility)
				.add_click([] { if (!m_vars.m_invisibility) ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true, true); }));

			core->add_option(toggle_option("Seatbelt")
				.add_hotkey().add_translate()
				.add_toggle(&m_vars.m_seatbelt)
				.add_click([] {
					if (!m_vars.m_seatbelt) {
						PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, true);
					}
				}));
		});
	}

	void vehicle_menu::update() {
		render();
		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (m_vars.m_godmode) {
				ENTITY::SET_ENTITY_INVINCIBLE(vehicle, true);
			}

			if (m_vars.m_invisibility) {
				ENTITY::SET_ENTITY_VISIBLE(vehicle, false, true);
			}

			if (m_vars.m_seatbelt) {
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, false);
			}

		}
	}
}