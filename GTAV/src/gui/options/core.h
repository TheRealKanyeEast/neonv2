#pragma once
#include "submenu.h"
#include "rage/classes/joaat.h"
namespace base::gui {
	class core : public base_submenu<core> {
	public:
		explicit core(const char* name, std::function<void(core*)> action) {
			set_name(name); set_id(rage::joaat(name)); set_action(std::move(action));
		}
	};
}