#pragma once
#include <cstdint>
#include "GamerInfo.h"

class CPlayerInfo {
public:
	char pad_0000[32]; //0x0000
	class rage::rlGamerInfo m_gamer_info; //0x0020
	char pad_0118[184]; //0x0118
	float m_swim_speed; //0x01D0
	char pad_01D4[20]; //0x1D4
	uint32_t m_water_proof; //0x01E8
	char pad_01EC[92]; //0x01EC
	class CPed* m_ped; //0x0248
	char pad_0250[40]; //0x0250
	uint32_t m_frame_flags; //0x0278
	char pad_027C[52]; //0x027C
	uint32_t m_player_controls; //0x02B0
	char pad_02B4[1256]; //0x02B4
	float m_wanted_can_change; //0x079C
	char pad_0740[304]; //0x07A0
	uint32_t m_npc_ignore; //0x08D0
	char pad_0874[12]; //0x08D4
	bool m_is_wanted; //0x08E0
	char pad_08E1[7]; //0x08E1
	uint32_t m_wanted_level; //0x08E8
	uint32_t m_wanted_level_display; //0x08EC
	char pad_08F0[1120]; //0x08F0
	float m_run_speed; //0x0D50
	float m_stamina; //0x0D54
	float m_stamina_regen; //0x0D58
	char pad_0D5C[16]; //0x0D5C
	float m_weapon_damage_mult; //0x0D6C
	float m_weapon_defence_mult; //0x0D70
	char pad_0D74[4]; //0x0D74
	float m_melee_weapon_damage_mult; //0x0D78
	float m_melee_damage_mult; //0x0D7C
	float m_melee_defence_mult; //0x0D80
	char pad_0D84[8]; //0x0D84
	float m_melee_weapon_defence_mult; //0x0D8C
}; //Size: 0x0D90
static_assert(sizeof(CPlayerInfo) == 0xD90);