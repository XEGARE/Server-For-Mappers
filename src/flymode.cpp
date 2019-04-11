#include "flymode.h"

#define PRESSED(x) \
				(((*newkeys & (x)) == (x)) && ((*oldkeys & (x)) != (x)))
#define RELEASED(x) \
				(((*newkeys & (x)) != (x)) && ((*oldkeys & (x)) == (x)))

// Private

void noclipenum::GetNextCameraPosition(int mode, float CP[3], float FV[3], float *X, float *Y, float *Z)
{
	#define OFFSET_X (FV[0]*6000.0f)
	#define OFFSET_Y (FV[1]*6000.0f)
	#define OFFSET_Z (FV[2]*6000.0f)
	switch (mode)
	{
		case MOVE_FORWARD:
		{
			*X = CP[0] + OFFSET_X;
			*Y = CP[1] + OFFSET_Y;
			*Z = CP[2] + OFFSET_Z;
			break;
		}
		case MOVE_BACK:
		{
			*X = CP[0] - OFFSET_X;
			*Y = CP[1] - OFFSET_Y;
			*Z = CP[2] - OFFSET_Z;
			break;
		}
		case MOVE_LEFT:
		{
			*X = CP[0] - OFFSET_Y;
			*Y = CP[1] + OFFSET_X;
			*Z = CP[2];
			break;
		}
		case MOVE_RIGHT:
		{
			*X = CP[0] + OFFSET_Y;
			*Y = CP[1] - OFFSET_X;
			*Z = CP[2];
			break;
		}
		case MOVE_BACK_LEFT:
		{
			*X = CP[0] + (-OFFSET_X - OFFSET_Y);
			*Y = CP[1] + (-OFFSET_Y + OFFSET_X);
			*Z = CP[2] - OFFSET_Z;
			break;
		}
		case MOVE_BACK_RIGHT:
		{
			*X = CP[0] + (-OFFSET_X + OFFSET_Y);
			*Y = CP[1] + (-OFFSET_Y - OFFSET_X);
			*Z = CP[2] - OFFSET_Z;
			break;
		}
		case MOVE_FORWARD_LEFT:
		{
			*X = CP[0] + (OFFSET_X - OFFSET_Y);
			*Y = CP[1] + (OFFSET_Y + OFFSET_X);
			*Z = CP[2] + OFFSET_Z;
			break;
		}
		case MOVE_FORWARD_RIGHT:
		{
			*X = CP[0] + (OFFSET_X + OFFSET_Y);
			*Y = CP[1] + (OFFSET_Y - OFFSET_X);
			*Z = CP[2] + OFFSET_Z;
			break;
		}
	}
}

void noclipenum::MoveCamera(int playerid)
{
	float FV[3], CP[3];

	GetPlayerCameraPos(playerid, &CP[0], &CP[1], &CP[2]);
	GetPlayerCameraFrontVector(playerid, &FV[0], &FV[1], &FV[2]);

	int keys, ud, lr;

	GetPlayerKeys(playerid, &keys, &ud, &lr);

	if ((keys & 32) || (keys & 128))
		accelmul = 0.0f;
	if (accelmul <= 1)
		accelmul += accelmul_RATE;

	float speed = MOVE_SPEED * accelmul;
	float X, Y, Z;

	GetNextCameraPosition(mode, CP, FV, &X, &Y, &Z);

	if ((keys & 32) && (keys & 128))
		MovePlayerObject(playerid, flyobject, X, Y, Z, speed / 25.0f, 0.0f, 0.0f, 0.0f);
	else if ((keys & 32) || (keys & 128))
		MovePlayerObject(playerid, flyobject, X, Y, Z, speed / 5.0f, 0.0f, 0.0f, 0.0f);
	else if (keys & 4)
		MovePlayerObject(playerid, flyobject, X, Y, Z, speed*5.0f, 0.0f, 0.0f, 0.0f);
	else
		MovePlayerObject(playerid, flyobject, X, Y, Z, speed, 0.0f, 0.0f, 0.0f);

	lastmove = GetTickCount();
}

int noclipenum::GetMoveDirectionFromKeys(int ud, int lr)
{
	int direction = 0;

	if (lr < 0)
	{
		if (ud < 0)
			direction = MOVE_FORWARD_LEFT;
		else if (ud > 0)
			direction = MOVE_BACK_LEFT;
		else
			direction = MOVE_LEFT;
	}
	else if (lr > 0)
	{
		if (ud < 0)
			direction = MOVE_FORWARD_RIGHT;
		else if (ud > 0)
			direction = MOVE_BACK_RIGHT;
		else
			direction = MOVE_RIGHT;
	}
	else if (ud < 0)
		direction = MOVE_FORWARD;
	else if (ud > 0)
		direction = MOVE_BACK;
	return direction;
}

// Public

int noclipenum::UpdateFlyMode(int playerid)
{
	if (cameramode)
	{
		int keys, ud, lr;
		GetPlayerKeys(playerid, &keys, &ud, &lr);

		if (mode && ((GetTickCount() - lastmove) > 100))
			MoveCamera(playerid);

		if (udold != ud || lrold != lr)
		{
			if ((udold != 0 || lrold != 0) && ud == 0 && lr == 0)
			{
				StopPlayerObject(playerid, flyobject);
				mode = 0;
				accelmul = 0.0f;
			}
			else
			{
				mode = GetMoveDirectionFromKeys(ud, lr);
				MoveCamera(playerid);
			}
		}
		udold = ud;
		lrold = lr;
		return false;
	}
	return false;
}

void noclipenum::CancelFlyMode(int playerid)
{
	flymode =
	cameramode = false;

	CancelEdit(playerid);

	TogglePlayerSpectating(playerid, false);

	DestroyPlayerObject(playerid, flyobject);
}

void noclipenum::FlyMode(int playerid)
{
	float X, Y, Z, Angle;

	GetPlayerPos(playerid, &X, &Y, &Z);
	GetPlayerFacingAngle(playerid, &Angle);

	spawnCordX = X;
	spawnCordY = Y;
	spawnCordZ = Z;
	spawnCordAngle = Angle;

	flyobject = CreatePlayerObject(playerid, 19300, X, Y, Z, Angle, 0.0f, 0.0f, 10.0f);

	TogglePlayerSpectating(playerid, true);

	AttachCameraToPlayerObject(playerid, flyobject);

	flymode =
	cameramode = true;
}

int noclipenum::FlyModeOnPlayerKeyStateChange(int * playerid, int * newkeys, int * oldkeys) {
	if (flymode) {
		if (PRESSED(KEY_SECONDARY_ATTACK | KEY_WALK)) {
			float cameraX, cameraY, cameraZ;
			float vectorX, vectorY, vectorZ;

			GetPlayerCameraPos(*playerid, &cameraX, &cameraY, &cameraZ);
			GetPlayerCameraFrontVector(*playerid, &vectorX, &vectorY, &vectorZ);

			float angle = 360.0f - (atan2(vectorX, vectorY) * 180.0f / 3.14159265f);

			SetSpawnInfo(*playerid, 0, 303, cameraX, cameraY, cameraZ, angle, 0, 0, 0, 0, 0, 0);
			CancelFlyMode(*playerid);
			return 1;
		}
		if (RELEASED(KEY_SECONDARY_ATTACK)) {
			SetSpawnInfo(*playerid, 0, 303,
				spawnCordX,
				spawnCordY,
				spawnCordZ,
				spawnCordAngle, 0, 0, 0, 0, 0, 0);

			SpawnPlayer(*playerid);

			CancelFlyMode(*playerid);
			return 1;
		}
	}
	return true;
}