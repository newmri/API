#pragma once
#include <Windows.h>
#include <conio.h>

#include "Common.h"

enum {MIN_X = 1, MIN_Y = 2, MAX_X = 20, MAX_Y = 4};

class Question12
{
private:
	unsigned int m_curx, m_cury;
	unsigned int m_omokx, m_omoky;
	char m_command;
	bool m_firstdraw;
	bool m_drawomok;
public:
	Question12();
	void ShowMap();
	void GetCommand();
	bool BoundCheck(int, int);
	void GoToXY(int, int);
};