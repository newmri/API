#include "ExceptionHandling.h"

bool ExceptionHandling()
{
	if (cin.fail()) {
		cin.clear();
		cout << "Error has been occured! You r able to enter number only dude!" << endl;
		return false;
	}
	
	else return true;

}