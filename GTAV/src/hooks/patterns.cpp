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

	uint64_t queue_dependency;
	PVOID interval_check_func;

	uint64_t send_network_event;

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
}