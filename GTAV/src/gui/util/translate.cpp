#include "pch.h"
#include "translate.h"
#include "util/log.h"
#include "util/util.h"
namespace base::gui {

	void translationManager::loadTranslation(const char* name) {
		m_translations.clear();

		try {
			m_path.append("neon").append("translations");
			if (std::filesystem::exists(m_path)) {
				std::filesystem::directory_iterator it{ m_path };
				for (auto&& entry : it) {
					if (entry.is_regular_file()) {
						auto path{ entry.path()};
						std::ifstream file(path.filename().c_str());

						if (file.good()) {
							std::stringstream str;
							std::string line;
							while (std::getline(file, line)) {
								str << line << '\n';
							}

							nlohmann::json json = nlohmann::json::parse(str, nullptr, false);
							auto objects = json.get<std::unordered_map<std::string, nlohmann::json>>();

							for (auto&& [key, value] : objects) {
								m_translations.emplace(rage::joaat(key.c_str()), value.get<std::string>());
							}
							LOG("loaded %s", name);
						}
					}
				}
			}
		}
		catch (nlohmann::detail::exception const&) {
			LOG_WARN("failed to parse %s", name);
		}

	}

	const char* translationManager::getTranslation(uint32_t label) {
		if (auto it = m_translations.find(label); it != m_translations.end()) {
			return &(it->second)[0];
		}
		else {
			static char buf[64];
			std::fill(std::begin(buf), std::end(buf), '\0');
			std::snprintf(&buf[0], sizeof(buf) - 1, "Error (0x%08X)", label);
			return &buf[0];
		}
	}
}