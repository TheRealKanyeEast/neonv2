#include "pch.h"
#include "network.h"
#include "network/network_session.h"
#include "network/network_players.h"
#include "network/network_new_session.h"
#include "network/network_transitions.h"
using namespace base::gui;

namespace menu {

	void network_menu::render() {
		renderer::addSubmenu("Network", "Network", [](core* core) {
			core->addOption(submenuOption("Players")
				.setTarget("Network Players"));

			core->addOption(submenuOption("Session")
				.setTarget("Network Session"));

			core->addOption(submenuOption("Transitions")
				.setTarget("Network Transitions"));

			core->addOption(submenuOption("New Session")
				.setTarget("Network New Session"));
		});
	}

	void network_menu::update() {
		render();
		getNetworkPlayersMenu()->update();
		getNetworkSessionMenu()->update();
		getNetworkNewSessionMenu()->update();
		getNetworkTransitionsMenu()->update();
	}
}