#include "pch.h"
#include "spawner.h"
#include "hooks/patterns.h"
#include "rage/engine.h"
using namespace base::gui;

using namespace menu::spawner::vars;

namespace menu::spawner::vars {
	variables m_vars;
}

namespace menu {

	void spawner_menu::render() {

		renderer::add_submenu("Spawner", [](core* core) {
			for (std::int32_t i = 0; i < 23; i++) {
				core->add_option(submenu_option(rage::engine::get_vehicle_class_name(i))
					.add_click([=] { m_vars.m_selected_vehicle_class = i; })
					.set_target(rage::engine::get_vehicle_class_name(m_vars.m_selected_vehicle_class)));
			}
		});

		renderer::add_submenu(rage::engine::get_vehicle_class_name(m_vars.m_selected_vehicle_class), [](core* core) {

			if (patterns::hash_list != nullptr) {
				for (std::int32_t i = 0; i < patterns::hash_list->capacity; i++) {
					std::uint64_t info = patterns::hash_list->get(i);
					if (info != NULL) {
						if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
							std::string make_ptr = (char*)((uintptr_t)info + 0x2A4);
							std::string model_ptr = (char*)((uintptr_t)info + 0x298);
							if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(rage::joaat(model_ptr)) == m_vars.m_selected_vehicle_class) {
								std::stringstream ss;
								std::string make(make_ptr);
								std::string model(model_ptr);
								if (make[0] || model[0]) {
									make = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(make.c_str());
									model = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(model.c_str());
									if (make != "NULL" && model != "NULL") {
										ss << make << " " << model;
									}
									else if (model != "NULL") {
										ss << model;
									}
									else {
										ss << "Unknown";
									}
								}
								core->add_option(button_option(ss.str().c_str())
									.add_click([&] { rage::engine::spawn_vehicle(*(std::uint32_t*)(info + 0x18)); }));
								}
							}
						}
					}
				}

		});
	}
	
	void spawner_menu::update() {
		render();
	}

}