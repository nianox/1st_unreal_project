#pragma once

#include"player.h"

using namespace std;

class Thief:public Player
{
public:
	Thief(string nickname);
	void attack() override;


};