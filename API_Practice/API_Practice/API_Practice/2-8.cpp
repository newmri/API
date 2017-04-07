#include <windows.h>
#include <stdio.h>
#include <time.h>
#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOW_X 800
#define WINDOW_Y 600
#define PEN_WIDTH 3
#define MAX_RECTANGLE_X 6
#define MAX_RECTANGLE_Y 6
#define FIRST_RECTANGLE_X 5
#define FIRST_RECTANGLE_Y 10
#define LAST_RECTANGLE_X 645
#define LAST_RECTANGLE_Y 460

enum { VK_W = 0, VK_S, VK_A, VK_D };
enum { eR = 0, eG, eB };

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
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	static int nPenWidth = PEN_WIDTH;
	static int nRFX{}, nRFY{}; // Rectangle's first point
	static int nEFX{}, nEFY{}; // Ellipse's first point
	static int nRX{ FIRST_RECTANGLE_X }, nRY{ FIRST_RECTANGLE_Y }; // Rectangle's point
	static int nEX{ FIRST_RECTANGLE_X }, nEY{ FIRST_RECTANGLE_Y }; // Ellipse's point
	static bool bIsFirst = true;
	static bool bDrawRRed = false; // Draw rectangle in red
	static bool bDrawERed = false; // Draw ellipse in red
	static bool bDrawE = false;
	static BYTE bytRGB[3]{};

	switch (iMessage) {
	case WM_CREATE: {
		srand((unsigned)time(NULL));
		nRFX = rand() % MAX_RECTANGLE_X;
		nRFY = rand() % MAX_RECTANGLE_Y;
		nEFX = rand() % MAX_RECTANGLE_X;
		nEFY = rand() % MAX_RECTANGLE_Y;
		break;
	}
	case WM_CHAR: {
		switch (wParam) {
		case 'c': {
			bDrawE = true;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case 'C': {
			bDrawE = true;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case 'r': {
			int nSwapX{ nRX }, nSwapY{ nRY };
			nRX = nEX;
			nRY = nEY;
			nEX = nSwapX;
			nEY = nSwapY;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case 'R': {
			int nSwapX{ nRX }, nSwapY{ nRY };
			nRX = nEX;
			nRY = nEY;
			nEX = nSwapX;
			nEY = nSwapY;

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case 'w': {
			if (bDrawE) {
				if (nEY != FIRST_RECTANGLE_Y) nEY -= (WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y;
				else nEY = LAST_RECTANGLE_Y;
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case 's': {
			if (bDrawE) {
				if (nEY != LAST_RECTANGLE_Y) nEY += (WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y;
				else nEY = FIRST_RECTANGLE_Y;
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case 'a': {
			if (bDrawE) {
				if (nEX != FIRST_RECTANGLE_X) nEX -= (WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X;
				else nEX = LAST_RECTANGLE_X;
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case 'd': {
			if (bDrawE) {
				if (nEX != LAST_RECTANGLE_X) nEX += (WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X;
				else nEX = FIRST_RECTANGLE_X;
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		}
	}
	case WM_KEYDOWN: { // Move Rectangle
		switch (wParam) {
		case VK_NUMPAD8: {
			if (bDrawE) {
				if (nEY != FIRST_RECTANGLE_Y) nEY -= (WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y;
				else {
					nEY = LAST_RECTANGLE_Y;
					bytRGB[eR] = rand() % 255;
					bytRGB[eG] = rand() % 255;
					bytRGB[eB] = rand() % 255;
				}
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_NUMPAD5: {
			if (bDrawE) {
				if (nEY != LAST_RECTANGLE_Y) nEY += (WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y;
				else {
					nEY = FIRST_RECTANGLE_Y;
					bytRGB[eR] = rand() % 255;
					bytRGB[eG] = rand() % 255;
					bytRGB[eB] = rand() % 255;
				}
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_NUMPAD4: {
			if (bDrawE) {
				if (nEX != FIRST_RECTANGLE_X) nEX -= (WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X;
				else {
					nEX = LAST_RECTANGLE_X;
					bytRGB[eR] = rand() % 255;
					bytRGB[eG] = rand() % 255;
					bytRGB[eB] = rand() % 255;
				}
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_NUMPAD6: {
			if (bDrawE) {
				if (nEX != LAST_RECTANGLE_X) nEX += (WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X;
				else {
					nEX = FIRST_RECTANGLE_X;
					bytRGB[eR] = rand() % 255;
					bytRGB[eG] = rand() % 255;
					bytRGB[eB] = rand() % 255;
				}
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_UP: {
			if(nRY != FIRST_RECTANGLE_Y) nRY -= (WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y;
			else {
				nRY = LAST_RECTANGLE_Y;
				bytRGB[eR] = rand() % 255;
				bytRGB[eG] = rand() % 255;
				bytRGB[eB] = rand() % 255;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_DOWN: {
			if(nRY != LAST_RECTANGLE_Y) nRY += (WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y;
			else {
				nRY = FIRST_RECTANGLE_Y;
				bytRGB[eR] = rand() % 255;
				bytRGB[eG] = rand() % 255;
				bytRGB[eB] = rand() % 255;
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_LEFT: {
			if(nRX != FIRST_RECTANGLE_X) nRX -= (WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X;
			else {
				nRX = LAST_RECTANGLE_X;
				bytRGB[eR] = rand() % 255;
				bytRGB[eG] = rand() % 255;
				bytRGB[eB] = rand() % 255;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_RIGHT: {
			if (nRX != LAST_RECTANGLE_X) nRX += (WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X;
			else {
				nRX = FIRST_RECTANGLE_X;
				bytRGB[eR] = rand() % 255;
				bytRGB[eG] = rand() % 255;
				bytRGB[eB] = rand() % 255;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		}

	}
	case WM_KEYUP: {
		switch (wParam) {
		case VK_NUMPAD8: {
			if (bDrawERed) bDrawERed = false;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_NUMPAD5: {
			if (bDrawERed) bDrawERed = false;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_NUMPAD4: {
			if (bDrawERed) bDrawERed = false;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_NUMPAD6: {
			if (bDrawERed) bDrawERed = false;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_UP: {
			if(bDrawRRed) bDrawRRed = false;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_DOWN: {
			if (bDrawRRed) bDrawRRed = false;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_LEFT: {
			if (bDrawRRed) bDrawRRed = false;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_RIGHT: {
			if (bDrawRRed) bDrawRRed = false;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		}
	}
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		hPen = CreatePen(PS_SOLID, nPenWidth, RGB(0,0,0));
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		for (int y = FIRST_RECTANGLE_Y, nYCnt = 0; y < WINDOW_Y; y += (WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y, ++nYCnt ) {
			if (nYCnt == MAX_RECTANGLE_Y) continue;
			for (int x = FIRST_RECTANGLE_X, nXCnt = 0; x < WINDOW_X; x += (WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X, ++nXCnt) {
				if (nXCnt == MAX_RECTANGLE_X) continue;
				Rectangle(hdc, x, y, (x + WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X, (y + WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y);
			}

		}
		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);
		if (GetAsyncKeyState(VK_UP) & 0x8000) if(!bDrawRRed) bDrawRRed = true;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) if (!bDrawRRed) bDrawRRed = true;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) if (!bDrawRRed) bDrawRRed = true;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) if (!bDrawRRed) bDrawRRed = true;

		if (bDrawRRed) hBrush = CreateSolidBrush(RGB(bytRGB[eR], bytRGB[eG], bytRGB[eB]));
		else hBrush = CreateSolidBrush(RGB(255, 255, 255));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		if (bIsFirst) {
			for (int nXcnt = 0; nXcnt < nRFX; ++nXcnt) nRX += (WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X;
			for (int nYcnt = 0; nYcnt < nRFY; ++nYcnt) nRY += (WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y;

			for (int nXcnt = 0; nXcnt < nRFX; ++nXcnt) nEX += (WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X;
			for (int nYcnt = 0; nYcnt < nRFY; ++nYcnt) nEY += (WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y;

			bIsFirst = false;
		}

		Rectangle(hdc, nRX, nRY, (nRX + WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X, (nRY + WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y);

		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);

		// Draw Ellipse
		if (bDrawE) {

			if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000) if (!bDrawERed) bDrawERed = true;
			if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000) if (!bDrawERed) bDrawERed = true;
			if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000) if (!bDrawERed) bDrawERed = true;
			if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000) if (!bDrawERed) bDrawERed = true;

			if (bDrawERed) hBrush = CreateSolidBrush(RGB(bytRGB[eR], bytRGB[eG], bytRGB[eB]));
			else hBrush = CreateSolidBrush(RGB(255, 255, 255));
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Ellipse(hdc, nEX, nEY, (nEX + WINDOW_X / MAX_RECTANGLE_X) - FIRST_RECTANGLE_X, (nEY + WINDOW_Y / MAX_RECTANGLE_Y) - FIRST_RECTANGLE_Y);

			SelectObject(hdc, hOldBrush);
			DeleteObject(hBrush);
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