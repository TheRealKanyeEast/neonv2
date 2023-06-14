#include "pch.h"
#include "main.h"
#include "gui/renderer.h"
#include "rage/classes/joaat.h"
#include "util/log.h"
#include "gui/util/fonts.h"
#include "gui/util/texture.h"
#include "gui/util/panels.h"
#include "gui/util/notify.h"
using namespace base::gui;

namespace menu {

	std::string toLower(std::string data) {
		std::transform(data.begin(), data.end(), data.begin(), ::tolower);
		return data;
	}

	std::vector<base::gui::abstract_option*> SearchOptions(const std::string& str) {
		std::vector<base::gui::abstract_option*> results;
		renderer::getRenderer()->get_submenu_stack().top()->reset();

		for (auto& sub : renderer::getRenderer()->get_all_subs()) {
			for (std::size_t i = 0; i < sub->get_options_size(); i++) {
				auto option = sub->get_option(i);
				std::string optionName = toLower(option->get_left_text());
				if (optionName.find(str) != std::string::npos) {
					results.insert(results.end(), option);
				}
			}
		}

		return results;
	}

	void main_menu::render() {	

		renderer::addSubmenu("Main Menu", [](core* core) {
			core->add_option(submenu_option("Player")
				.add_translate()
				.set_target("Player"));

			core->add_option(submenu_option("Network")
				.add_translate()
				.set_target("Network"));

			core->add_option(submenu_option("Protections")
				.add_translate()
				.set_target("Protections"));

			core->add_option(submenu_option("Vehicle")
				.add_translate()
				.set_target("Vehicle"));

			core->add_option(submenu_option("Weapons")
				.add_translate()
				.set_target("Weapons"));

			core->add_option(submenu_option("Teleport")
				.add_translate()
				.set_target("Teleport"));

			core->add_option(submenu_option("Spawner")
				.add_translate()
				.set_target("Spawner"));

			core->add_option(submenu_option("World")
				.add_translate()
				.set_target("World"));

			core->add_option(submenu_option("Recovery")
				.add_translate()
				.set_target("Recovery"));

			core->add_option(submenu_option("Miscellaneous")
				.add_translate()
				.set_target("Miscellaneous"));

			core->add_option(submenu_option("Settings")
				.add_translate()
				.set_target("Settings"));

		});

	}

	void main_menu::update() {
		fonts::update_queue();
		menu::textures::tick();
		renderer::getRenderer()->render();
		render();
	}
}