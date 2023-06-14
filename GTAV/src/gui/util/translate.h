#pragma once
#include "util/json.h"
#include "timer.h"
#include "rage/classes/joaat.h"
#include "util/util.h"

namespace base::gui
{
	class translationManager
	{
	public:
		void init();

		void loadTranslation(const char* name);
		const char* getTranslation(uint32_t label);

		
	private:
		std::unordered_map<std::uint32_t, std::string> m_translations;
		std::filesystem::path m_path{ Util::GetDocumentsPath() };
	};

	static translationManager* getTranslationManager() {
		static translationManager instance;
		return &instance;
	}
}

#define TRANSLATE_IMPL(label) (::base::gui::getTranslationManager()->getTranslation(rage::joaat(label)))
#define TRANSLATE(label) TRANSLATE_IMPL(label)