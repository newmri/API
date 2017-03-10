#pragma once
#include "Question10.h"

enum { SUN = 0, MON, TUE, WED, THU, FRI, SAT };
enum { YEAR = 2017, MONTH = 3, DAY = 1 };
class Question8 : public Question10
{
private:
	unsigned short m_inputdate;
	unsigned short m_date;
public:
	void GetYear();
	bool GetMonth();
	bool GetDay();
	void ShowDateResult();

};