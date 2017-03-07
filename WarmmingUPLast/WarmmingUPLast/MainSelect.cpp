#include "MainSelect.h"

bool MainSelect()
{
	unsigned int select{};

	cout << "Select number: ";
	cin >> select;

	if (!ExceptionHandling()) return false;

	switch (select) {
	case 0:
		cout << "Exit..." << endl;
		return false;
	case 1:
		ShowMultipleResult();
		break;
	case 2: {
		Question2 quest2;
		quest2.GetData();
		quest2.GeneratePadding();
		quest2.ShowGeneratedPadding();
		quest2.GetCommand();
		break;
	}
	case 3: {
		Question3 quest3;
		quest3.GetSentence();
		quest3.ShowSentence();
		quest3.ModifySentence();
		break;
	}
	case 4: {
		Question4 quest4;
		cout << "Column, row input: ";
		unsigned int column{};
		unsigned int row{};
		unsigned int select{};
		cin >> column >> row;
		 
		if (column > MAX_NUMBER || row > MAX_NUMBER) {
			cout << "Error has been occured!" << endl;
			return false;
		}


		int **arr = new int*[column];

		for (int i = 0; i < column; ++i) {
			arr[i] = new int[row];
			memset(arr[i], 0, sizeof(int)*row);
		}

		quest4.StoreData(arr,column,row);

		for (int i = 0; i < column; ++i) {
			for (int j = 0; j < row; ++j) cout << arr[i][j] << "  ";
			cout << endl;
		}

		while (true) {
			quest4.ShowCommand();
			cin >> select;

			if (!ExceptionHandling()) return false;

			switch (select) {
			case 0:
				cout << "Exit..." << endl;
				return false;
			case 1:
				quest4.MultiplyTwoToOdd(arr);
		
				for (int i = 0; i < column; ++i) {
					for (int j = 0; j < row; ++j) cout << arr[i][j] << "  ";
					cout << endl;
				}

				break;
			case 2:
				quest4.MultiplyThreeToEven(arr);

				for (int i = 0; i < column; ++i) {
					for (int j = 0; j < row; ++j) cout << arr[i][j] << "  ";
					cout << endl;
				}

				break;
			case 3:
				quest4.AddFourToMatrix(arr);
				for (int i = 0; i < column; ++i) {
					for (int j = 0; j < row; ++j) cout << arr[i][j] << "  ";
					cout << endl;
				}

				break;
			case 4:
				quest4.ResetMatrix(arr);

				for (int i = 0; i < column; ++i) {
					for (int j = 0; j < row; ++j) cout << arr[i][j] << "  ";
					cout << endl;
				}

				break;

			default:
				cout << "Error has been occured!" << endl;
				return false;
			}

		}
		quest4.DeleteMatrix(arr, column);
		break;
	}
		
	case 5: {
		Question5 quest5;

		if (quest5.GetEquation()) quest5.CalculateByOperator();

		break;
	}
	case 6:
		break;
	case 7: {
		Question7 quest7;
		quest7.GetAndSetTurn();
		quest7.PlayGame();
		break;
	}
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	default:
		cout << "Error has been occured!" << endl;
		return false;
	}

	cin.ignore();
	cin.clear();
	return true;

}