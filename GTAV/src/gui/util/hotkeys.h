#pragma once
#include "pch.h"

namespace menu {
	struct hotkey_context {
		int m_key;
	};
	class hotkey {
	public:
		void update();
		void read_hotkey();
		void register_hotkey(int key);
		void unregister_hotkey();

		std::vector<hotkey_context>& get_hotkeys() { return m_hotkeys; }
	private:
		std::vector<hotkey_context> m_hotkeys;
	};

	hotkey* get_hotkey();

	inline void update() {
		get_hotkey()->update();
	}


}
