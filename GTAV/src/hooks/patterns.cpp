#include "pch.h"
#include "patterns.h"

namespace patterns {
	uint64_t script_vm;

	uint32_t* game_state;
	uint32_t* frame_count;

	void* jmp_rbx_register;

	get_native_handler_t get_native_handler;

	rage::scrNativeRegistrationTable* native_registration_table;
	rage::scrProgramTable* script_program;
	rage::types::store_manager* store_manager;
	rage::hash_list* hash_list;
	rage::weapon_hash_list* weapon_components;
	rage::weapon_hash_list* weapon_info;
	CPedFactory** ped_factory;

	PVOID set_this_thread_networked;
	int64_t** script_globals;
	uint64_t get_font_id;
	uint64_t font_table;
	uint64_t font_memory_helper;
	uint64_t get_font_id_table;
	uint64_t construct_gfx_font;
	uint64_t destruct;
	uint64_t create_id_for_font;
	uint64_t add_font_lib;
	uint64_t get_store_module_extension;
	uint64_t register_streaming_file;
	uint64_t request_streaming_file;


	setup_dictionary_t setup_dictionary;
	add_texture_to_dictionary_t add_texture_to_dictionary;
	setup_store_item_t setup_store_item;
	add_dictionary_to_pool_t add_dictionary_to_pool;
	rage::grcTextureStore* texture_store;
	rage::grcTextureFactory** texture_factory;
	get_net_game_player get_net_player;
	IDXGISwapChain** swapchain;

	uint64_t format_game_string;
	uint64_t get_game_string_line_count;

	bool* is_session_started;
	request_control_t request_control;
	handle_to_ptr_t handle_to_ptr;

	memory::byte_patch* max_wanted_level;
	memory::byte_patch* max_wanted_level_2;

	fix_vectors_t fix_vectors;

	ptr_to_handle_t ptr_to_handle;

	 GenericPool** ped_pool;
	 GenericPool** prop_pool;
	 VehiclePool*** vehicle_pool;

	 int* resolution_x;
	 int* resolution_y;

	 uint64_t allow_weapons_in_vehicle;
	 uint64_t get_entity_address;
	 uint64_t set_vehicle_gravity;

	 std::pair<CWheelVfx*, uint8_t> vfx_wheel;
	 CBlipList* blip_list;


	 uint64_t invalid_resource_check; //80 3D ?? ?? ?? ?? ?? 0F 85 A7 00 00 00 48 8B 05
	 uint64_t integ_check_1; //48 83 EC 48 48 83 64 24 ? ? 83 4C 24
	 uint64_t add_event_to_list; //4C 8B D1 48 63 49 18
	 uint64_t check_crc; // 48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 30 44 8B F1 48 8B 0D
	 uint64_t report_myself; // 40 53 48 83 EC 40 83 B9 ? ? ? ? ? 48 8B D9 75 67 48 83 64 24 ? ? 48 83 64 24 ? ? 48 8D 54 24 ? 48 81 C1
	 uint64_t cash_spawn; // 48 89 5C 24 08 57 48 83 EC 20 33 FF 48 8B D9 48 85 C9 74 0B
	 uint64_t send_http_request;
	 uint64_t queue_dependency;
	 uint64_t send_network_event;
	 PVOID interval_check_func;

	 rage::atArray<GtaThread*>* script_threads;
	 CNetworkPlayerMgr** network_player_mgr;
	 uint64_t start_get_session_by_gamer_handle;
	 Network** network;
	 uint64_t encode_session_info;
}