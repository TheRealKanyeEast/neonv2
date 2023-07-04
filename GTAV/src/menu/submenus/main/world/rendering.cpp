#include "pch.h"
#include "rendering.h"
#include "menu/util/control.h"

using namespace base::gui;
using namespace menu::world::rendering::vars;

namespace menu::world::rendering::vars {
	variables m_vars;



}

namespace menu {

	void rendering_menu::render() {
		renderer::addSubmenu("Rendering", "game_rendering", [](core* core) {
			core->addOption(submenuOption("Visual Settings")
				.setTarget("visual_settings"));

			core->addOption(toggleOption("Night Vision")
				.addToggle(&m_vars.night_vision));

			core->addOption(toggleOption("Thermal Vision")
				.addToggle(&m_vars.thermal_vision));

			core->addOption(toggleOption("See Through Walls")
				.addToggle(&m_vars.m_see_through_walls).addTooltip("See through walls when aiming"));

			core->addOption(numberOption<float>("Distance Scaling")
				.addNumber(&m_vars.distance_scaling).addMin(1.00f).addMax(200.0f).addStep(0.01f).setPrecision(2));

			core->addOption(numberOption<float>("Fog on Map")
				.addNumber(&patterns::game_visuals->m_fog_level).addMin(0).addMax(10).addStep(0.0001).setPrecision(4));

			core->addOption(toggleOption("Render HD Only")
				.addToggle(&m_vars.render_hd_only));

			core->addOption(toggleOption("Potato Mode")
				.addToggle(&m_vars.decrease_graphics));
		});

		renderer::addSubmenu("Visual Settings", "visual_settings", [](core* core) {
			core->addOption(numberOption<float>("Shadow Light")
				.addNumber(&patterns::visual_settings->m_shadow_light).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Reflection")
				.addNumber(&patterns::visual_settings->m_reflection).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Gamma")
				.addNumber(&patterns::visual_settings->m_gamma).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Near Blur")
				.addNumber(&patterns::visual_settings->m_blur).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Far Blur")
				.addNumber(&patterns::visual_settings->m_blur2).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Sky Intensity")
				.addNumber(&patterns::visual_settings->m_sky_intensity).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Saturation")
				.addNumber(&patterns::visual_settings->m_saturation).addMin(-100).addMax(100).addStep(1).setPrecision(0));
		});
	}

	void rendering_menu::update() {
		render();
		if (m_vars.m_see_through_walls) {
			CAM::SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(418.490f);
		}

		STREAMING::OVERRIDE_LODSCALE_THIS_FRAME(m_vars.distance_scaling);

		if (m_vars.night_vision) {
			*script_global(1853988).at(PLAYER::PLAYER_ID(), 862).at(823).at(13).as<int*>() = -1;
			GRAPHICS::SET_NIGHTVISION(true);
		}
		else {
			GRAPHICS::SET_NIGHTVISION(false);
		}

		if (m_vars.thermal_vision) {
			*script_global(1853988).at(PLAYER::PLAYER_ID(), 862).at(823).at(13).as<int*>() = -1;
			GRAPHICS::SET_SEETHROUGH(true);
		}
		else {
			GRAPHICS::SET_SEETHROUGH(false);
		}

		if (m_vars.render_hd_only) {
			STREAMING::SET_RENDER_HD_ONLY(true);
		}
		else {
			STREAMING::SET_RENDER_HD_ONLY(false);
		}
		
	}
}