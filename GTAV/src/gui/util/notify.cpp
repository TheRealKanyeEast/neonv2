#include "pch.h"
#include "notify.h"
#include "rage/invoker/natives.h"
#include "gui/renderer.h"
#include "util/log.h"
#include "util/util.h"
#include "gui/render.h"
namespace menu::notify {


	void notify::update() {

		float current = 0.f;
		for (auto context = m_context.begin(); context != m_context.end(); context++) {
			float wrap = 0.1362f;
			float x_offset = 0.01f;
			float text_height = 0.2f;

			if (context->m_has_init) {
				continue;
			}

			context->m_has_init = true;

			if (context->m_text.size() == 1) {
				HUD::SET_TEXT_FONT(0);
				HUD::SET_TEXT_SCALE(0.f, text_height);
				HUD::SET_TEXT_WRAP(context->x + x_offset, wrap);
				HUD::BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(context->m_text[0].c_str());

				context->m_lines = HUD::END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING({ context->x + x_offset, 0.015f });
				current += (context->m_lines * HUD::GET_RENDERED_CHARACTER_HEIGHT(text_height, 0)) + (context->m_lines * x_offset) + (x_offset * 3.f);
			}
			else {
				context->m_max_width = render::calculate_string_width(context->m_text[0], 0, text_height) + (x_offset * 2.f);

				for (std::size_t i = 0; i < context->m_text.size(); i++) {
					std::string str = context->m_text[i];

					float width = render::calculate_string_width(str, 0, text_height) + (x_offset * 2.f);
					if (context->m_max_width < width) {
						context->m_max_width = width;
					}
				}

				context->m_lines = (int)context->m_text.size();
				current += (context->m_lines * HUD::GET_RENDERED_CHARACTER_HEIGHT(text_height, 0)) + (context->m_lines * x_offset) + (x_offset * 3.f);
			}

			current += 0.004f;
			context->m_y = -current;
		}

		float y = 0.01f;
		for (auto context = m_context.rbegin(); context != m_context.rend(); context++) {
			float x_offset = 0.003f;
			float wrap = context->m_max_width + x_offset;
			float text_height = 0.2f;
			float height = (text_height / 10.f) + ((text_height * 1.1f) / 10.f);
			bool death = false;

			float scaled_body_height = render::get_normalized_font_scale(0, text_height);
			float scaled_title_height = render::get_normalized_font_scale(0, text_height * 1.1f);

			// nearing death, slide out
			uint32_t end_time = context->m_start_time + context->m_time_limit;
			if (end_time < GetTickCount() || end_time - GetTickCount() < 1000) {
				death = true;
				context->m_y = math::lerp(context->m_y, 1.2f, 5.f * renderer::getRenderer()->m_delta);

				if (context->m_alpha_start == 0) context->m_alpha_start = GetTickCount();
				context->m_alpha = 255 - (((GetTickCount() - context->m_alpha_start) * 255) / 1000);
			}
			else {
				if (context->m_title_width > context->m_max_width) {
					wrap = context->m_title_width + x_offset;
				}
			}

			if (context->m_title_width == 0.f) {
				context->m_title_width = render::calculate_string_width("~bold~" + context->m_title, 0, scaled_title_height) + (0.004f * 2.f);
			}

			// if it has one bit of text, calculate the lines
			if (context->m_text.size() == 1) {
				HUD::SET_TEXT_FONT(0);
				HUD::SET_TEXT_SCALE(scaled_body_height, scaled_body_height);
				HUD::SET_TEXT_WRAP(context->x, wrap - x_offset);
				HUD::BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(context->m_text[0].c_str());

				context->m_lines = HUD::END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING({ context->x, y + 0.005f });
				context->m_rendering_text = context->m_text[0];

				if (context->m_lines > 1) {
					height = (context->m_lines * HUD::GET_RENDERED_CHARACTER_HEIGHT(scaled_body_height, 0)) + 0.034f;
				}
				else {
					context->m_max_width = render::calculate_string_width(context->m_text[0], 0, scaled_body_height) + (x_offset * 2.f);
				}
			}
			else {
				// its a list of lines, calculate the longest line and use that as the width
				std::string full_line = "";
				context->m_max_width = render::calculate_string_width(context->m_text[0], 0, scaled_body_height) + (x_offset * 2.f);

				for (std::size_t i = 0; i < context->m_text.size(); i++) {
					std::string str = context->m_text[i];

					float width = render::calculate_string_width(str, 0, scaled_body_height) + (x_offset * 2.f);
					if (context->m_max_width < width) {
						context->m_max_width = width;
					}

					full_line += str;

					if (i != (context->m_text.size() - 1)) {
						full_line += '\n';
					}
				}

				context->m_lines = (int)context->m_text.size();
				context->m_rendering_text = full_line;
				height = (context->m_lines * HUD::GET_RENDERED_CHARACTER_HEIGHT(scaled_body_height, 0)) + 0.034f;
			}

			if (context->m_text.size() == 4) {
				height += 0.002f;
			}

			// lerp the Y position to account for new notifies
			if (!death) {
				context->m_y = math::lerp(context->m_y, y, 5.f * renderer::getRenderer()->m_delta);
			}

			if (context->m_y + height > 0.7f) {
				context->m_time_limit = 0;
			}

			if (context->m_y <= 1.f) {
				HUD::CLEAR_HELP(true);
				HUD::CLEAR_ALL_HELP_MESSAGES();

				int rect_alpha = context->m_alpha >= 35 ? context->m_alpha - 35 : 0;
				std::pair<std::string, std::string> texture = { "re", "re" };
				render::draw_sprite_aligned(texture, { context->x, context->m_y }, { context->m_max_width, height }, 0.f, m_notify_background.opacity(rect_alpha));

				render::draw_sprite_aligned(texture, { context->x, context->m_y }, { 0.002f, height }, 0.f, context->m_color.opacity(rect_alpha));

				math::vector2<float> text_wrap = context->m_text.size() > 1 ? math::vector2<float>(0.f, 1.f) : math::vector2<float>(context->x, wrap);
				render::draw_text2(context->m_rendering_text, { context->x + x_offset, context->m_y + 0.02f + 0.001f }, scaled_body_height, 0, { 255, 255, 255, 255 }, JUSTIFY_LEFT, text_wrap);
				render::draw_text2("~bold~" + context->m_title, { context->x + x_offset, context->m_y + 0.003f + 0.001f }, scaled_title_height, 0, { 255, 255, 255, 255 }, JUSTIFY_LEFT);
				y += height + 0.004f;
			}
		}

		for (auto context = m_context.begin(); context != m_context.end();) {
			if (context->m_start_time + context->m_time_limit < GetTickCount()) {
				context = m_context.erase(context);
				continue;
			}

			context++;
		}
	}

	void notify::stacked(std::string title, std::string text, color color, uint32_t timeout) {
		notify_context context;
		context.m_text.push_back(text);
		context.m_title = title;
		context.m_color = color;
		context.m_start_time = GetTickCount();
		context.m_time_limit = timeout;

		LOG_CUSTOM(title.c_str(), text.c_str());
		m_context.push_back(context);
	}

	void notify::stacked_lines(std::string title, std::vector<std::string> text, color color) {
		notify_context context;
		for (std::string str : text) context.m_text.push_back(str);

		context.m_title = title;
		context.m_color = color;
		context.m_start_time = GetTickCount();
		context.m_time_limit = 6000;

		m_context.push_back(context);
	}

	void notify::protection(std::string sender, std::string event, bool redirected, bool blocked) {
		
	}

	void notify::subtitle(const char* msg) {
		HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
		HUD::END_TEXT_COMMAND_PRINT(3000, true);
	}

	notify* get_notify() {
		static notify instance;
		return &instance;
	}
}