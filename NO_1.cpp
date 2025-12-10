#include<iostream>
#include<functional>
#include<map>

using namespace std;

struct Gamestats {
	int status[4] = { 0 };
	int hpotion, mpotion;
	// int levels;
};

void use_hp_potion(Gamestats& stats)
{
	if (stats.hpotion > 0)
	{
		stats.status[0] += 20;
		stats.hpotion--;
		cout << "* HP가 20 증가되었습니다. 포션이 1개 차감됩니다." << endl;
 	}
	else
	{
		cout << "포션이 부족합니다." << endl;
	}
	cout << "현재 HP: " << stats.status[0] << endl;
	cout << "남은 HP 포션 갯수 " << stats.hpotion << endl;
}

void use_mp_potion(Gamestats& stats)
{
	if (stats.mpotion > 0)
	{
		stats.status[1] += 20;
		stats.mpotion--;
		cout << "* MP가 20 증가되었습니다. 포션이 1개 차감됩니다." << endl;
	}
	else
	{
		cout << "포션이 부족합니다." << endl;
	}
	cout << "현재 MP: " << stats.status[1] << endl;
	cout << "남은 MP 포션 갯수 " << stats.mpotion << endl;
}

void use_atk_amp(Gamestats& stats)
{
	stats.status[2] *= 2;
	cout << "* 공격력이 2배로 증가되었습니다. " << endl;
	cout << "현재 공격력: " << stats.status[2] << endl;
}

void use_def_amp(Gamestats& stats)
{
	stats.status[3] *= 2;
	cout << "* 방어력이 2배로 증가되었습니다. " << endl;
	cout << "현재 방어력: " << stats.status[3] << endl;
}

void use_show_stats(Gamestats& stats)
{
	cout << "* HP : " << stats.status[0] << ", MP : " << stats.status[1] << ", 공격력 : " << stats.status[2] << ", 방어력 : " << stats.status[3] << endl;
}

void use_levelup(Gamestats& stats)
{
	stats.hpotion++;
	stats.mpotion++;
	// stats.level++;
	cout << "* 레벨업!HP / MP 포션이 지급됩니다. " << endl;
	cout << "남은 HP / MP 포션 수 : " << stats.hpotion << "/" << stats.mpotion << endl;
}

void setPotion(int count, Gamestats* stats)
{
	stats->hpotion = count;
	stats->mpotion = count;
	cout << "* 포션이 지급되었습니다. (HP, MP 포션 각 5개)" << endl;
	cout << "=============================================" << endl;
}


void setATK(Gamestats& stats)
{
	cout << "ATK와 DEF를 입력해주세요 : ";
	cin >> stats.status[2] >> stats.status[3];
	if (stats.status[2] <= 0 || stats.status[3] <= 0)
	{
		cout << "ATK나 DEF의 값이 너무 작습니다.다시 입력해주세요." << endl;
		setATK(stats);
	}
	else
	{
		setPotion(5, &stats);
	}
}
void setHPMP(Gamestats& stats)
{
	cout << "HP와 MP를 입력해주세요 : ";
	cin >> stats.status[0] >> stats.status[1];
	if (stats.status[0] < 50 || stats.status[1] < 50)
	{
		cout << "HP나 MP의 값이 너무 작습니다.다시 입력해주세요." << endl;
		setHPMP(stats);
	}
	else
	{
		setATK(stats);
	}
}


int main()
{
	Gamestats stats;

	map<int, function<void(Gamestats&)>> stats_map =
	{
		{1, use_hp_potion},
		{2, use_mp_potion},
		{3, use_atk_amp},
		{4, use_def_amp},
		{5, use_show_stats},
		{6, use_levelup}
	};

	setHPMP(stats);
	cout << "<스탯 관리 시스템>" << endl;
	cout << "1. HP UP" << endl;
	cout << "2. MP UP" << endl;
	cout << "3. 공격력 UP" << endl;
	cout << "4. 방어력 UP" << endl;
	cout << "5. 현재 능력치" << endl;
	cout << "6. Level Up" << endl;
	cout << "0. 나가기" << endl;
	int loopnums = -1;
	while (loopnums != 0)
	{
		cout << "번호를 입력하세요: ";
		cin >> loopnums;

		if (stats_map.count(loopnums))
		{
			stats_map[loopnums](stats);
		}
		else if (loopnums == 0)
		{
			cout << "프로그램을 종료합니다." << endl;
		}
		else
		{
			cout << "잘못된입력입니다" << endl;
		}
	}


	return 0;
	

	

	



}