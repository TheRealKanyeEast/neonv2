#pragma once
#include "pch.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "rage/invoker/natives.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
namespace rage::engine {
	inline rage::types::store_module* get_store_module_extension(const char* extension) {
		return caller::call<rage::types::store_module*>(patterns::get_store_module_extension, &patterns::store_manager->m_module, extension);
	}

	inline uint64_t construct_gfx_font(uint64_t allocation) {
		return caller::call<uint64_t>(patterns::construct_gfx_font, allocation);
	}

	inline void destruct(uint64_t allocation) {
		caller::call<void>(patterns::destruct, allocation);
	}

	inline int create_id_for_font(const char* asset_name) {
		static uint8_t junk[2][0x100];
		memset(junk, 0, sizeof(junk));

		return caller::call<int>(patterns::create_id_for_font, asset_name, junk[0], junk[1], 0, -1, -1, 1, 2, 0, 0);
	}

	inline void add_font_lib(uint64_t allocation, int index) {
		rage::types::store_module* store = get_store_module_extension("gfx");
		caller::call<void>(patterns::add_font_lib, store, allocation, index - store->m_base_index);
	}


	inline void request_streaming_file(int index) {
		caller::call<void>(patterns::request_streaming_file, patterns::store_manager, index, 7);
	}

	inline int register_streaming_file(const char* file_path, const char* asset_name) {
		int index = -1;
		caller::call<void>(patterns::register_streaming_file, &index, file_path, true, asset_name, false);

		return index;
	}

	inline const char* get_vehicle_class_name(int id) {
		std::stringstream ss; ss << "VEH_CLASS_" << id;
		return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str()) == "NULL" ? "Unknown Class" : HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str());
	}



	inline float deg_to_rad(float degs) {
		return degs * 3.141592653589793f / 180.f;
	}


	inline void request_model(std::uint32_t hash) {
		STREAMING::REQUEST_MODEL(hash);
		while (!STREAMING::HAS_MODEL_LOADED(hash)) {
			util::fiber::go_to_main();
		}
	}

	inline std::vector<uint32_t> get_hash_list_from_hash_table(uint32_t count, uint64_t table) {
		std::vector<uint32_t> hashes;

		if (count && table) {
			uint64_t* ptr = (uint64_t*)table;

			for (uint32_t i = 0; i < count; i++) {
				if (ptr[i]) {
					uint32_t hash = *(uint32_t*)(ptr[i] + 0x10);

					if (hash) {
						hashes.push_back(hash);
					}
				}
			}
		}

		return hashes;
	}
}