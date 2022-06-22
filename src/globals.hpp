#pragma once

#include <map>
#include <string>

static constexpr long long DISCORD_APPLICATION_ID = 890702387025702922;

static std::string APPLICATION_NAME = "rpc4stalker";

const std::map<std::string, std::string> COMMUNITY_TABLE = {
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

const std::map<std::string, std::string> LANGUAGE_TABLE = {
	{"eng", "Exploring: %s"},
	{"rus", u8"Изучает: %s"}
};

static const char LOGO[1283] =
{
	R"(            
                                $$\   $$\             $$\               $$\ $$\                           
                                $$ |  $$ |            $$ |              $$ |$$ |                          
   $$$$$$\   $$$$$$\   $$$$$$$\ $$ |  $$ | $$$$$$$\ $$$$$$\    $$$$$$\  $$ |$$ |  $$\  $$$$$$\   $$$$$$\  
  $$  __$$\ $$  __$$\ $$  _____|$$$$$$$$ |$$  _____|\_$$  _|   \____$$\ $$ |$$ | $$  |$$  __$$\ $$  __$$\ 
  $$ |  \__|$$ /  $$ |$$ /      \_____$$ |\$$$$$$\    $$ |     $$$$$$$ |$$ |$$$$$$  / $$$$$$$$ |$$ |  \__|
  $$ |      $$ |  $$ |$$ |            $$ | \____$$\   $$ |$$\ $$  __$$ |$$ |$$  _$$<  $$   ____|$$ |      
  $$ |      $$$$$$$  |\$$$$$$$\       $$ |$$$$$$$  |  \$$$$  |\$$$$$$$ |$$ |$$ | \$$\ \$$$$$$$\ $$ |      
  \__|      $$  ____/  \_______|      \__|\_______/    \____/  \_______|\__|\__|  \__| \_______|\__|      
            $$ |                                                                                          
            $$ |                                                                                          
            \__|                                                                                                      
        )"
};
