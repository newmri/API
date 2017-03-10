#include "Question10.h"

Question10::Question10()
{
	m_year = 0;
	m_month = 0;
	m_day = 0;

}

void Question10::GetYear()
{

	cout << "Input year:";
	cin >> m_year;
	if (m_year < 2000 || m_year > 2100) {
		cout << "You can input year between 2010 and 2100" << endl;
		return;
	}

	IsLeapYear();
	ShowResult();
}

void Question10::IsLeapYear()
{
	if (m_year % 4 == 0 && ((m_year) % 100 != 0 || (m_year) % 400 == 0))
		m_totalday[2] = 29;

}

void Question10::ShowResult()
{
	m_month = 1;

	
		--m_year;
		m_month = 13;
		for (int date = 0; date <= m_totalday[2]; ++date) {
			m_day = ((21 * (m_year / 100) / 4) + (5 * (m_year % 100) / 4) + (26 * (m_month + 1) / 10) + date - 1) % 7;
			if (m_day == 5 && date == 13) cout <<m_year+1<<"-"<<m_month-12<<"-"<<date<<" friday" << endl;
		}

		m_month = 14;
		for (int date = 0; date <= m_totalday[3]; ++date) {
			m_day = ((21 * (m_year / 100) / 4) + (5 * (m_year % 100) / 4) + (26 * (m_month + 1) / 10) + date - 1) % 7;
			if (m_day == 5 && date == 13) cout << m_year + 1 << "-" << m_month - 12 << "-" << date << " friday" << endl;
		}
		m_month = 3;
		++m_year;
	
	for (int i = 3; i <= 12; ++i, ++m_month) {

		if (m_month <= 2) {
			--m_year;
			m_month = m_month + 12;

		}

		for (int date = 0; date <= m_totalday[i]; ++date) {
			m_day = ((21 * (m_year / 100) / 4) + (5 * (m_year % 100) / 4) + (26 * (m_month + 1) / 10) + date - 1) % 7;
			if (m_day == 5 && date == 13) cout << m_year << "-" << m_month << "-" << date << " friday" << endl;
		}

	}







}