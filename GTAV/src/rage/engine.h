#pragma once
#include "pch.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "classes/classes.h"
#include "rage/invoker/natives.h"

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

	inline void request_model(std::uint32_t hash) {
		STREAMING::REQUEST_MODEL(hash);
		while (!STREAMING::HAS_MODEL_LOADED(hash)) {
			std::this_thread::yield();
		}
	}

	inline float deg_to_rad(float degs) {
		return degs * 3.141592653589793f / 180.f;
	}

	inline Vehicle spawn_vehicle(std::uint32_t hash) {
		if (!STREAMING::IS_MODEL_VALID(hash)) {
			return NULL;
		}
		request_model(hash);
		float forward = 5.f;
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		float x = forward * sin(deg_to_rad(heading)) * -1.f;
		float y = forward * cos(deg_to_rad(heading));
		*(unsigned short*)patterns::set_this_thread_networked = 0x9090; // we set this thread as networked so we can spawn the vehicle / u can add rage classes and use excute under thread instead of this
		Vehicle the_vehicle = VEHICLE::CREATE_VEHICLE(hash, coords, heading, NETWORK::NETWORK_IS_SESSION_ACTIVE(), false, false);
		std::int32_t net_id = NETWORK::VEH_TO_NET(the_vehicle);
		*(unsigned short*)patterns::set_this_thread_networked = 0x0574; // We restore it so we don't get detected 
		if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
			NETWORK::NETWORK_FADE_IN_ENTITY(the_vehicle, true, 0);
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(net_id, TRUE);
			if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_VEH(net_id))) {
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), NETWORK::NET_TO_VEH(net_id), -1);
				float speed = ENTITY::GET_ENTITY_SPEED(the_vehicle);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(NETWORK::NET_TO_VEH(net_id), speed);
				VEHICLE::SET_VEHICLE_ENGINE_ON(NETWORK::NET_TO_VEH(net_id), TRUE, TRUE, TRUE);
				DECORATOR::DECOR_SET_INT(NETWORK::NET_TO_VEH(net_id), "MPBitset", (1 << 10));
				return the_vehicle;
			}
		}
		return NULL;
	}
}