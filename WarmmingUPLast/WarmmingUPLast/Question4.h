#pragma once
#include <ctime>
#include "Common.h"
#define MAX_NUMBER 10

class Question4
{
private:
	unsigned int m_select;
	unsigned int m_row;
	unsigned int m_column;


public:
	void StoreData(int**, int, int);
	void ShowCommand();
	void MultiplyTwoToOdd();
	void MultiplyThreeToEven();
	void AddFourToMatrix();
	void ResetMatrix();
	void DeleteMatrix(int**, int);


};