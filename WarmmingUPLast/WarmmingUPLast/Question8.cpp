#include "Question8.h"



void Question8::GetYear()
{
	cout << "Input year:";
	cin >> m_year;
	switch (m_year) {
	case 2010: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}
	case 2011: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}
	case 2012: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}
	case 2013: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}
	case 2014: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}
	case 2015: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}
	case 2016: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}
	case 2017: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}
	case 2018: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}
	case 2019: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}
	case 2020: {
		IsLeapYear();
		if (GetMonth()) {
			if (GetDay()) ShowDateResult();
		}
		break;
	}

	default:
			cout << "You can input year between 2010 and 2020" << endl;
			break;
	}
	


}

bool Question8::GetMonth()
{
	cout << "Input month:";
	cin >> m_month;
	if (m_month > 12 || m_year < 0) {
		cout << "You can input month between 1 and 12" << endl;
		return false;
	}
	return true;
}
bool Question8::GetDay()
{
	cout << "Input date:";
	cin >> m_day;
	if (m_day > m_totalday[m_month]) {
		cout << "You can input day between 1 and "<<m_totalday[m_month] << endl;
		return false;
	}
	return true;
}

void Question8::ShowDateResult()
{
	m_date = ((21 * (YEAR / 100) / 4) + (5 * (YEAR % 100) / 4) + (26 * (MONTH + 1) / 10) + DAY - 1) % 7;
	
	switch (m_date) {
	case SUN:
		cout << YEAR << "/" << MONTH << "/" << DAY << ": " << "Sunday" << endl;
		break;
	case MON:
		cout << YEAR << "/" << MONTH << "/" << DAY << ": " << "Monday" << endl;
		break;
	case TUE:
		cout << YEAR << "/" << MONTH << "/" << DAY << ": " << "Thuesday" << endl;
		break;
	case WED:
		cout << YEAR << "/" << MONTH << "/" << DAY << ": " << "Wednesday" << endl;
		break;
	case FRI:
		cout << YEAR << "/" << MONTH << "/" << DAY << ": " << "Friday" << endl;
		break;
	case SAT:
		cout << YEAR << "/" << MONTH << "/" << DAY << ": " << "Saturday" << endl;
		break;



	}

	if (m_month == 1 || m_month == 2) {
		--m_year;
		m_month += 12;
		
		m_date = ((21 * (m_year / 100) / 4) + (5 * (m_year % 100) / 4) + (26 * (m_month + 1) / 10) + m_day - 1) % 7;
		
		switch (m_date) {
		case SUN:
			cout << m_year + 1 << "/" << m_month - 12 << "/" << m_day << ": " << "Sunday" << endl;
			break;
		case MON:
			cout << m_year + 1 << "/" << m_month - 12 << "/" << m_day << ": " << "Monday" << endl;
			break;
		case TUE:
			cout << m_year + 1 << "/" << m_month - 12 << "/" << m_day << ": " << "Thuesday" << endl;
			break;
		case WED:
			cout << m_year + 1 << "/" << m_month - 12 << "/" << m_day << ": " << "Wednesday" << endl;
			break;
		case FRI:
			cout << m_year + 1 << "/" << m_month - 12 << "/" << m_day << ": " << "Friday" << endl;
			break;
		case SAT:
			cout << m_year + 1 << "/" << m_month - 12 << "/" << m_day << ": " << "Saturday" << endl;
			break;

		}
		
	}

	else {

		m_date = ((21 * (m_year / 100) / 4) + (5 * (m_year % 100) / 4) + (26 * (m_month + 1) / 10) + m_day - 1) % 7;

		switch (m_date) {
		case SUN:
			cout << m_year << "/" << m_month << "/" << m_day << ": " << "Sunday" << endl;
			break;
		case MON:
			cout << m_year << "/" << m_month << "/" << m_day << ": " << "Monday" << endl;
			break;
		case TUE:
			cout << m_year << "/" << m_month << "/" << m_day << ": " << "Thuesday" << endl;
			break;
		case WED:
			cout << m_year << "/" << m_month << "/" << m_day << ": " << "Wednesday" << endl;
			break;
		case FRI:
			cout << m_year << "/" << m_month  << "/" << m_day << ": " << "Friday" << endl;
			break;
		case SAT:
			cout << m_year << "/" << m_month << "/" << m_day << ": " << "Saturday" << endl;
			break;

		}



	}


	}
	

