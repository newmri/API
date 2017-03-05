#include "Question4.h"

void Question4::StoreData(int** parr, int column, int row)
{
	srand((unsigned)time(NULL));

		for(int i=0; i<column; ++i){
			for (int j = 0; j < row; ++j) parr[i][j]= rand() % MAX_NUMBER;
		}

		m_column = column;
		m_row = row;

		int** tempparr = new int*[column];

		for (int i = 0; i < column; ++i) {
			tempparr[i] = new int[row];
			memset(tempparr[i], 0, sizeof(int)*row);
		}

		for (int i = 0; i<column; ++i) {
			for (int j = 0; j < row; ++j) tempparr[i][j] = parr[i][j];
		}
		
		m_parr = tempparr;
	
}

void Question4::ShowCommand()
{
	cout << "Command 1: Multiply number two to column of odd and print out" << endl;
	cout << "Command 2: Multiply number three to row of even and print out" << endl;
	cout << "Command 3: Add number four to matrix and print out" << endl;
	cout << "Command 4: Reset initial matrix and print out" << endl;
	cout << "Command: ";
}

void Question4::MultiplyTwoToOdd(int** parr)
{
	for (int i = 0; i < m_column; ++i) {
		if (i+1 & 1) {
			for (int j = 0; j < m_row; ++j)  parr[i][j] *= 2;
		}
		
	}

}

void Question4::MultiplyThreeToEven(int** parr)
{
	for (int i = 0; i < m_column; ++i) {
			for (int j = 0; j < m_row; ++j){
				if (!(j + 1 & 1)) parr[i][j] *= 3;
		}

	}

}

void Question4::ResetMatrix(int** parr)
{
	for (int i = 0; i<m_column; ++i) {
		for (int j = 0; j < m_row; ++j) parr[i][j] = m_parr[i][j];
	}

}
void Question4::DeleteMatrix(int** parr, int column)
{
	for (int i = 0; i < column; ++i) {
		delete[] parr[i];
	}
	delete[] parr;

	for (int i = 0; i < column; ++i) {
		delete[] m_parr[i];
	}
	delete[] m_parr;

}