#pragma once

#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"
#include "gui/options/break.h"
#include "gui/util/rainbow.h"
namespace menu {
	class water_menu {
	public:
		void render();
		void update();
	};

	static water_menu* getWaterMenu() {
		static water_menu instance;
		return &instance;
	}

	namespace world::water::vars {

		struct variables {
			float m_wave_intensity;
			bool part_water;
		};

		extern variables m_vars;
	}
}