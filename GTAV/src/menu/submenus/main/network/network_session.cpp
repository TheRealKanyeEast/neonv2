#include "pch.h"
#include "network_session.h"
#include "rage/invoker/natives.h"
#include "gui/util/timer.h"
#include "menu/util/globals.h"
#include "rage/engine.h"
#include "gui/util/notify.h"
#include "rage/classes/rlSessionByGamerTaskResult.h"
#include "rage/classes/rlTaskStatus.h"
#include "util/caller.h"

#include "session/network_session_block_join.h"
#include "session/network_session_scripts.h"

using namespace base::gui;
using namespace menu::network::session::vars;

namespace menu::network::session::vars {
	variables m_vars;

	enum class eSessionType {
		JOIN_PUBLIC,
		NEW_PUBLIC,
		CLOSED_CREW,
		CREW,
		CLOSED_FRIENDS = 6,
		FIND_FRIEND = 9,
		SOLO,
		INVITE_ONLY,
		JOIN_CREW,
		SC_TV,
		LEAVE_ONLINE = -1
	};

	struct SessionType {
		eSessionType id;
		const char name[29];
	};

	const SessionType sessions[] = {
		{eSessionType::JOIN_PUBLIC, "Find Public Session"},
		{eSessionType::NEW_PUBLIC, "Find New Public Session"},
		{eSessionType::CLOSED_CREW, "Create Closed Crew Session"},
		{eSessionType::CREW, "Create Crew Session"},
		{eSessionType::CLOSED_FRIENDS, "Create Closed Friend Session"},
		{eSessionType::FIND_FRIEND, "Find Friend Session"},
		{eSessionType::SOLO, "Create Solo Session"},
		{eSessionType::INVITE_ONLY, "Create Invite Only Session"},
		{eSessionType::JOIN_CREW, "Find Crew Session"},
		{eSessionType::SC_TV, "Social Club TV"},
		{eSessionType::LEAVE_ONLINE, "Leave GTA Online"},
	};

	void join_type(eSessionType session) {
		util::fiber::pool::add([=] {
			*script_global(2695915).as<int*>() = (session == eSessionType::SC_TV ? 1 : 0);// If SC TV Then Enable Spectator Mode

			if (session == eSessionType::LEAVE_ONLINE)
				*script_global(1574589).at(2).as<int*>() = -1;
			else
				*script_global(1575017).as<int*>() = (int)session;

			*script_global(1574589).as<int*>() = 1;
			util::fiber::go_to_main();
			*script_global(1574589).as<int*>() = 0;
			});
	}

	void join_session(const rage::rlSessionInfo& info)
	{
		m_vars.join_queued = true;
		m_vars.info = info;
		join_type({ eSessionType::NEW_PUBLIC });
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) == 0) {
			m_vars.join_queued = false;
		}
		return;
	}

	void join_by_rockstar_id(uint64_t rid) {
		util::fiber::pool::add([=] {
			if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) != 0 || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
				menu::notify::stacked("Unable to join player");
				return;
			}

			rage::rlGamerHandle player_handle(rid);
			rage::rlSessionByGamerTaskResult result;
			bool success = false;
			rage::rlTaskStatus state{};

			if (caller::call<uint64_t>(patterns::start_get_session_by_gamer_handle, 0, &player_handle, 1, &result, 1, &success, &state)) {
				while (state.status == 1)
					util::fiber::go_to_main();

				if (state.status == 3 && success) {
					join_session(result.m_session_info);
					return;
				}
			}

			menu::notify::stacked("Unable to join player, player is offline");

		});
	}
	static bool active = false;
	void join_via_rid() {
		util::fiber::pool::add([=] {
			MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
			while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
				active = true;
				renderer::getRenderer()->reset_keys();
				util::fiber::go_to_main();
			}
			active = false;
			if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
				return;
			m_vars.rid_to_join = std::atoi(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
		});
	}

}


namespace menu {

	void network_session_menu::render() {
		renderer::addSubmenu("Session", "Network Session", [](core* core) {
			core->addOption(submenuOption("Session Scripts")
				.setTarget("Session Scripts"));

			core->addOption(submenuOption("Session Info")
				.setTarget("Session Info"));

			core->addOption(submenuOption("Kicked Players")
				.setTarget("Kicked Players"));

			core->addOption(submenuOption("Join Blocking")
				.setTarget("Session Block Join"));

			core->addOption(submenuOption("Join Bypass")
				.setTarget("Session Join Bypass"));

			core->addOption(submenuOption("Join Tools")
				.setTarget("Session Join Tools"));

			core->addOption(buttonOption("Become Script Host")
				.addClick([] { rage::engine::force_host(rage::joaat("freemode")); }));
		});

		renderer::addSubmenu("Kicked Players", "Kicked Players", [](core* core) {
			int numBlacklistedPlayers = 16 - (*patterns::network)->m_blacklist.m_free_nodes;

			for (int i = 0; i < numBlacklistedPlayers; i++) {
				if (i > 0) {
					const CNetBlacklistNode& node = (*patterns::network)->m_blacklist.m_nodes[i];
					core->addOption(buttonOption(std::to_string(node.m_handle.m_rockstar_id).c_str()));
				}
				else {
					core->addOption(buttonOption("~c~Empty"));
				}
			}
		});

		renderer::addSubmenu("Session Info", "Session Info", [](core* core) {
			if (*patterns::is_session_started) {
				char buf[0x100]{};
				const auto& info = (*patterns::network)->m_game_session;
				std::string session_info = std::format("{}", caller::call<uint64_t>(patterns::encode_session_info,  &info.m_rline_session.m_session_info, buf, 0xA9, nullptr));
				std::string session_id = std::format("{}", info.m_rline_session.m_session_id);
				std::string token_key = std::format("{}", info.m_token_key);

				core->addOption(buttonOption("Session Info: ")
					.addRightText(session_info.c_str()));

				core->addOption(buttonOption("Session ID: ")
					.addRightText(session_id.c_str()));

				core->addOption(buttonOption("Token Key: ")
					.addRightText(session_id.c_str()));
			}
			else {
				core->addOption(buttonOption("~c~Offline"));
			}
		});

		renderer::addSubmenu("Join Tools", "Session Join Tools", [](core* core) {
			core->addOption(submenuOption("Join by RID")
				.setTarget("join_by_rid"));

			core->addOption(submenuOption("Join by Session")
				.setTarget("join_by_session"));

		});

		renderer::addSubmenu("Join by Session", "join_by_session", [](core* core) {
			core->addOption(keyboard_option("Enter Session id")
				.add_right_text(std::to_string(m_vars.rid_to_join).c_str())
				.add_click([] { join_via_rid(); }));

			core->addOption(buttonOption("Join")
				.addClick([] { join_by_rockstar_id(m_vars.rid_to_join); }));
		});

		renderer::addSubmenu("Join by RID", "join_by_rid", [](core* core) {
			core->addOption(keyboard_option("Enter Rid")
				.add_right_text(std::to_string(m_vars.rid_to_join).c_str())
				.add_click([] { join_via_rid(); }));

			core->addOption(buttonOption("Join")
				.addClick([] { join_by_rockstar_id(m_vars.rid_to_join); }));
		});

		renderer::addSubmenu("Join Bypass", "Session Join Bypass", [](core* core) {
			static bool invite_only = true;
			static bool friend_only = true;
			static bool crew_only = true;

			core->addOption(toggleOption("Invite Only")
				.addToggle(&invite_only));

			core->addOption(toggleOption("Friend Only")
				.addToggle(&friend_only));

			core->addOption(toggleOption("Crew Only")
				.addToggle(&crew_only));
		});

	}


	void network_session_menu::update() {
		render();
		getSessionBlockJoinMenu()->update();
		getSessionScriptsMenu()->update();
	}

}