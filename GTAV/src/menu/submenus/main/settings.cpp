#include "pch.h"
#include "settings.h"
#include "gui/renderer.h"
#include "util/log.h"
#include "settings/position.h"
#include "settings/color.h"
using namespace base::gui;

namespace menu {
	void settings_menu::render() {
		renderer::addSubmenu("Settings", [](core* core) {
			core->add_option(submenu_option("Position")
				.set_target("Position"));

			core->add_option(submenu_option("Color")
				.set_target("Color"));

			core->add_option(button_option("Unload")
				.add_click([] { g_running = false; }));
		});
	}

	void settings_menu::update() {
		render();
		getPositionMenu()->update();
		getColorMenu()->update();
	}
}