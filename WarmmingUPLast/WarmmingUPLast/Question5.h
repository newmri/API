#pragma once
#include <string>
#include "Common.h"

#define MAX_SIZE 7
#define MAX_OPERATOR 4
#define MAX_TEMP_ARRAY_SIZE 3

class Question5
{
private:
	char m_equation[MAX_SIZE];
	char m_temparray[MAX_TEMP_ARRAY_SIZE];

	unsigned int m_lvalue;
	unsigned int m_rvalue;
	unsigned int m_result;

	bool m_errchk;
public:
	Question5();
	bool GetEquation();
	void CheckError();
	void DevideEquation();
	void CalculateByOperator();
	void ShowReulst();

};
