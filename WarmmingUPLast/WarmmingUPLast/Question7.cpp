#include "Question7.h"

Question7::Question7()
{
	for (int i = 0; i < MAX_PLAYER; ++i) m_turn[i] = 0;
	m_count = 0;
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
				cout << "Enter number: ";

				for (m_index = 0; m_index < MAX_ARRAY; ++m_index) {
					scanf("%c", &m_num[m_index]);
					if (m_num[m_index] == '\n') break;	
				}
				cout << atoi(&m_num[m_index-1]) << endl;
				break;
			}
				
			case COM1:
				break;
			case COM2:
				break;

			}

		}
		

	}

}