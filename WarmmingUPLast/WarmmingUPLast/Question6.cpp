#include "Question6.h"

Question6::Question6()
{
	for (int i = 0; i < MAX_DATA_NUM; ++i) {
		memset(&m_data[i], 0, sizeof(m_data[i]) - 4);
		m_data[i].m_datatype = DEFAULT;
	}

	
}


void Question6::GetPoint()
{
	cout << "Input 2 points: ";
	cin >> m_data[0].m_lx >> m_data[0].m_ly >> m_data[0].m_rx >> m_data[0].m_ry;
	cout << endl;
}

void Question6::GetCommand()
{

	cout << "Input Command:";
	cin >> m_command;
	switch (m_command) {
	case IN_CIRCLE:
		m_data[0].m_datatype = CIRCLE;
		break;
	case IN_RECTANGLE:
		break;
	case IN_TRIANGLE:
		break;
	case IN_PRINTOUT:
		break;

	}
}