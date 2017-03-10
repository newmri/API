#pragma once
#include "Common.h"

class Question10
{
private:
	unsigned short m_year;
	unsigned short m_month;
	unsigned short m_day;
	unsigned short m_totalday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
public:
	Question10();
	void GetYear();
	void IsLeapYear();
	void ShowResult();



};