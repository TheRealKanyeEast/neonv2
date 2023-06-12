#pragma once
#include "pch.h"
#include "rage/classes/scrNativeRegistrationTable.h"
#include "rage/classes/scrProgram.h"
#include "rage/classes/scrNativeCallContext.h"
#include "rage/classes/pgDictionary.h"
#include "rage/classes/grcTextureStore.h"
#include "rage/classes/grcTextureFactory.h"
#include "rage/classes/CPedFactory.h"
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
	extern uint64_t queue_dependency;
	extern PVOID interval_check_func;

	extern uint64_t send_network_event;

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
}