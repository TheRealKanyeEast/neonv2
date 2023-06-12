#pragma once
#include <cstdint>
#include "PeerInfo.h"
#include "GamerHandle.h"

namespace rage {
	class rlGamerInfo : public rlPeerInfo {
	public:
		uint64_t m_peer_address; //0x00C0
		uint64_t m_platform_data; //0x00C8
		rlGamerHandle m_unk_gamer_handle; //0x00D0
		uint32_t m_ros_privilege; //0x00E0
		char m_name[20]; //0x00E4
	}; //Size: 0x00F8
	static_assert(sizeof(rlGamerInfo) == 0xF8);
}