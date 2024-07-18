#include <graphics.h>
#include <time.h>
#include <iostream>
#include <stack>
#include <vector>
#include <conio.h> // 用于 _getch()
#include "Show.h"
#include "Chess.h"
#include "Users.h"
#pragma comment(lib,"Winmm.lib")
using namespace std;
constexpr int  Width = 800;
constexpr int  High = 640;
vector<vector<int>> map(18, vector<int>(18, -1)), cop(map);		//map是棋盘，-1空，0电脑，1友方
stack<pair<int, int>> stk;			//用以控制悔棋
double myPos = 0, aiPos = 0;		//我方和电脑棋局得分
int aiset;							//记录电脑上一步下的位置

int main() {
	MyChess mychs;
	Show s;
	AiChess ai;
	Users user;
	std::mutex mt;
	user.Read();
	while (1) {
		int t = 0;
		initgraph(Width, High);
		map = cop;
		mychs.steps = 0;
		while (1) {
			mychs.now = true;
			if (ai.gameOver(s, user)) {
				t++;
				break;
			}
			s.Mouse(mychs, user);	
			s.show(mychs, user);
			
			if (mychs.gameOver(s, user)) {
				t++;
				break;
			}
			mychs.now = false;
			ai.Get_key_Setchess(mychs);	
			s.show(mychs, user);
		}
		if (t == 5)
			break;//防上头
	}
}