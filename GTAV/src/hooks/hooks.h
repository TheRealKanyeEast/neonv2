#pragma once
#include "util/hooking/hooking.h"
#include "rage/classes/scrNativeCallContext.h"
#include "rage/classes/scrThread.h"
#include "rage/classes/scrProgram.h"

namespace base::hooks {
	bool patterns();
	bool hooks();

	void stat_get_int(rage::scrNativeCallContext* context);
	void set_current_ped_weapon(rage::scrNativeCallContext* context);
	void disable_control_action(rage::scrNativeCallContext* context);


	uint64_t script_vm(void* stack, int64_t** globals, rage::scrProgram* program, rage::scrThreadContext* ctx);
	inline decltype(&script_vm) script_vm_t;

	void* get_font_id(uint64_t font, int id);
	inline decltype(&get_font_id) get_font_id_t;

	int nt_query_virtual_memory(void* _this, HANDLE handle, PVOID base_addr, int info_class, MEMORY_BASIC_INFORMATION* info, int size, size_t* return_len);
	
	void queue_dependency(void* dependency);
	inline decltype(&queue_dependency) queue_dependency_t;

	void send_network_event(uint64_t net_table, uint64_t event);
	inline decltype(&send_network_event) send_network_event_t;

	uint64_t format_engine_string(uint64_t rcx, uint64_t rdx, uint32_t r8d, const char* r9, uint32_t stack);
	inline decltype(&format_engine_string) format_engine_string_t;

	int get_engine_string_line_count(uint64_t rcx, const char* rdx, float xmm2, uint64_t r9, bool stack);
	inline decltype(&get_engine_string_line_count) get_engine_string_line_count_t;

	bool allow_weapons_in_vehicle(int64_t unk, int weaponinfo_group);
	inline decltype(&allow_weapons_in_vehicle) allow_weapons_in_vehicle_t;

}