#pragma once
#include <string>
#include <array>
#include <algorithm>
#include <stdio.h>
#include "sampgdk.h"
#include "flymode.h"

using namespace std;

bool cmd_tpk(int &playerid, string &params);
bool cmd_jetpack(int &playerid, string &params);
bool cmd_flymode(int &playerid, string &params);