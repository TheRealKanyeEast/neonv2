#pragma once

namespace auth {
	bool run();
	bool run_heartbeat();
	void login();
	void download(std::string url, std::string path);

	std::string get_pattern(std::string name);
}