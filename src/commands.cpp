#include "commands.hpp"

extern array <noclipenum, MAX_PLAYERS> noclipdata;

bool cmd_tpk(int &playerid, string &params)
{
	replace(params.begin(), params.end(), ',', ' ');
	replace(params.begin(), params.end(), '|', ' ');
	replace(params.begin(), params.end(), '{', ' ');
	replace(params.begin(), params.end(), '}', ' ');
	float X, Y, Z;
	int interior = 0, world = 0;
	if (sscanf(params.c_str(), "%f%f%f%d%d", &X, &Y, &Z, &interior, &world) < 3)
		return SendClientMessage(playerid, -1, "Èñïîëüçóéòå: /òïê (x y z) [INT World]");

	if (noclipdata[playerid].flymode) SetPlayerObjectPos(playerid, noclipdata[playerid].flyobject, X, Y, Z);
	else {
		if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK) {
			SetPlayerPos(playerid, X, Y, Z + 3.0f);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
		}
		else
			SetPlayerPos(playerid, X, Y, Z + 3.0f);
	}
	SetPlayerInterior(playerid, interior);
	SetPlayerVirtualWorld(playerid, world);
	return true;
}

bool cmd_jetpack(int &playerid, string &params)
{
	return
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
}

bool cmd_flymode(int &playerid, string &params)
{
	if (noclipdata[playerid].flymode)
		noclipdata[playerid].CancelFlyMode(playerid);
	else
		noclipdata[playerid].FlyMode(playerid);
	return true;
}
