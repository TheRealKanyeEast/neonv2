#pragma once
#include "pch.h"

namespace auth::socket {
	std::string send_request(std::string url, std::string username, std::string password, std::string auth_key, std::string pattern, std::string iv, std::string hwid);
}