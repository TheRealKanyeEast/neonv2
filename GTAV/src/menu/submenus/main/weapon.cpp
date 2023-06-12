#include "pch.h"
#include "weapon.h"
#include "rage/invoker/natives.h"
#include "menu/util/lists.h"
#include "rage/engine.h"
#include "util/util.h"

using namespace base::gui;

void upgrade_weapon_components(Ped ped, uint32_t weapon_hash) {
	for (const auto components : menu::lists::weapon_components) {
		if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weapon_hash, components.hash)) {
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weapon_hash, components.hash);
		}
	}
}

void remove_weapon_upgrades(Ped ped, uint32_t weapon_hash) {
	for (const auto components : menu::lists::weapon_components) {
		if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weapon_hash, components.hash)) {
			WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(ped, weapon_hash, components.hash);
		}
	}
}

void give_weapon(Ped ped, uint32_t weapon_hash, bool equip_now, bool fully_upgraded) {
	int ammo = -1;
	WEAPON::GET_MAX_AMMO(ped, weapon_hash, &ammo);
	WEAPON::GIVE_WEAPON_TO_PED(ped, weapon_hash, ammo, false, equip_now);

	if (fully_upgraded) {
		upgrade_weapon_components(ped, weapon_hash);
	}
} 

const char* give_components[] = {
	"Current", "All"
}; std::size_t give_components_id = 0;

const char* remove_components[] = {
	"Current", "All"
}; std::size_t remove_components_id = 0;

const char* give_ammo[] = {
	"Current", "All"
}; std::size_t give_ammo_id = 0;

const char* remove_ammo[] = {
	"Current", "All"
}; std::size_t remove_ammo_id = 0;

const char* remove_weapons[] = {
	"Current", "All"
}; std::size_t remove_weapons_id = 0;

namespace menu {
	void weapon_menu::render() {
		renderer::addSubmenu("Weapons", [](core* core) {

			core->add_option(submenu_option("Weapon Mods"));
			core->add_option(submenu_option("Weapon Mangement"));
			core->add_option(submenu_option("Tint Mangement"));

			core->add_option(break_option("Quick Access"));

			core->add_option(button_option("Give All Weapons")
				.add_click([] {
					for (const auto& weapon : lists::g_weapons) {
						give_weapon(PLAYER::PLAYER_PED_ID(), weapon.id, true, false);
					}
				}));

			core->add_option(scroll_option<const char*, std::size_t>("Remove Weapons")
				.add_array(&remove_weapons).set_position(&remove_weapons_id)
				.add_click([] {
					uint32_t hash;
					switch (remove_weapons_id) {
					case 0:
						if (Util::is_key_pressed(VK_RETURN)) {
							WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &hash, 0));
						}
						break;
					case 1:
						if (Util::is_key_pressed(VK_RETURN)) {
							WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), 0);
						}
						break;
					}
				}));

			core->add_option(scroll_option<const char*, std::size_t>("Give Ammo")
				.add_array(&give_ammo).set_position(&give_ammo_id)
				.add_click([] {
					uint32_t hash;
					int ammo = -1;
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &hash, 0), &ammo);
					switch (give_ammo_id) {
					case 0:
						if (Util::is_key_pressed(VK_RETURN)) {
							WEAPON::REFILL_AMMO_INSTANTLY(PLAYER::PLAYER_PED_ID());
						}

						break;
					case 1:
						if (Util::is_key_pressed(VK_RETURN)) {
							for (const auto& weapon : lists::g_weapons) {
								WEAPON::ADD_AMMO_TO_PED(PLAYER::PLAYER_PED_ID(), weapon.id, ammo);
							}
						}
						break;
					}
				}));

			core->add_option(scroll_option<const char*, std::size_t>("Remove Ammo")
				.add_array(&remove_ammo).set_position(&remove_ammo_id)
				.add_click([] {
					uint32_t hash;
					int ammo = -1;
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &hash, 0), &ammo);
					switch (remove_ammo_id) {
					case 0:
						if (Util::is_key_pressed(VK_RETURN)) {
							WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &hash, 0), 0, 0);
						}

						break;
					case 1:
						if (Util::is_key_pressed(VK_RETURN)) {
							for (const auto& weapon : lists::g_weapons) {
								WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), weapon.id, 0, 0);
							}
						}
	
						break;
					}
				}));

			core->add_option(scroll_option<const char*, std::size_t>("Upgrade Components")
				.add_array(&give_components).set_position(&give_components_id)
				.add_click([] {
					uint32_t hash;
					int ammo = -1;
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &hash, 0), &ammo);
					switch (give_components_id) {
					case 0:
						if (Util::is_key_pressed(VK_RETURN)) {
							upgrade_weapon_components(PLAYER::PLAYER_PED_ID(), WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &hash, 0));
						}

						break;
					case 1:
						if (Util::is_key_pressed(VK_RETURN)) {
							for (const auto& weapon : lists::g_weapons) {
								upgrade_weapon_components(PLAYER::PLAYER_PED_ID(), weapon.id);
							}
						}

						break;
					}
				}));

			core->add_option(scroll_option<const char*, std::size_t>("Downgrade Components")
				.add_array(&remove_components).set_position(&remove_components_id)
				.add_click([] {
					uint32_t hash;
					int ammo = -1;
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &hash, 0), &ammo);
					switch (remove_components_id) {
					case 0:
						if (Util::is_key_pressed(VK_RETURN)) {
							remove_weapon_upgrades(PLAYER::PLAYER_PED_ID(), WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &hash, 0));
						}

						break;
					case 1:

						if (Util::is_key_pressed(VK_RETURN)) {
							for (const auto& weapon : lists::g_weapons) {
								remove_weapon_upgrades(PLAYER::PLAYER_PED_ID(), weapon.id);
							}
						}
						break;
					}
					}));
		});
	}

	void weapon_menu::update() {
		render();
	}
}