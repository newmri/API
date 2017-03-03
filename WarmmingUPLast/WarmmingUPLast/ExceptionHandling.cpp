#include "ExceptionHandling.h"

bool ExceptionHandling()
{
	if (cin.fail()) {
		cin.clear();
		cout << "Error!" << endl;
		return false;
	}
	
	else return true;

}