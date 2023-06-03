#pragma once
#include "pch.h"
#include "rage/classes/scrNativeRegistrationTable.h"
#include "rage/classes/scrProgram.h"
#include "rage/classes/scrNativeCallContext.h"
#include "rage/classes/classes.h"
namespace patterns {
	extern rage::scrNativeRegistrationTable* native_registration_table;
	extern rage::scrProgramTable* script_program;
	extern rage::hash_list* hash_list;
	extern rage::types::store_manager* store_manager;

	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable* registration_table, rage::scrNativeHash hash);
	extern get_native_handler_t get_native_handler;

	extern void* jmp_rbx_register;

	extern PVOID set_this_thread_networked;

	extern uint32_t* game_state;
	extern uint32_t* frame_count;

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
}