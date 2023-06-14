#pragma once
#include "pch.h"
#include "hooks/patterns.h"
#include "rage/classes/NetObject.h"
#include "util/fiber.h"
#include "rage/invoker/natives.h"

namespace menu::control {
	inline bool network_has_control_of_entity(rage::netObject* net_object) {
		return !net_object || !net_object->m_next_owner_id && (net_object->m_control_id == -1);
	}

	inline bool request_control(Entity ent, int timeout = 300) {
		if (!*patterns::is_session_started)
			return true;

		auto hnd = patterns::handle_to_ptr(ent);

		if (!hnd || !hnd->m_net_object || !*patterns::is_session_started)
			return false;

		if (network_has_control_of_entity(hnd->m_net_object))
			return true;

		for (int i = 0; i < timeout; i++)
		{
			patterns::request_control(hnd->m_net_object);

			if (network_has_control_of_entity(hnd->m_net_object))
				return true;

			if (timeout != 0)
				util::fiber::go_to_main();
		}

		return false;
	}

	inline void simple_request_weapon(uint32_t model) {
		int tries = 0;
		while (!WEAPON::HAS_WEAPON_ASSET_LOADED(model) && tries < 30) {
			WEAPON::REQUEST_WEAPON_ASSET(model, 31, 0);
			tries++;
			util::fiber::go_to_main();
		}
	}



}