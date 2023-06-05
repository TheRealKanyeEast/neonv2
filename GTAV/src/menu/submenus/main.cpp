#include "pch.h"
#include "main.h"
#include "gui/renderer.h"
#include "rage/classes/joaat.h"
#include "util/log.h"
#include "gui/util/fonts.h"
#include "gui/util/panels.h"
#include "gui/util/notify.h"

using namespace base::gui;

namespace menu {
	void main_menu::render() {	

		renderer::add_submenu("Neon", [](core* core) {
			core->add_option(submenu_option("Player")
				.set_target("Player"));

			core->add_option(submenu_option("Network")
				.set_target("Network"));

			core->add_option(submenu_option("Spawner")
				.set_target("Spawner"));

			core->add_option(submenu_option("Settings")
				.set_target("Settings"));

			core->add_option(button_option("Test")
				.add_click([] { notify::stacked("Test Notification", "Txl and Stash are lovers"); }));
		});

	}

	void main_menu::update() {
		fonts::update_queue();
		renderer::getRenderer()->render();
		render();
	}
}