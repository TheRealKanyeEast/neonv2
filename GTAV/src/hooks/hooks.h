#pragma once
#include "util/hooking/hooking.h"
#include "rage/classes/scrNativeCallContext.h"
namespace base::hooks {
	bool patterns();
	bool hooks();

	void stat_get_int(rage::scrNativeCallContext* context);


	uint64_t script_vm(void* stack, int64_t** globals, uint64_t* program, uint64_t* ctx);
	inline decltype(&script_vm) script_vm_t;

	void* get_font_id(uint64_t font, int id);
	inline decltype(&get_font_id) get_font_id_t;

	int nt_query_virtual_memory(void* _this, HANDLE handle, PVOID base_addr, int info_class, MEMORY_BASIC_INFORMATION* info, int size, size_t* return_len);
	
	void queue_dependency(void* dependency);
	inline decltype(&queue_dependency) queue_dependency_t;

	void send_network_event(uint64_t net_table, uint64_t event);
	inline decltype(&send_network_event) send_network_event_t;
}