#include "pch.h"
#include "weapon_mods.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
using namespace base::gui;
using namespace menu::weapon::mods::vars;

namespace menu::weapon::mods::vars {
	variables m_vars;


	Vector3 get_direction(Vector3 rotation) {
		Vector3 tmp;
		tmp.y = rotation.z * 0.0174532924f;
		tmp.x = rotation.x * 0.0174532924f;
		tmp.z = abs(cos(tmp.x));

		return Vector3((-sin(tmp.y)) * tmp.z, (cos(tmp.y)) * tmp.z, sin(tmp.x));
	}
}



namespace menu {

	void weapon_mods_menu::render() {
		renderer::addSubmenu("Weapon Mods", [](core* core) {

			core->add_option(toggle_option("Unlimited Ammo")
				.add_hotkey().add_translate()
				.add_toggle(&m_vars.m_unlimited_ammo));

			core->add_option(toggle_option("Instant Kill")
				.add_hotkey().add_translate()
				.add_toggle(&m_vars.m_instant_kill));

			core->add_option(toggle_option("Rapid Fire")
				.add_hotkey().add_translate()
				.add_toggle(&m_vars.m_rapid_fire));

		});		
	}

	void weapon_mods_menu::update() {
		render();		
		raycast::raycastUpdate();

		uint32_t m_weapon_hash = 0;
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_weapon_hash, false);

		if (m_vars.m_unlimited_ammo) {
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), true);
		}

		if (m_vars.m_instant_kill) {
			PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_PED_ID(), 99999.f, 1);
			PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_PED_ID(), 99999.f);
		}

		if (m_vars.m_rapid_fire) {
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
				if (PAD::IS_CONTROL_PRESSED(0, ControlAttack)) {
					Vector3 start = CAM::GET_GAMEPLAY_CAM_COORD() + (get_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)));
					Vector3 end = CAM::GET_GAMEPLAY_CAM_COORD() + (get_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)) * 200.f);
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(start, end, WEAPON::GET_WEAPON_DAMAGE_TYPE(m_weapon_hash), true, m_weapon_hash, PLAYER::PLAYER_PED_ID(), true, false, 500.0f, PLAYER::PLAYER_PED_ID(), 0);
				}
			}
		}

	}
}