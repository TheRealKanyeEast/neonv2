#include "pch.h"
#include "hooks/hooks.h"
#include "rage/classes/datBitBuffer.h"
#include "rage/classes/netGameEvent.h"

namespace base::hooks {
	
	bool get_msg_type(rage::netConnection::eNetMessage& msgType, rage::datBitBuffer& buffer)
	{
		uint32_t pos;
		uint32_t magic;
		uint32_t length;
		uint32_t extended{};
		if ((buffer.m_flagBits & 2) != 0 || (buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			buffer.m_bitsRead + 15 > pos || !buffer.ReadDword(&magic, 14) || magic != 0x3246 || !buffer.ReadDword(&extended, 1))
		{
			msgType = rage::netConnection::eNetMessage::MsgInvalid;
			return false;
		}
		length = extended ? 16 : 8;
		if ((buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			length + buffer.m_bitsRead <= pos && buffer.ReadDword((uint32_t*)&msgType, length))
			return true;
		else
			return false;
	}

	bool hooks::receiveNetMessageHook(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame) {

		if (frame->get_event_type() != rage::netConnection::InFrame::EventType::FrameReceived) {
			LOG_WARN("Bad Frame Execution - 1");
			return ogReceiveNetMessageHook(netConnectionManager, a2, frame);
		}

		if (frame->m_data == nullptr || frame->m_length == 0) {
			LOG_WARN("Bad Frame Execution - 2");
			return ogReceiveNetMessageHook(netConnectionManager, a2, frame);
		}

		rage::datBitBuffer buffer(frame->m_data, frame->m_length);
		buffer.m_flagBits = 1;

		rage::netConnection::eNetMessage msgType;

		CNetGamePlayer* player{};
		for (auto p : (*patterns::network_player_mgr)->m_player_list) {
			if (p)
				if (p->m_msg_id == frame->m_msg_id) player = p;
		}

		if (!get_msg_type(msgType, buffer)) {
			LOG_WARN("Bad Frame Execution - 3");
			return ogReceiveNetMessageHook(netConnectionManager, a2, frame);
		}


		if (player) {
			switch (msgType) {
			case rage::netConnection::eNetMessage::MsgNetComplaint:
			{
				uint64_t host_token{};
				buffer.ReadQWord(&host_token, 64);

				std::vector<CNetGamePlayer*> players;

				uint32_t num_of_tokens{};
				buffer.ReadDword(&num_of_tokens, 32);
				return true; // block desync kicks as host
			}
			}
		}

		return ogReceiveNetMessageHook(netConnectionManager, a2, frame);
	}
}