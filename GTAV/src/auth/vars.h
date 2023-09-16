#pragma once
#include "pch.h"
#include "security/xor.h"
#include "hardware/hardware.h"

namespace auth::vars {

	inline std::string g_username;
	inline std::string g_password;

	inline std::string g_type = XOR("NULL");
	inline bool g_logged_in = true;

}