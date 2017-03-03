#include "MainSelect.h"

bool MainSelect()
{
	unsigned int select{};

	cout << "Select number: ";
	cin >> select;

	bool except = ExceptionHandling();
	if (!except) return false;

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
		break;
	}
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
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
	return true;

}