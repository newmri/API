#include "Question2.h"

Question2::Question2()
{
	for (int i = 0; i < MAX_ARRAY; i++) m_array[i] = 0;
	m_select = 0;
	m_maxval = 0;
	m_minval = 0;
}

void Question2::GetData()
{
	cout << "Input Number: ";
	cin >> m_select;
	m_oldselect = m_select;
}

void Question2::GeneratePadding()
{
	unsigned int cnt{};
	unsigned int chk{};
	int temp{};
	srand((unsigned)time(NULL));
	while(MAX_ARRAY!=cnt-1) {
		if (0 == cnt) {
			temp = rand() % m_select;
			m_array[cnt] = temp;
			++cnt;
		}
		else {
			temp = rand() % m_select;
			for (int i = 0; i < MAX_ARRAY; ++i) {
				if (m_array[i] == temp) chk += 1;
			}
			if (0 == chk) {
				m_array[cnt] = temp;
				++cnt;	
			}
			chk = 0;
		}
	
		}
	
}

void Question2::ShowGeneratedPadding()
{
	cout << "Generated numbers: ";
	for (int i = 0; i < MAX_ARRAY; i++) cout << m_array[i] << " ";
	cout << endl;
}

void Question2::ShowPadding()
{
	for (int i = 0; i < MAX_ARRAY; i++) cout << m_array[i] << " ";
	cout << endl;
}

void Question2::GetCommand()
{
	while (true) {

		cin.ignore();
		ShowCommand();

		cout << "Command: ";
		cin >> m_commandselect;

		switch (m_commandselect) {
		case 'Q':
			cout << "Quit..." << endl;;
			return;
		case 'A':
			cout << "Ascending: ";
			OrderByAsc();
			ShowPadding();
			break;
		case 'D':
			cout << "Decending: ";
			OrderByDesc();
			ShowPadding();
			break;
		case 'R':
			break;
		case 'M':
			cout << "Max: ";
			ShowMaxVal();
			break;
		case 'I':
			cout << "Min: ";
			ShowMinVal();
			break;
		case 'S':
			InitArray();
			GeneratePadding();
			ShowGeneratedPadding();
			break;
		default:
			cout << "Error!" << endl;
			break;
		}

	}

}

void Question2::OrderByAsc()
{
	unsigned int tmp{};
	for (int i = 0; i < MAX_ARRAY; i++) {
		for (int j = 0; j < MAX_ARRAY - i - 1; j++) {
			if (m_array[j] > m_array[j + 1]) {
				tmp = m_array[j];
				m_array[j] = m_array[j + 1];
				m_array[j + 1] = tmp;
			}
		}
	}

}

void Question2::OrderByDesc()
{
	unsigned int tmp{};
	for (int i = 0; i < MAX_ARRAY; i++) {
		for (int j = 0; j < MAX_ARRAY - i - 1; j++) {
			if (m_array[j] < m_array[j + 1]) {
				tmp = m_array[j];
				m_array[j] = m_array[j + 1];
				m_array[j + 1] = tmp;
			}
		}
	}
}

void Question2::ShowMaxVal()
{
	unsigned int temp=m_array[0];
	for (int i = 1; i < MAX_ARRAY; i++) {
		if (temp < m_array[i]) temp = m_array[i];
	}
	m_maxval = temp;
	cout << m_maxval<<endl;

}

void Question2::ShowMinVal()
{
	unsigned int temp = m_array[0];
	for (int i = 1; i < MAX_ARRAY; i++) {
		if (temp > m_array[i]) temp = m_array[i];
	}
	m_minval = temp;
	cout << m_minval << endl;

}

void Question2::InitArray()
{
	for (int i = 0; i < MAX_ARRAY; i++) m_array[i] = 0;
	if (m_oldselect != m_select) m_select = m_oldselect;
}

void Question2::ShowCommand()
{
	cout << "A: OrderByAscending, D: OrderByDescending, R: OrderByRandom " << endl;
	cout << "M: ShowMaxValue, I: ShowMinValue, S: RegenerateAndShowPadding" << endl;
}