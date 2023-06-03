#include "pch.h"
#include "hooks/hooks.h"
#include "rage/classes/scrNativeCallContext.h"
#include "rage/invoker/natives.h"
#include "menu/submenus/main.h"
#include "menu/submenus/main/settings.h"
#include "menu/submenus/main/player.h"
#include "menu/submenus/main/spawner.h"
#include "menu/submenus/main/network.h"
#include "util/fiber.h"
#include "features/features.h"
#include "gui/util/fonts.h"
#include "gui/util/panels.h"
namespace base::hooks {
	void stat_get_int(rage::scrNativeCallContext* context) {
		static bool call_once_loaded = false;
		static int frame_cache = 0;
		static uint32_t this_frame = 0;
		static uint32_t last_frame = 0;

		if (frame_cache < MISC::GET_FRAME_COUNT()) {
			frame_cache = MISC::GET_FRAME_COUNT();
			if (!call_once_loaded) {
				try {
					call_once_loaded = true;

					util::fiber::load();
					fonts::load();

					util::fiber::add("F_MENU", [] {
						menu::getMainMenu()->update();
						menu::getSettingsMenu()->update();
						menu::getPlayerMenu()->update();
						menu::getSpawnerMenu()->update();
						menu::getNetworkMenu()->update();
					});

					

				}
				catch (std::exception& exception) {
					LOG("Exception initializing menu: %s", exception.what());
				}
			} 

			if (g_running && call_once_loaded) {
				util::fiber::update();
			}
		}

		context->set_return_value(STATS::STAT_GET_INT(context->get_arg<Hash>(0), context->get_arg<int*>(1), context->get_arg<int>(2)));
	}
}