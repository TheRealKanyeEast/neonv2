#pragma once
#include "pch.h"
#include <functional>

namespace util::fiber {
	struct fiber_context {
		fiber_context* m_next = nullptr;
		void* m_handle = nullptr;
		uint32_t m_wake_time = 0;
		bool m_running = true;
		std::string m_name = "";
	};

	class fiber_manager {
	public:
		void load();
		void update();
		void add(std::string name, std::function<void()> function);
		void sleep(uint32_t time);
		void go_to_main();
		void cleanup();

		std::vector<fiber_context>& get_fibers() { return m_fibers; }
	private:
		bool m_loaded;
		void* m_main_fiber;
		fiber_context* m_current;
		std::vector<fiber_context> m_fibers;
	};

	fiber_manager* get_fiber_manager();

	inline void load() {
		get_fiber_manager()->load();
	}

	inline void update() {
		get_fiber_manager()->update();
	}

	inline void add(std::string name, std::function<void()> function) {
		get_fiber_manager()->add(name, function);
	}

	inline void sleep(uint32_t time) {
		get_fiber_manager()->sleep(time);
	}

	inline void go_to_main() {
		get_fiber_manager()->go_to_main();
	}

	inline void cleanup() {
		get_fiber_manager()->cleanup();
	}
}