#include "pch.h"
#include "hooks.h"
#include "memory/pattern.h"
#include "util/hooking/hooking.h"
#include "patterns.h"
#include "util/caller.h"
#include "gui/util/fonts.h"
using namespace memory;

namespace base::hooks {
	bool patterns() {
		batch batch;
		bool out = true;

		batch.Add("GS", "83 3D ? ? ? ? ? 75 17 8B 43 20", [](Ptr ptr) {
			patterns::game_state = ptr.lea().as<decltype(patterns::game_state)>();
		}, out);

		batch.Add("NRT", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", [](Ptr ptr) {
			patterns::native_registration_table = ptr.from_instruction().as<decltype(patterns::native_registration_table)>();
			patterns::get_native_handler = ptr.add(12).rip().as<decltype(patterns::get_native_handler)>();
		}, out);

		batch.Add("JRR", "23 C3 C1 E0 0C", [](Ptr ptr) {
			patterns::jmp_rbx_register = ptr.sub(1).as<decltype(patterns::jmp_rbx_register)>();
		}, out);

		batch.Add("SP", "48 8B 1D ? ? ? ? 41 83 F8 FF", [](Ptr ptr) {
			patterns::script_program = ptr.from_instruction().as<decltype(patterns::script_program)>();
		}, out);

		batch.Add(("FT"), "48 8B 05 ? ? ? ? 48 8B CB 48 69 C9 ? ? ? ? 40 38 AC 01 ? ? ? ? 74 0F E8 ? ? ? ? 0F 28 CE 8B CB E8 ? ? ? ? F3 0F 10 05 ? ? ? ? B2 01 E8", [](Ptr ptr) {
			patterns::font_table = ptr.from_instruction().as<uint64_t>();
		}, out);

		batch.Add(("FMH"), "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 DB 48 85 C9", [](Ptr ptr) {
			patterns::font_memory_helper = ptr.from_instruction().as<uint64_t>();
		}, out);

		batch.Add(("D"), "48 83 EC 28 F0 FF 49 08 75 0F 48 85 C9 74 0A 48 8B 01 BA ? ? ? ? FF 10 48 83 C4 28 C3", [](Ptr ptr) {
			patterns::destruct = ptr.as<uint64_t>();
		}, out);

		batch.Add(("CGF"), "40 53 48 83 EC 20 C7 41 ? ? ? ? ? 48 8D 05 ? ? ? ? 48 8B D9 48 89 01 C7 41 ? ? ? ? ? 48 8D 05 ? ? ? ? 48 89 01", [](Ptr ptr) {
			patterns::construct_gfx_font = ptr.as<uint64_t>();//gfx :thumbs_up:
		}, out);

		batch.Add(("CIFF"), "40 55 48 8B EC 48 81 EC ? ? ? ? 49 8B 00 F3 0F 10 02 F3 0F 10 4A ? 83 65 B8 00 83 65 C0 00 83 65 C4 00 F3", [](Ptr ptr) {
			patterns::create_id_for_font = ptr.as<uint64_t>();
		}, out);

		batch.Add(("AFL"), "40 53 48 83 EC 20 48 8B 41 40 4D 63 C8 4C 8B D9 46 0F B6 14 08 48 8B DA 41 81 E2 ? ? ? ? 41 8B C2 45 8B CA 49 F7 D9 4C 0B", [](Ptr ptr) {
			patterns::add_font_lib = ptr.as<uint64_t>();
		}, out);

		batch.Add(("GFIFT"), "48 85 D2 74 10 49 83 C8 FF 49 FF C0 42 80 3C 02 ? 75 F6 EB 03 45 33 C0 E9", [](Ptr ptr) {
			patterns::get_font_id_table = ptr.as<uint64_t>();
		}, out);

		batch.Add(("SM"), "48 8D 0D ? ? ? ? 03 D3 E8 ? ? ? ? 66 44 39 7D ? 74 09 48 8B 4D E8 E8", [](Ptr ptr) {
			patterns::store_manager = ptr.from_instruction().as<rage::types::store_manager*>();
		}, out);

		batch.Add(("GSME"), "40 53 48 83 EC 20 48 8B C2 48 8B D9 33 D2 48 8B C8 E8 ? ? ? ? 33 D2 44 8B D0 F7 35 ? ? ? ? 44 8B C2 48 8B 15 ? ? ? ? 46 8B 0C 82 41", [](Ptr ptr) {
			patterns::get_store_module_extension = ptr.as<uint64_t>();
		}, out);

		batch.Add("RSF", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9 B2", [](Ptr ptr) {
			patterns::register_streaming_file = ptr.as<uint64_t>();
		}, out);

		batch.Add("RSF2", "E8 ? ? ? ? 83 4F 48 10", [](Ptr ptr) {
			patterns::request_streaming_file = ptr.call().as<uint64_t>();
		}, out);

		batch.Add("VHL", "4C 03 05 ? ? ? ? EB 09 49 83 C2 04 EB 8B", [](Ptr ptr) {
			patterns::hash_list = ptr.from_instruction().as<decltype(patterns::hash_list)>();
		}, out);

		batch.Add("STTN", "48 8B C8 FF 52 30 84 C0 74 05 48", [](Ptr ptr) {
			patterns::set_this_thread_networked = ptr.add(8).as<decltype(patterns::set_this_thread_networked)>();
		}, out);

		auto mod = memory::module("GTA5.exe");	
		batch.run(mod);

		return true;
	}
	
	bool hooks() {
		batch batch;
		bool out = false;

		batch.Add("SVM", "E8 ? ? ? ? 48 85 FF 48 89 1D", [&](Ptr ptr) {
			patterns::script_vm = ptr.call().as<uint64_t>();
			return hooking::detour("SVM", patterns::script_vm, &script_vm, &script_vm_t);
		}, out);

		batch.Add("GFI", "85 D2 74 68 FF CA 74 5B FF CA 74 4E FF CA 74 41 FF CA 74 34 FF CA 74 27 FF CA 74 1A FF CA 74 0D", [](Ptr ptr) {
			patterns::get_font_id = ptr.as<uint64_t>();
			return hooking::detour("GFI", patterns::get_font_id, &get_font_id, &get_font_id_t);
		}, out);

		auto mod = memory::module("GTA5.exe");
		batch.run(mod);

		return true;
	}

	uint64_t script_vm(void* stack, int64_t** globals, uint64_t* program, uint64_t* ctx) {
		return script_vm_t(stack, globals, program, ctx);
	}

	void* get_font_id(uint64_t font, int id) {
		std::vector<fonts::font_context> fonts = fonts::get_list();
		for (fonts::font_context font_ : fonts) {
			if (font_.m_font_id == id) {
				return caller::call<void*>(patterns::get_font_id_table, font, font_.m_font_name.c_str());
			}
		}
		return get_font_id_t(font, id);
	}
}