#include "Question7.h"
#include <string>

Question7::Question7()
{
	for (int i = 0; i < MAX_PLAYER; ++i) m_turn[i] = 0;
	m_count = 1;
	m_numcount = 0;
	m_index = 0;
	m_pchk = false;
	m_gamestart = true;
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



				if (8 == m_index) {
					cin.ignore();
					cin.clear();
				}

				if (31 == m_count) {
					cout << "You lost" << endl;
					return;
				}

				if (m_count != 30 || m_count != 29) { m_count += 1; }
				break;
			}

			case COM1: {
				if (!m_pchk) {
					if (30 == m_count) {
						m_count += 1;
						cout << "Computer1: " << m_count << endl;
						cout << "Computer1 Lost!" << endl;
						m_pchk = false;
						return;
					}
				}

				bool skip = false;
				srand((unsigned)time(NULL));
				int temp{};
				temp = (rand() % MAX_NUM) + 1;


				if (m_pchk) {
					while (true) {
						temp = (rand() % MAX_NUM) + 1;

						if (temp != m_numcount) {
							if (30 == m_count) {
								cout << "Computer1: " << m_count << endl;
								skip = true;
								break;
							}
							if (31 == m_numcount + temp) continue;
							else break;
						}

					}
				}
				
					while (31 == (m_numcount + temp-1)) temp = (rand() % MAX_NUM) + 1;
					
				
				if (!skip) {
					cout << "Computer1: ";

					for (int i = 0; i < temp; ++i, m_count++) {
						if (m_count != 31 || m_count != 30 || m_count != 29) {
							if (m_count == 31) {
								cout << m_count << endl;
								cout << "Computer1 Lost!" << endl;
								m_pchk = false;
								return;
							}
							cout << m_count << " ";
						}
						else m_count++;

						if (31 <= m_count) {
							cout << m_count << endl;
							cout << "Computer1 Lost!" << endl;

							m_pchk = false;
							return;
						}
					}

					cout << endl;



				}
				m_pchk = false;
				break;

			}

			case COM2:
				if (!m_pchk) {
					if (30 == m_count) {
						m_count += 1;
						cout << "Computer2: " << m_count << endl;
						cout << "Computer2 Lost!" << endl;
						m_pchk = false;
						return;
					}
				}
				bool skip = false;
				srand((unsigned)time(NULL));

				int temp{};
				temp = (rand() % MAX_NUM) + 1;
				if (m_pchk) {
					while (true) {
						temp = (rand() % MAX_NUM) + 1;
						if (temp != m_numcount) {
							if (30 == m_count) {
								cout << "Computer2: " << m_count << endl;
								skip = true;
								break;
							}
							if (temp != m_numcount) {
								if (31 == m_numcount + temp) continue;
								else break;
							}

						}
					}
				}
				while (31 == (m_numcount + temp - 1)) temp = (rand() % MAX_NUM) + 1;
				if (!skip) {
					cout << "Computer2: ";
					for (int i = 0; i < temp; ++i, m_count++) {
						if (m_count != 31 || m_count != 30 || m_count != 29) {
							if (m_count == 31) {
								cout << m_count << endl;
								cout << "Computer2 Lost!" << endl;
								m_pchk = false;
								return;
							}
							cout << m_count << " ";
						}
						else m_count++;

						if (31 <= m_count) {
							cout << m_count << endl;
							cout << "Computer2 Lost!" << endl;
							m_pchk = false;
							return;
						}
					}
					cout << endl;

				}
					m_pchk = false;
					break;

				
			}
				
		}
		m_numcount = 0;

	}

}