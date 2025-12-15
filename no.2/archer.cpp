#include"archer.h"
#include<iostream>

using namespace std;

Archer::Archer(string nickname) :Player(nickname)
{
	job_name = "궁수";
	cout << "궁수로 전직했습니다. " << endl;
	HP = 50;
}

void Archer::attack()
{
	cout << "활대를 휘두른다." << endl;

}