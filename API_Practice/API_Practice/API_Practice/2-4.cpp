/* 화면에 숫자 쓰기

화면의 9개의 임의의 위치를 정하고 각 위치에 1부터 9까지의 숫자를 숫자행 숫자열에 맞게 쓴다

1 22
  22

333
333
333
*/

#include <windows.h>
#include <atlstr.h>
#include <time.h>

#define MAX_ROOP 9
#define WINDOW_X 800
#define WINDOW_Y 600
#define POINT_INCREMENT 20

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
	int nX{}, nY{};
	switch (iMessage) {
	case WM_CREATE: {
		break;
	}
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		srand((unsigned)time(NULL));
		for (int i = 0; i < MAX_ROOP; ++i) {

			nX = rand() % WINDOW_X / 2 + 1;
			nY = rand() % WINDOW_Y / 2 + 1;

			rect.left = nX;
			rect.right = nX + POINT_INCREMENT;
			rect.top = nY;
			rect.bottom = nY + POINT_INCREMENT;


			for (int nRow = 0; nRow < i; ++nRow) {
				cStr.Format("%d", i);
				DrawText(hdc, cStr, cStr.GetLength(), &rect, DT_CENTER);
				rect.left += POINT_INCREMENT;
				rect.right += POINT_INCREMENT;
			}

			for (int j = 1; j < i; ++j) {
				rect.top += POINT_INCREMENT;
				rect.bottom = rect.top + POINT_INCREMENT;
				rect.left = nX;
				rect.right = rect.left + POINT_INCREMENT;

				for (int nColumn = 0; nColumn < i; ++nColumn) {
					cStr.Format("%d", i);
					DrawText(hdc, cStr, cStr.GetLength(), &rect, DT_CENTER);
					rect.left += POINT_INCREMENT;
					rect.right += POINT_INCREMENT;
				}
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