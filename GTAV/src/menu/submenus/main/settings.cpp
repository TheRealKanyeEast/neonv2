#include "pch.h"
#include "settings.h"
#include "gui/renderer.h"
#include "util/log.h"
#include "settings/position.h"
#include "settings/color.h"
#include "settings/hotkeys.h"
using namespace base::gui;

namespace menu {
	void settings_menu::render() {
		renderer::addSubmenu("Settings", [](core* core) {
			core->add_option(submenu_option("Hotkeys")
				.add_translate()
				.set_target("Hotkeys"));

			core->add_option(submenu_option("Position")
				.add_translate()
				.set_target("Position"));

			core->add_option(submenu_option("Color")
				.add_translate()
				.set_target("Color"));

			core->add_option(button_option("Unload")
				.add_translate()
				.add_click([] { g_running = false; }));
		});
	}

	void settings_menu::update() {
		render();
		getPositionMenu()->update();
		getColorMenu()->update();
		getHotkeysMenu()->update();
	}
}