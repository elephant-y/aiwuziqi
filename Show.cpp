#include "Show.h"
#include "Chess.h"
#include <vector>
#include<windows.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;
extern int aiset;
extern stack<pair<int, int>> stk;
extern vector<vector<int>> map;
extern double myPos, aiPos;
static const char dir1[] = { "ABCDEFGHIJKLMNOPQR" };
static const char dir2[] = { "123456789ABCDEFGHI" };
void Show::show(MyChess& mychs, Users& user)
{
	BeginBatchDraw();
	setbkcolor(YELLOW);
	cleardevice();
	setcolor(BLACK);
	TCHAR row, col;
	for (int i = 20; i <= 530; i += 30) {
		line(20, i, 530, i);
		line(i, 20, i, 530);
		row = dir1[reswitch_xy(i)];
		col = dir2[reswitch_xy(i)];
		outtextxy(5, i - 7, row);
		outtextxy(i - 5, 545, col);
	}
	setfillcolor(BLACK);
	/*4��С�ڵ�*/
	fillcircle(170, 170, 3);
	fillcircle(170, 380, 3);
	fillcircle(380, 170, 3);
	fillcircle(380, 380, 3);
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 18; j++) {
			if (map[i][j] != -1) {
				setChess(switch_xy(i), switch_xy(j), map[i][j]);
			}
		}
	}
	TCHAR str[250];
	wchar_t* wstr = new wchar_t[100];
	//double nowTime = clock(), sec = 20 - ((nowTime - startTime) / CLOCKS_PER_SEC);
	mychs.get_grade(user, wstr);
	setcolor(BLACK);
	/*��ʾ�û���Ϣ*/
	outtextxy(600, 5, _T("�û���Marmot"));
	_stprintf_s(str, _T("ʤ����%d"), user.wincnt);
	outtextxy(600, 25, str);
	_stprintf_s(str, _T("������%d"), user.failcnt);
	outtextxy(600, 45, str);
	_stprintf_s(str, _T("ƽ�֣�%d"), user.drawcnt);
	outtextxy(600, 65, str);
	_stprintf_s(str, _T("ʤ�ʣ�%.2f%%"), user.failcnt ? (double)user.wincnt / (double)(user.wincnt + user.failcnt) * 100: 0);
	outtextxy(600, 85, str);
	_stprintf_s(str, _T("��λ��%s"), wstr);
	outtextxy(600, 105, str);
	_stprintf_s(str, _T("ʤ����̲���: %d"), user.minsteps);
	outtextxy(600, 125, str);
	_stprintf_s(str, _T("ʣ����岽��: %d"), user.restcnt);
	outtextxy(600, 145, str);

	setcolor(BLUE);
	line(580, 2, 580, 170);
	line(580, 170, 735, 170);
	line(735, 170, 735, 2);
	line(580, 2, 735, 2);
	setcolor(BLACK);

	_stprintf_s(str, _T("����ǰ���� %d ��"), mychs.steps);
	outtextxy (600, 195, str);
	outtextxy(600, 225, _T("��ǰ������У�"));

	setcolor(RED);
	rectangle(620, 265, 680, 305);
	outtextxy(634, 276, _T("����"));
	setcolor(BLACK);

	_stprintf_s(str, _T("���Ըղ�����λ�ã�%c�� %c��"), dir1[aiset & 0x1f], dir2[aiset >> 5]);
	outtextxy(570, 330, str);
	
	_stprintf_s(str, _T("������ֵ÷�: %.1f"), myPos);
	outtextxy(570, 370, str);
	_stprintf_s(str, _T("�Է���ֵ÷�: %.1f"), aiPos);
	outtextxy(570, 410, str);
	mychs.get_assuse(wstr);
	_stprintf_s(str, _T("��ǰ�������������%s"), wstr);
	outtextxy(570, 450, str);

	if (mychs.now == true) {
		outtextxy(180, 595, _T("���������Ļغϣ�������..."));
	}
	else
		outtextxy(160, 595, _T("�����ǶԷ��Ļغϣ������ȴ�..."));
	FlushBatchDraw();
	EndBatchDraw();
	return;
}

void Show::setChess(int x, int y, int choice)//0Ϊ�������壬1Ϊ�Լ�����
{
	setfillcolor(BLACK);
	if (!choice) 
		setfillcolor(WHITE);
	fillcircle(x, y, 14);
	return;
}

void Show::Mouse(MyChess& mychs, Users& user)
{
	MOUSEMSG m;
	while (true) {
		TCHAR str[250];
		m = GetMouseMsg();
		int x = m.x, y = m.y;
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:	
			show(mychs, user);
			if (mychs.Get_xy(x, y) && map[reswitch_xy(x)][reswitch_xy(y)] == -1) {
				int x1 = reswitch_xy(x), y1 = reswitch_xy(y);
				_stprintf_s(str, _T("%c�� %c��"), dir1[y1], dir2[x1]);
				outtextxy(705, 225, str);
				circle(x, y, 14);		
			}
			else if (m.x > 620 && m.x < 680 && m.y > 265 && m.y < 305) {
				setcolor(BLUE);
				rectangle(620, 265, 680, 305);
				outtextxy(634, 276, _T("����"));
				setcolor(BLACK); 
			}
			break;

		case WM_LBUTTONUP:
			/*����*/
			if (mychs.Get_xy(x, y) && map[reswitch_xy(x)][reswitch_xy(y)] == -1) {
				int x1 = reswitch_xy(x), y1 = reswitch_xy(y);
				stk.push({ aiset, (x1 << 5) | y1 });
				map[x1][y1] = 1;
				mychs.now = false;
				mychs.steps++;
				myPos = mychs.GetNowPoints(1);
				aiPos = mychs.GetNowPoints(0);
				mciSendString(_T("close chs"), NULL, 0, NULL);
				mciSendString(_T("open setChs.wav alias chs"), NULL, 0, NULL);
				mciSendString(_T("play chs"), NULL, 0, NULL);
				return;
			}
			/*����*/
			else if (m.x > 620 && m.x < 680 && m.y > 265 && m.y < 305) {
				if (!user.restcnt){
					MessageBox(0, _T("��û�л�������ˣ�����Ӯ���Ի�ø������ɣ�"), _T("NO"), 0);
					continue;
				}
				if (stk.empty()) {
					MessageBox(0, _T("�����޷����壡"), _T("NO"), 0);
					continue;
				}				
				auto it = stk.top();
				stk.pop();
				int ai = it.first, self = it.second;			
				map[self >> 5][self & 0x1f] = -1;
				map[aiset >> 5][aiset & 0x1f] = -1;
				aiset = ai;

				myPos = mychs.GetNowPoints(1);
				aiPos = mychs.GetNowPoints(0);
				user.restcnt--;
				user.Write();
				show(mychs, user);
				return Mouse(mychs, user);
			}
		}
	}
	return;
}

void Show::End(int who, Users& user, int steps){
	if (!who) return;
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 20;						// ��������߶�Ϊ 48
	wcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	outtextxy(615, 500, _T("��Ϸ����"));
	if (who == 1) {
		user.wincnt++;
		user.restcnt += 10;
		if (user.minsteps == 0)
			user.minsteps = steps;
		else
			user.minsteps = min(user.minsteps, steps);
		mciSendString(_T("close win"), NULL, 0, NULL);
		mciSendString(_T("open win.wav alias win"), NULL, 0, NULL);
		mciSendString(_T("play win"), NULL, 0, NULL);
		MessageBox(NULL, _T("��ϲ��ʤ����"), _T("��Ϸʤ��"), MB_OK | MB_ICONINFORMATION);
	}
	else {
		user.failcnt++;
		mciSendString(_T("close det"), NULL, 0, NULL);
		mciSendString(_T("open defet.mp3 alias det"), NULL, 0, NULL);
		mciSendString(_T("play det"), NULL, 0, NULL);
		MessageBox(NULL, _T("�Ծ�ʧ�ܣ�"), _T("��Ϸ����"), MB_OK | MB_ICONINFORMATION);
	}

	while (!stk.empty()) {
		stk.pop();
	}
	aiPos = 0;
	myPos = 0;
	closegraph();
	return;
}

