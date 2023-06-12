#include "pch.h"
#include "spawner_settings.h"

using namespace base::gui;

using namespace menu::spawner::settings::vars;

namespace menu::spawner::settings::vars {
	variables m_vars;

}

namespace menu {

	void spawner_settings_menu::render() {
		renderer::addSubmenu("Spawner Settings", [](core* core) {
			core->add_option(toggle_option("Notification")
				.add_toggle(&m_vars.m_notification));

			core->add_option(toggle_option("Blip")
				.add_toggle(&m_vars.m_blip));

			core->add_option(toggle_option("Particle FX")
				.add_toggle(&m_vars.m_particle_fx));

			core->add_option(toggle_option("Teleport Inside")
				.add_toggle(&m_vars.m_teleport_inside));

			core->add_option(toggle_option("Godmode")
				.add_toggle(&m_vars.m_godmode));

			core->add_option(toggle_option("Fade")
				.add_toggle(&m_vars.m_fade));

			core->add_option(toggle_option("Air Vehicles In Air")
				.add_toggle(&m_vars.m_air_vehicles_in_air));

			core->add_option(number_option<float>("Air Vehicles Height")
				.add_number(&m_vars.m_spawn_height).add_step(1.f).add_precision(0)
				.add_min(0.f).add_max(1000.f));

			core->add_option(toggle_option("Delete Current")
				.add_toggle(&m_vars.m_delete_current));
		});
	}

	void spawner_settings_menu::update() {
		render();
	}
};

