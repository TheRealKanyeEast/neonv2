#include "pch.h"
#include "network.h"
#include "network/network_players.h"
using namespace base::gui;

namespace menu {

	void network_menu::render() {
		renderer::add_submenu("Network", [](core* core) {
			core->add_option(submenu_option("Players")
				.set_target("Players"));
		});
	}

	void network_menu::update() {
		render();
		getNetworkPlayersMenu()->update();
	}
}