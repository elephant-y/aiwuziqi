#pragma once
#ifndef SHOW_H
#define SHOW_H
#include "Class.h"
#include "Users.h"
#include <graphics.h>
#include <time.h>
#include <string>
#include <stack>
#include <vector>
/*������ת��Ϊʵ��λ��*/
template<typename T> constexpr auto switch_xy(T x) { return x * 30 + 20; }

/*��ʵ��λ��ת��Ϊ����*/
template<typename T> constexpr auto reswitch_xy(T x) { return (x - 20) / 30; }
class Show
{
public:
	void show(MyChess& mychs, Users& user);		/*���ƺ���*/
	void setChess(int x, int y, int choice);	/*���庯����choice���ó�0Ϊ�����£�1Ϊ�ҷ�*/
	void Mouse(MyChess& mychs, Users& user);	/*������Ӧ���*/
	void End(int who, Users& user, int steps);	/*��Ϸ��������ҳ��*/
};

#endif // !SHOW_H



