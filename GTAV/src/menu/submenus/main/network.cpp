#include "pch.h"
#include "network.h"
#include "network/network_players.h"
using namespace base::gui;

namespace menu {

	void network_menu::render() {
		renderer::addSubmenu("Network", "Network", [](core* core) {
			core->addOption(submenuOption("Players")
				.setTarget("Network Players"));
		});
	}

	void network_menu::update() {
		render();
		getNetworkPlayersMenu()->update();
	}
}