#pragma once
#include "sampgdk.h"
#include <cmath>

#define MOVE_SPEED              100.0f
#define accelmul_RATE			0.03f
#define MOVE_FORWARD    		1
#define MOVE_BACK       		2
#define MOVE_LEFT       		3
#define MOVE_RIGHT      		4
#define MOVE_FORWARD_LEFT       5
#define MOVE_FORWARD_RIGHT      6
#define MOVE_BACK_LEFT          7
#define MOVE_BACK_RIGHT         8

class noclipenum {
private:
	void GetNextCameraPosition(int mode, float CP[3], float FV[3], float *X, float *Y, float *Z);
	void MoveCamera(int playerid);
	int GetMoveDirectionFromKeys(int ud, int lr);
public:
	int FlyModeOnPlayerKeyStateChange(int * playerid, int * newkeys, int * oldkeys);
	int UpdateFlyMode(int playerid);
	void CancelFlyMode(int playerid);
	void FlyMode(int playerid);
	bool flymode;
	bool cameramode;
	int flyobject;
	int mode;
	int lrold;
	int udold;
	int lastmove;
	float accelmul;
	float spawnCordX;
	float spawnCordY;
	float spawnCordZ;
	float spawnCordAngle;
};