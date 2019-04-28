#include "ServerForMappers.hpp"

using namespace std;

array <noclipenum, MAX_PLAYERS> noclipdata;

unordered_map<string, bool(*)(int&, string&)> CommandMap;

struct Commands
{
	string names;
	bool(*ptr)(int&, string&);
};

const Commands commands[] = { 
	{ "/тпк", cmd_tpk },
	{ "/tpk", cmd_tpk },
	{ "/ngr", cmd_tpk },
	{ "/езд", cmd_tpk },
	{ "/джетпак", cmd_jetpack },
	{ "/jetpack", cmd_jetpack },
	{ "/l;tngfr", cmd_jetpack },
	{ "/оуезфсл", cmd_jetpack },
	{ "/полет", cmd_flymode },
	{ "/fly", cmd_flymode },
	{ "/gjktn", cmd_flymode },
	{ "/адн", cmd_flymode }
};

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
	SendRconCommand("hostname Server for mappers");
	SendRconCommand("language Russian | English");
	SetGameModeText("by XEGARE");
	SendRconCommand("weburl vk.com/xegare");
	DisableInteriorEnterExits();

	printf("|-----------------------------|\n");
	printf("| Server for mappers: Loaded! |\n");
	printf("|          by XEGARE          |\n");
	printf("|-----------------------------|\n");
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeExit()
{
	for (static int i; i < MAX_PLAYERS; i++) if (noclipdata[i].cameramode)
		noclipdata[i].CancelFlyMode(i);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid,
                                                    int classid)
{
	for (static int i; i < 50; i++)
		SendClientMessage(playerid, -1, "");

	SetSpawnInfo(playerid, 0, 303, 1958.3783f, 1343.1572f, 15.3746f, -90.0f, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid) {
	GivePlayerWeapon(playerid, 24, 10000);
	GivePlayerWeapon(playerid, 34, 10000);
	GivePlayerWeapon(playerid, 38, 10000);
	SetPlayerHealth(playerid, 0x7F800000);
	SetPlayerArmour(playerid, 0x7F800000);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid,
                                                   const char *cmdtext)
{
	string temp;
	int pos = 0;
	for (int i = strlen(cmdtext); pos < i; pos++)
	{
		if (cmdtext[pos] == ' ')
		{
			pos++;
			break;
		}
		temp.push_back(cmdtext[pos]);
	}

	string cmdtext_s = string(&cmdtext[pos]);

	unordered_map<string, bool(*)(int&, string&)>::const_iterator iter = CommandMap.find(temp);
	if (iter != CommandMap.end()) 
		iter->second(playerid, cmdtext_s);
	else
		SendClientMessage(playerid, -1, "Неизвестная команда!");
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	noclipdata[playerid].FlyModeOnPlayerKeyStateChange(&playerid, &newkeys, &oldkeys);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char *text)
{
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid)
{
	noclipdata[playerid].UpdateFlyMode(playerid);
	return true;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
  return
	  sampgdk::Supports() | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
		CommandMap.emplace(move(commands[i].names), move(commands[i].ptr));
	return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
  sampgdk::Unload();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
  sampgdk::ProcessTick();
}
