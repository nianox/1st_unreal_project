#include"thief.h"
#include<iostream>

using namespace std;

Thief::Thief(string nickname) :Player(nickname)
{
	job_name = "도적";
	cout << "도적으로 전직했습니다. " << endl;
	HP = 60;

}

void Thief :: attack()
{ 
	cout << "단검 슛!" << endl;
}