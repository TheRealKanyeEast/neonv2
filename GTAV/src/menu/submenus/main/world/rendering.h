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
	class rendering_menu {
	public:
		void render();
		void update();
	};

	static rendering_menu* getRenderingMenu() {
		static rendering_menu instance;
		return &instance;
	}

	namespace world::rendering::vars {

		struct variables {
			bool m_see_through_walls;
			bool decrease_graphics;
			bool blackout;
			bool thermal_vision;
			bool night_vision;
			bool render_hd_only;
			float distance_scaling = 1.00f;
		};

		extern variables m_vars;
	}
}