#include"warrior.h"
#include<iostream>

using namespace std;

Warrior::Warrior(string nickname): Player(nickname)
{
	job_name = "전사";
	cout << "* 전사로 전직했습니다." << endl;
	HP = 80;

	
}

void Warrior::attack()
{
	cout << "도끼 쩍!" << endl;
}