#pragma once
#include <ctime>
#include "Common.h"
#define MAX_NUMBER 10

class Question4
{
private:
	int** m_parr;
	unsigned int m_column;
	unsigned int m_row;

public:
	void StoreData(int**, int, int);
	void ShowCommand();
	void MultiplyTwoToOdd(int**);
	void MultiplyThreeToEven(int**);
	void AddFourToMatrix(int**);
	void ResetMatrix(int**);
	void DeleteMatrix(int**, int);


};