#pragma once

#include <map>
#include <string>

namespace config
{
	const std::map<std::string, std::string> mCommunities = {
		{"actor_stalker", "stalker_patch_stalker"},
		{"actor_bandit", "stalker_patch_bandit"},
		{"actor_csky", "stalker_patch_csky"},
		{"actor_dolg", "stalker_patch_dolg"},
		{"actor_freedom", "stalker_patch_freedom"},
		{"actor_killer", "stalker_patch_killer"},
		{"actor_army", "stalker_patch_army"},
		{"actor_ecolog", "stalker_patch_ecolog"},
		{"actor_monolith", "stalker_patch_monolith"},
		{"actor_renegade", "stalker_patch_renegade"},
		{"actor_isg", "stalker_patch_isg"},
		{"actor_greh", "stalker_patch_greh"}
	};

	const std::map<std::string, std::string> mLanguage = {
		{"eng", "[%s] Exploring: %s"},
		{"rus", u8"[%s] Изучает: %s"}
	};
}
