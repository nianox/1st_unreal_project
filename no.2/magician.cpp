#include"magician.h"
#include<iostream>

using namespace std;

Magician::Magician(string nickname) : Player(nickname)
{
	job_name = "마법사";
	cout << "* 마법사!로 전직했습니다." << endl;
	HP = 40;


}
void Magician::attack()
{
	cout << "지팡이 휘두르기" << endl;
}