#include "pch.h"
#include "hotkeys.h"
#include "gui/renderer.h"
#include "gui/util/notify.h"
#include "gui/util/panels.h"
using namespace base::gui;

namespace menu {
	void hotkeys_menu::render() {
		renderer::addSubmenu("Hotkeys", [](core* core) {
			core->add_option(button_option("Save")
				.add_click([] { renderer::getRenderer()->save_hotkeys(); }));

			core->add_option(button_option("Reload")
				.add_click([] { renderer::getRenderer()->load_hotkeys(); }));

			core->add_option(break_option("Hotkeys"));

			if (!renderer::getRenderer()->m_bool_hotkeys.empty()) {
				for (auto pair : renderer::getRenderer()->m_bool_hotkeys) {
					std::string display = std::format("{}({})", g_key_names[pair.second.m_key], pair.second.m_name);
					core->add_option(button_option(display.c_str()));
				}
			}
			else {
				core->add_option(button_option("~c~Empty"));
			}
		});
	}

	void hotkeys_menu::update() {
		render();
	}
}