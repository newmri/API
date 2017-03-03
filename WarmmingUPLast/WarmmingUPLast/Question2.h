#pragma once

#include <random>
#include <stdlib.h>
#include <ctime>

#include "Common.h"
#define MAX_ARRAY 20

class Question2
{
private:
	unsigned int m_array[20];
	unsigned int m_select;
	unsigned int m_maxval;
	unsigned int m_minval;
	char m_commandselect;
	

public:
	Question2();
	void GetData();
	void GeneratePadding();
	void ShowGeneratedPadding();
	void ShowPadding();
	void GetCommand();
	void OrderByAsc();
	void OrderByDesc();
	void ReArray();
	void ShowMaxVal();
	void ShowMinVal();
	void ReGenerate();

};