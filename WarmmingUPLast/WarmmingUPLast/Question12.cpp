#include "Question12.h"

Question12::Question12()
{

	m_firstdraw = true;
	m_drawomok = true;
}
void Question12::ShowMap()
{
	system("cls");
	cout << endl;
	cout << "---------------------" << endl;
	cout << "| | | | | | | | | | |" << endl;
	cout << "---------------------" << endl;
	cout << "| | | | | | | | | | |" << endl;
	cout << "---------------------" << endl;

	if (m_firstdraw) {
		GoToXY(1, 2);
		m_firstdraw = false;
	}

	if (m_drawomok) {
		switch (m_command) {
		case 'w':
			GoToXY(m_omokx, m_omoky - 2);
			cout << "O";
			break;
		case 's':
			GoToXY(m_omokx, m_omoky + 2);
			cout << "O";
			break;
		case 'a':
			GoToXY(m_omokx -2 , m_omoky);
			cout << "O";
			break;
		case 'd':
			GoToXY(m_omokx + 2, m_omoky);
			cout << "O";
			break;
		default:
			cout << "O";
			break;
		}
	}

	m_drawomok = false;

	GetCommand();
}

void Question12::GetCommand()
{
	GoToXY(0, 0);
	cout << "Input command: " << endl;
	GoToXY(14, 0);
	cin >> m_command;

	m_drawomok = true;

}

bool Question12::BoundCheck(int x, int y)
{
	if (y < MIN_Y || y > MAX_Y || x > MAX_X || x < MIN_X) {
		GoToXY(m_omokx, m_omoky);
		return true;
	}
	return false;
}

void Question12::GoToXY(int x, int y)
{


	COORD cur;
	if (m_drawomok) {
		if (BoundCheck(x, y)) return;
	}

	cur.X = x;
	cur.Y = y;
	if (m_drawomok) {
		m_omokx = cur.X;
		m_omoky = cur.Y;
	}
	else {
		m_curx = cur.X;
		m_cury = cur.Y;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

}