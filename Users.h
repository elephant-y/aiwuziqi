#pragma once
#ifndef  USERS_H
#define  USERS_H
#include <fstream>
class Users {
public:
	int wincnt = 0;		/*ʤ������*/
	int failcnt = 0;	/*ʧ�ܳ���*/
	int drawcnt = 0;	/*ƽ�ֳ���*/
	int minsteps = 0;	/*ʤ����̲���*/
	int restcnt = 10;	/*ʣ����岽��*/
	void Read(void);	/*��ȡ�ĵ�*/
	void Write(void);	/*�浵*/
};
#endif // ! USERS_H