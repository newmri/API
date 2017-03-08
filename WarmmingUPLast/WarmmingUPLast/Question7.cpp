#include "Question7.h"
#include <string>

Question7::Question7()
{
	for (int i = 0; i < MAX_PLAYER; ++i) m_turn[i] = 0;
	m_count = 1;
	m_numcount = 0;
	m_index = 0;
	m_pchk = false;
}

void Question7::GetAndSetTurn()
{
	cout << "1: Player 2: Computer1 3: Computer2"<<endl;
	cout << "Decide turn: ";

	cin >> m_turn[MAX_PLAYER - 3] >> m_turn[MAX_PLAYER - 2] >> m_turn[MAX_PLAYER - 1];

	cin.ignore();
	cin.clear();
}


void Question7::PlayGame()
{
	
	while (true) {
		for (int i = 0; i < MAX_PLAYER; ++i) {
			switch (m_turn[i]) {

			case PLAYER: {
				m_pchk = true;
				for (m_index = 0; m_index < MAX_ARRAY; ++m_index) {
					scanf("%c", &m_num[m_index]);
					if (m_num[m_index] == '\n') break;
				}
				if (m_num[m_index - 2] == ' ' && m_num[m_index + 2] != ' ') m_count = atoi(&m_num[m_index - 1]);
				if (m_num[m_index] == '\n')  m_count = atoi(&m_num[m_index - 1]);
				if (m_num[m_index - 2] != ' ' && m_num[m_index - 1] != ' ' && (m_index - 2) != -1) {
					char* p = &m_num[m_index - 2];
					m_count = atoi(p);
					if (m_num[5] == ' ') m_numcount = 3;
				}

				if (m_index == 1 || m_index == 2) m_numcount = 1;
				else if ((m_index == 3 || m_index == 4) && m_numcount != 3) m_numcount = 2;
				else m_numcount = 3;

				
				if (10 < m_count) {
					cin.ignore();
					cin.clear();
				}

				m_count += 1;
				break;
			}

			case COM1: {

				srand((unsigned)time(NULL));
				int temp{};
				temp = (rand() % MAX_NUM) + 1;

				if (m_pchk) {
					while (true) {
						temp = (rand() % MAX_NUM) + 1;

						if (temp != m_numcount) break;

					}
				}
				cout << "Computer1: ";
				for (int i = 0; i < temp; ++i, ++m_count) {
					cout << m_count << " ";
				}
				cout << endl;
				m_pchk = false;
				break;
			}

			case COM2:

				srand((unsigned)time(NULL));

				int temp{};
				temp = (rand() % MAX_NUM) + 1;
				if (m_pchk) {
				while (true) {
					temp = (rand() % MAX_NUM) + 1;

					if (temp != m_numcount) break;

				}
			}
				cout << "Computer2: ";
				for (int i = 0; i < temp; ++i, ++m_count) {
					cout << m_count << " ";
				}
				cout << endl;
				m_pchk = false;
				break;

			}

		}
		m_numcount = 0;

	}

}