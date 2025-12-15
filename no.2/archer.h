#pragma once
#include"player.h"

using namespace std;

class Archer:public Player
{
public:
	Archer(string nickname);
	void attack() override;
};