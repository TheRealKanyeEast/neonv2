#include "pch.h"
#include "core.h"
#include "util/thread_pool.h"
#include "util/Log.h"
#include "hooks/hooks.h"
#include "util/hooking/hooking.h"
#include "features/manager/manager.h"
#include "hooks/patterns.h"
#include "rage/invoker/invoker.h"
#include "exception.h"
#include "rage/invoker/natives.h"
#include "util/hooking/script.h"
#include "util/fiber.h"
#include "util/dirs.h"
namespace base::core {


	DWORD WINAPI unload(LPVOID handle) {
		
		hooking::cleanup();
		util::threads::getThreadPool()->Cleanup();
		util::fiber::cleanup();
		features::clear();
		util::log::Cleanup();

		FreeLibraryAndExitThread(static_cast<HMODULE>(handle), 0);
	}

	DWORD WINAPI load(LPVOID handle) {
		AddVectoredExceptionHandler(0, exception::handler::exception_handler);
		
		if (!util::dirs::load()) {
			unload(handle);
		}

		util::log::Load();
		LOG_SUCCESS("Neon Initializing");

		if (!(g_window = FindWindowA(("grcWindow"), NULL))) {
			int timeout = 0;
			while (!g_window) {
				if (timeout >= 20) {
					LOG_ERROR(("Failed to find game window"));
					unload(handle);
					return 0;
				}

				g_window = FindWindowA(("grcWindow"), NULL);
				timeout++;
				Sleep(1000);
			}
		}

		if (!base::hooks::patterns()) {
			LOG_WARN("Failed to load patterns, unloading...");
			std::this_thread::sleep_for(6s);
			unload(handle);
		}

		while (*patterns::game_state != 0) {
			std::this_thread::sleep_for(3s);
			std::this_thread::yield();
		}

		if (!invoker::invoker::handlers_cached()) {
			invoker::invoker::cache_handlers();
		}

		if (!base::hooks::hooks()) {
			LOG_WARN("Failed to load hooks, unloading...");
			std::this_thread::sleep_for(6s);
			unload(handle);
		}

		auto script_hooks = std::make_unique<script::native_hooks>();

		g_running = true;

		LOG_SUCCESS("Neon Initialized");

		while (g_running) {
			if (GetAsyncKeyState(VK_END)) {
				g_running = false;
			}
		}

		script_hooks.reset();
		unload(handle);

	}
}