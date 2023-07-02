#include "pch.h"
#include "hardware.h"
#include "security/xor.h"

namespace auth {
	std::string hardware::get_hwid() {
		std::string hwid;

#ifdef _WIN32
		WCHAR volume_name[MAX_PATH + 1] = { 0 };
		DWORD serial_number = 0;
		DWORD max_component_len = 0;
		DWORD file_system_flags = 0;

		if (GetVolumeInformation(XOR(L"C:\\"), volume_name, ARRAYSIZE(volume_name), &serial_number, &max_component_len, &file_system_flags, NULL, 0)) {
			hwid = std::to_string(serial_number);
		}
		else {
			std::cerr << XOR("Failed to get HWID: ") << GetLastError() << std::endl;
		}
#else

		hwid = system(XOR("sudo dmidecode -s system-uuid"));
#endif

		return hwid;
	}
}