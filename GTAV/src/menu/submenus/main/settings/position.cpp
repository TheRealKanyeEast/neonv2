#include "pch.h"
#include "position.h"
#include "gui/renderer.h"
#include "gui/util/notify.h"
#include "gui/util/panels.h"
using namespace base::gui;

namespace menu {
	void position_menu::render() {
		renderer::addSubmenu("Position", [](core* core) {
			core->add_option(number_option<float>("Horizontal Position")
				.add_number(&renderer::getRenderer()->m_position.x).add_min(0).add_max(1)
				.add_step(0.01f).add_precision(2));

			core->add_option(number_option<float>("Vertical Position")
				.add_number(&renderer::getRenderer()->m_position.y).add_min(0).add_max(1)
				.add_step(0.01f).add_precision(2));

			core->add_option(number_option<float>("Wrap")
				.add_tooltip("Hotkeys Supported. Press F12 to bind. Test test estsetssssssss testestes tse setse tsetes tse test sets etset estset setsetsetests").add_number(&renderer::getRenderer()->m_wrap).add_min(-1).add_max(1)
				.add_step(0.001f).add_precision(3));
		});
	}

	void position_menu::update() {
		render();
	}
}