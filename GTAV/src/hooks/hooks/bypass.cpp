#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"

namespace base::hooks {

	bool send_http_request(CHttpRequest* request) {
		if (request->RequestData && request->RequestData->Data) {
		//	LOG("Request to %s://%s%s:\n%s\n%s", request->Scheme, request->Host, request->Path, request->RequestHeaders ? request->RequestHeaders : "No headers available.", request->RequestData && request->RequestData->Data && strcmp(request->Scheme, "https") == 0 ? request->RequestData->Data : "null");
			
			const auto path = std::string(request->Path);
			for (auto blockedApi : { "SubmitCompressed", "SubmitRealTime", "Bonus" }) {
				if (path.find(blockedApi) != std::string::npos) {
					request->Host = const_cast<char*>("google.com");
					return og_send_http_request(request);
				}
			}
		}

		return og_send_http_request(request);
	}

	uint64_t add_event_to_list(uint64_t event_pool) {
		uint64_t caller = (uint64_t)_ReturnAddress();

		if (caller == patterns::report_myself) {
			LOG_CUSTOM_WARN("AC", "Prevented REPORT_MYSELF_EVENT creation");
		}

		if (caller == patterns::check_crc) {
			LOG_CUSTOM_WARN("AC", "Prevented NETWORK_CHECK_CODE_CRCS_EVENT creation");
		}

		if (caller == patterns::cash_spawn) {
			LOG_CUSTOM_WARN("AC", "Prevented REPORT_CASH_SPAWN_EVENT creation");
		}

		return og_add_event_to_list(event_pool);
	}

	void send_network_event(uint64_t net_table, uint64_t event) {
		if (event) {
			short type = *(short*)(event + 8);

			if (type == 83u || type == 84u || type == 78u) {
				LOG_CUSTOM_WARN("AC", "Blocking network event - %i", type);

				uint64_t table = *(uint64_t*)event;
				caller::call<int>(*(uint64_t*)table, event, 1); // Deallocate event
				return;
			}
		}

		return og_send_network_event(net_table, event);
	}

	int nt_query_virtual_memory(void* _this, HANDLE handle, PVOID base_addr, int info_class, MEMORY_BASIC_INFORMATION* info, int size, size_t* return_len) {
		return 1;
	}

	bool inline is_address_in_game_region(uint64_t address) {
		static uint64_t moduleBase = NULL;
		static uint64_t moduleSize = NULL;
		if ((!moduleBase) || (!moduleSize)) {
			MODULEINFO info;
			if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info))) {
				LOG_ERROR("Failed to find address in game region");
				return true;
			}
			else
			{
				moduleBase = (uint64_t)GetModuleHandle(0);
				moduleSize = (uint64_t)info.SizeOfImage;
			}
		}
		return address > moduleBase && address < (moduleBase + moduleSize);
	}

	bool is_jump(__int64 fptr) {
		if (!is_address_in_game_region(fptr))
			return false;

		auto value = *(std::uint8_t*)(fptr);
		return value == 0xE9;
	}

	bool is_unwanted_dependency(__int64 cb) {
		auto f1 = *(__int64*)(cb + 0x60);
		auto f2 = *(__int64*)(cb + 0x100);
		auto f3 = *(__int64*)(cb + 0x1A0);

		return is_jump(f1) || is_jump(f2) || is_jump(f3);
	}

	void queue_dependency(void* dependency) {
		if (is_unwanted_dependency((__int64)dependency))
			return;

		return og_queue_dependency(dependency);
	}

}