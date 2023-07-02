#include "pch.h"
#include "water.h"
#include "menu/util/control.h"

using namespace base::gui;
using namespace menu::world::water::vars;

namespace menu::world::water::vars {
	variables m_vars;



}

namespace menu {

	void water_menu::render() {
		renderer::addSubmenu("Water", "water/ocean", [](core* core) {
			core->addOption(toggleOption("Part Water")
				.addToggle(&m_vars.part_water));

			core->addOption(numberOption<float>("Wave Intensity")
				.addNumber(&m_vars.m_wave_intensity).addMin(0).addMax(10).addStep(0.1).setPrecision(1)
				.addClick([] { WATER::SET_DEEP_OCEAN_SCALER(m_vars.m_wave_intensity); }));

			core->addOption(buttonOption("Reset Wave Intensity")
				.addClick([] {WATER::RESET_DEEP_OCEAN_SCALER(); }));
		});
	}

	void water_menu::update() {
		render();

		static bool once = false;
		if (!once) {
			m_vars.m_wave_intensity = WATER::GET_DEEP_OCEAN_SCALER();
			once = true;
		}

		if (m_vars.part_water) {
			float offset[] = { -4, 4 };
			for (int i = 0; i < 5; i++) {
				Vector3 current_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				if (i < 2) current_coords.x += offset[(i % 2 == 0)];
				else if (i < 4) current_coords.y += offset[(i % 2 == 0)];
				WATER::MODIFY_WATER({ current_coords.x, current_coords.y }, -500000.0f, 0.2f);
			}
		}
	}
}