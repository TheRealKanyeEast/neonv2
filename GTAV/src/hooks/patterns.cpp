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

	PVOID set_this_thread_networked;

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
}