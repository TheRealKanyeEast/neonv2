#include "pch.h"
#include "features.h"
#include "features/manager/manager.h"
#include "rage/invoker/natives.h"
#include "util/fiber.h"
namespace features {

	void suicide(features::actionFeature* feature) {
		ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, 0);
	}

	void run() {
		features::g_manager.add(features::actionFeature("suicide", "suicide", suicide));
		"suicide"_AF->add_hotkey(VK_F8);
		features::g_manager.init();

		while (true) {
			features::g_manager.tick();
			util::fiber::go_to_main();
		}
	}
}