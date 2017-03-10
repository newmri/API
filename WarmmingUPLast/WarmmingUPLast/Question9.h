#pragma once

#include "Common.h"

#define MAX_NUM 20

class Question9
{
private:
	char m_num[MAX_NUM];
	char m_oldnum[MAX_NUM];
	unsigned short m_len;
public:
	Question9();
	void GetNumber();
	void Process();
	void ShowResult();
};