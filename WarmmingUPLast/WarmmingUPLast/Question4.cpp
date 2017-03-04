#include "Question4.h"

void Question4::StoreData(int** parr, int column, int row)
{
	srand((unsigned)time(NULL));

		for(int i=0; i<column; ++i){
			for (int j = 0; j < row; ++j) parr[i][j]= rand() % MAX_NUMBER;
		}
	
}

void Question4::ShowCommand()
{
	cout << "Command 1: Multiply number two to column of odd and print out" << endl;
	cout << "Command 2: Multiply number three to row of even and print out" << endl;
	cout << "Command 3: Add number four to matrix and print out" << endl;
	cout << "Command 4: Reset initial matrix and print out" << endl;
	cout << "Command: ";
}

void Question4::DeleteMatrix(int** parr, int column)
{
	for (int i = 0; i < column; ++i) {
		delete[] parr[i];
	}
	delete[] parr;

}