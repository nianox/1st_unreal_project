#include "player.h"
#include<iostream>

Player::Player(string nickname) : nickname(nickname)
{
	//default;
	this->level = 0;
	this->HP = 0;
	this->MP = 0;
	this->power = 0;
	this->defence = 0;
	this->accuracy = 0;
	this->speed = 0;
}

void Player::printPlayerStatus() {
    cout << "------------------------------------" << endl;
    cout << "* 현재 능력치" << endl;
    cout << "닉네임: " << nickname << endl;
    cout << "Lv. " << level << endl;
    cout << "HP: " << HP << endl;
    cout << "MP: " << MP << endl;
    cout << "공격력: " << power << endl;
    cout << "방어력: " << defence << endl;
    cout << "정확도: " << accuracy << endl;
    cout << "속도: " << speed << endl;
    cout << "------------------------------------" << endl;
}

string Player::getJobName()
{
    return job_name;
}

string Player::getNickname()
{
    return nickname;
}

int Player::getLevel()
{
    return level;
}
int Player::getHP()
{
    return HP;
}
int Player::getMP()
{
    return MP;
}
int Player::getPower()
{
    return power;
}
int Player::getDefence()
{
    return defence;
}
int Player::getAccuracy()
{
    return accuracy;
}
int Player::getSpeed()
{
    return speed;
}

void Player::setNickname(string nickname)
{
    this->nickname = nickname;
}

//이게 맞아?
bool Player::setHP(int HP)
{
    if (HP <= 0)
    {
        this->HP = 0;
        return false;
    }
    this->HP = HP;
    return true;
}// gethp를 통해서 체력을 얻을테고 외부에서 공격이 와서 체력이 줄어들었다면 해당 공격데미지를 계산한 결과를 hp로 입력
//헤더에서 bool로 설정되어 있는 이유를 캐릭터가 시체인지 아닌지를-
bool Player::setMP(int MP)
{
    if (MP <= 0)
    {
        this->MP = 0;
        return false;
    }
    this->MP = MP;
    return true;
}
void Player::setPower(int power)
{
    this->power = power;
}
void Player::setDefence(int defence)
{
    this->defence = defence;
}
void Player::setAccuracy(int accuracy)
{
    this->accuracy = accuracy;
}

void Player::setSpeed(int speed)
{
    this->speed = speed;
}