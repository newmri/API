#pragma once
#include "Common.h"

#define MAX_DATA_NUM 10

enum DATATYPE {DEFAULT, CIRCLE, RECTANGLE, TRIANGLE };
enum { IN_CIRCLE = 1, IN_RECTANGLE, IN_TRIANGLE, IN_PRINTOUT };
#pragma pack(1)
struct Data
{
	unsigned short m_lx, m_rx, m_ly, m_ry;
	unsigned short m_area;
	DATATYPE m_datatype;
};

class Question6
{
private:
	Data m_data[MAX_DATA_NUM];
	unsigned short m_command;
public:
	Question6();
	void GetPoint();
	void GetCommand();
};