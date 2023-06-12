#include "pch.h"
#include "color.h"
#include "gui/renderer.h"
#include "rage/classes/joaat.h"
#include "util/log.h"
#include "gui/util/fonts.h"
#include "gui/util/texture.h"
#include "gui/util/panels.h"
#include "gui/util/notify.h"

using namespace base::gui;

namespace menu {

	void color_menu::render() {

		renderer::addSubmenu("Color", [](core* core) {	
			core->add_option(color_option("Header Color", renderer::getRenderer()->m_header.m_color)
				.set_target("Header Color"));

			core->add_option(color_option("Header Text Color", renderer::getRenderer()->m_header.m_text_color)
				.set_target("Header Text Color"));

			core->add_option(color_option("Title Color", renderer::getRenderer()->m_title.m_color)
				.set_target("Title Color"));

			core->add_option(color_option("Title Text Color", renderer::getRenderer()->m_title.m_text_color)
				.set_target("Title Text Color"));

			core->add_option(color_option("Background Color", renderer::getRenderer()->m_option.m_color)
				.set_target("Background Color"));

			core->add_option(color_option("Scroller Color", renderer::getRenderer()->m_scroller_color)
				.set_target("Scroller Color"));

			core->add_option(color_option("Scroller Text Color", renderer::getRenderer()->m_option.m_color)
				.set_target("Scroller Text Color"));

			core->add_option(color_option("Scroller Selected Text Color", renderer::getRenderer()->m_option.m_selected_text_color)
				.set_target("Scroller Text Color"));

			core->add_option(color_option("Footer Color", renderer::getRenderer()->m_footer.m_color)
				.set_target("Footer Color"));

			core->add_option(color_option("Footer Text Color", renderer::getRenderer()->m_footer.m_text_color)
				.set_target("Footer Text Color"));
		});

		renderer::addSubmenu("Footer Color", [](core* core) {
			core->add_option(number_option<int>("[R]ed")
				.add_number(&renderer::getRenderer()->m_footer.m_color.r)
				.add_min(0).add_max(255));

			core->add_option(number_option<int>("[G]reen")
				.add_number(&renderer::getRenderer()->m_footer.m_color.g)
				.add_min(0).add_max(255));

			core->add_option(number_option<int>("[B]lue")
				.add_number(&renderer::getRenderer()->m_footer.m_color.b)
				.add_min(0).add_max(255));
		});

		renderer::addSubmenu("Scroller Color", [](core* core) {
			core->add_option(number_option<int>("[R]ed")
				.add_number(&renderer::getRenderer()->m_scroller_color.r)
				.add_min(0).add_max(255));

			core->add_option(number_option<int>("[G]reen")
				.add_number(&renderer::getRenderer()->m_scroller_color.g)
				.add_min(0).add_max(255));

			core->add_option(number_option<int>("[B]lue")
				.add_number(&renderer::getRenderer()->m_scroller_color.b)
				.add_min(0).add_max(255));
		});

		renderer::addSubmenu("Background Color", [](core* core) {
			core->add_option(number_option<int>("[R]ed")
				.add_number(&renderer::getRenderer()->m_option.m_color.r)
				.add_min(0).add_max(255));

			core->add_option(number_option<int>("[G]reen")
				.add_number(&renderer::getRenderer()->m_option.m_color.g)
				.add_min(0).add_max(255));

			core->add_option(number_option<int>("[B]lue")
				.add_number(&renderer::getRenderer()->m_option.m_color.b)
				.add_min(0).add_max(255));
		});

		renderer::addSubmenu("Title Color", [](core* core) {
			core->add_option(number_option<int>("[R]ed")
				.add_number(&renderer::getRenderer()->m_title.m_color.r)
				.add_min(0).add_max(255));

			core->add_option(number_option<int>("[G]reen")
				.add_number(&renderer::getRenderer()->m_title.m_color.g)
				.add_min(0).add_max(255));

			core->add_option(number_option<int>("[B]lue")
				.add_number(&renderer::getRenderer()->m_title.m_color.b)
				.add_min(0).add_max(255));
		});

		renderer::addSubmenu("Header Color", [](core* core) {
			core->add_option(number_option<int>("[R]ed")
				.add_number(&renderer::getRenderer()->m_header.m_color.r)
				.add_min(0).add_max(255));

			core->add_option(number_option<int>("[G]reen")
				.add_number(&renderer::getRenderer()->m_header.m_color.g)
				.add_min(0).add_max(255));

			core->add_option(number_option<int>("[B]lue")
				.add_number(&renderer::getRenderer()->m_header.m_color.b)
				.add_min(0).add_max(255));
		});

	}

	void color_menu::update() {
		render();
	}
}