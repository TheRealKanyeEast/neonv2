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
}