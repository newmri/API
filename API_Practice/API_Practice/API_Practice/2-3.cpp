#include <windows.h>
#include <atlstr.h>
#include <time.h>

#define MAX_COLUMN 20
#define WINDOW_X 800
#define WINDOW_Y 600
#define FIRST_X  WINDOW_X / 4
#define FIRST_ROW 1
#define MAX_ROW 5
HINSTANCE g_hInst;
LPCTSTR lpszClass = "Windows";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	// 윈도우 클래스 구조체 값 설정
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// 윈도우 클래스 등록
	RegisterClassEx(&WndClass);
	// 윈도우 생성
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, WINDOW_X, WINDOW_Y, NULL, (HMENU)NULL, hInstance, NULL);
	// 윈도우 출력
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// 이벤트 루프 처리
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	CString cStr;
	int x{ FIRST_X }, y{};
	int nBlankX{}, nBlankY{};
	int nLeftEnd{}, nRightEnd{ 800 };
	int j{1};
	int nColumn{ 1 };
	int nRow{ FIRST_ROW };
	static int nRandomNum{};
	int nPermanentY{};
	int nBeforeNum{};
	int nBeforeColumn{};
	switch (iMessage) {
	case WM_CREATE: {
		srand((unsigned)time(NULL));
		nRandomNum = rand() % 6 + 1;
		break;
	}
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);

		for (int i = 1; i <= MAX_COLUMN; ++i) {
			for (int line = 0; line < 2; ++line) {
				rect.left = x;
				rect.right = x += 100;
				if (line == 0) {
					nBeforeNum = y;
					nBeforeColumn = nColumn;
				}
				for (int j = 0; j <nRandomNum; ++j, ++nColumn) {
					rect.top = y;
					rect.bottom = y += 20;
					cStr.Format("(%d, %d)", nColumn, nRow);
					if(nColumn <= MAX_COLUMN)
					DrawText(hdc, cStr, cStr.GetLength(), &rect, DT_LEFT);
				}
				++nRow;
				if (nRow == MAX_ROW) nRow = FIRST_ROW;
			}
			//nPermanentY = y;
			if (i % 2 != 0) {
				y = nBeforeNum;
				nColumn = nBeforeColumn;
			}
			else {
				x = FIRST_X;
				y = y;
			}


		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam); // 위의 세 메시지 외의 나머지 메시지는 OS로
}