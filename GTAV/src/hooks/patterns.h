#pragma once
#include "pch.h"
#include "rage/classes/scrNativeRegistrationTable.h"
#include "rage/classes/scrProgram.h"
#include "rage/classes/scrNativeCallContext.h"
#include "rage/classes/pgDictionary.h"
#include "rage/classes/grcTextureStore.h"
#include "rage/classes/grcTextureFactory.h"
#include "rage/classes/CPedFactory.h"
#include "rage/invoker/types.h"
#include "memory/pattern.h"
#include "rage/classes/vfx.h"
#include "rage/classes/CBlipList.h"
#include "rage/classes/atArray.h"
#include "rage/classes/CNetworkPlayerMgr.h"
#include "rage/classes/scrThread.h"
#include "rage/classes/Network.h"

class GenericPool;
class VehiclePool;
namespace patterns {
	extern rage::scrNativeRegistrationTable* native_registration_table;
	extern rage::scrProgramTable* script_program;
	extern rage::hash_list* hash_list;
	extern rage::weapon_hash_list* weapon_components;
	extern rage::weapon_hash_list* weapon_info;
	extern rage::types::store_manager* store_manager;
	extern CPedFactory** ped_factory;

	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable* registration_table, rage::scrNativeHash hash);
	extern get_native_handler_t get_native_handler;

	extern void* jmp_rbx_register;

	extern PVOID set_this_thread_networked;

	extern uint32_t* game_state;
	extern uint32_t* frame_count;
	extern int64_t** script_globals;
	extern uint64_t script_vm;
	extern uint64_t get_font_id;
	extern uint64_t font_table;
	extern uint64_t font_memory_helper;
	extern uint64_t get_font_id_table;
	extern uint64_t construct_gfx_font;
	extern uint64_t destruct;
	extern uint64_t create_id_for_font;
	extern uint64_t add_font_lib;
	extern uint64_t get_store_module_extension;
	extern uint64_t register_streaming_file;
	extern uint64_t request_streaming_file;	

	using setup_dictionary_t = rage::pgDictionary* (*)(rage::pgDictionary* dict, int size);
	using add_texture_to_dictionary_t = void(*)(rage::pgDictionary* dict, uint32_t hash, rage::grcTexture* texture);
	using setup_store_item_t = uint32_t * (*)(rage::grcTextureStore* store, uint32_t* out, uint32_t* dictHash);
	using add_dictionary_to_pool_t = void(*)(rage::grcTextureStore* store, uint32_t slot, rage::pgDictionary* dict);
	using add_text_component_t = void(*)(const char* string);

	using get_net_game_player = CNetGamePlayer* (*) (uint32_t player);
	extern get_net_game_player get_net_player;


	extern setup_dictionary_t setup_dictionary;
	extern add_texture_to_dictionary_t add_texture_to_dictionary;
	extern setup_store_item_t setup_store_item;
	extern add_dictionary_to_pool_t add_dictionary_to_pool;
	extern rage::grcTextureStore* texture_store;
	extern rage::grcTextureFactory** texture_factory;

	extern uint64_t format_game_string;
	extern uint64_t get_game_string_line_count;

	extern IDXGISwapChain** swapchain;

	extern bool* is_session_started;

	using handle_to_ptr_t = rage::CDynamicEntity* (*)(Entity);
	extern handle_to_ptr_t handle_to_ptr;
	
	using request_control_t = void (*)(rage::netObject* net_object);
	extern request_control_t request_control;

	extern memory::byte_patch* max_wanted_level;
	extern memory::byte_patch* max_wanted_level_2;

	using fix_vectors_t = void(*)(rage::scrNativeCallContext* call_ctx);
	extern fix_vectors_t fix_vectors;

	extern GenericPool** ped_pool;
	extern GenericPool** prop_pool;
	extern VehiclePool*** vehicle_pool;

	using ptr_to_handle_t = Entity(*)(void*);
	extern ptr_to_handle_t ptr_to_handle;

	extern int* resolution_x;
	extern int* resolution_y;

	extern uint64_t allow_weapons_in_vehicle;
	extern uint64_t get_entity_address;
	extern uint64_t set_vehicle_gravity;

	extern std::pair<CWheelVfx*, uint8_t> vfx_wheel;
	extern CBlipList* blip_list;

	extern uint64_t invalid_resource_check;
	extern uint64_t ac_patch_1;//48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 8D 8D ? ? ? ? 0F 29 70 B8 E8 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 4C 8D 05 (detected, has self healing vtables)
	extern uint64_t ac_patch_2;//48 89 5C 24 ?? 55 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B D9 48 8D 0D 
	extern uint64_t integ_check_1;
	extern uint64_t add_event_to_list;
	extern uint64_t send_network_event;
	extern uint64_t send_http_request;
	extern uint64_t check_crc;
	extern uint64_t report_myself;
	extern uint64_t cash_spawn;
	extern uint64_t queue_dependency;
	extern PVOID interval_check_func;

	extern rage::atArray<GtaThread*>* script_threads;
	extern CNetworkPlayerMgr** network_player_mgr;
	extern uint64_t start_get_session_by_gamer_handle;

	extern Network** network;
	extern uint64_t encode_session_info;
}