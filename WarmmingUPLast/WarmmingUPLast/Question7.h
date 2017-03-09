#pragma once
#include <ctime>
#include "Common.h"

#define MAX_PLAYER 3
#define MAX_NUM 3
#define MAX_ARRAY 8

enum { PLAYER = 1, COM1, COM2 };

class Question7
{
private:
	unsigned int m_turn[MAX_PLAYER];
	unsigned int m_count;
	unsigned int m_numcount;
	unsigned int m_index;
	bool m_pchk;
	bool m_gamestart;
	char m_num[MAX_ARRAY];
public:
	Question7();
	void GetAndSetTurn();
	void PlayGame();
};

