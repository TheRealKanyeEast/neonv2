#include "pch.h"
#include "position.h"
#include "gui/renderer.h"

using namespace base::gui;

namespace menu {
	void position_menu::render() {
		renderer::add_submenu("Position", [](core* core) {
			core->add_option(number_option<float>("Horizontal Position")
				.add_number(&renderer::renderer::get_renderer()->m_position.x).add_min(0).add_max(1)
				.add_step(0.01f).add_precision(2));

			core->add_option(number_option<float>("Vertical Position")
				.add_number(&renderer::renderer::get_renderer()->m_position.y).add_min(0).add_max(1)
				.add_step(0.01f).add_precision(2));
		});
	}

	void position_menu::update() {
		render();
	}
}