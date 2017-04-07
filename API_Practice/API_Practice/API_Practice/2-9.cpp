#include <windows.h>
#include <stdio.h>
#include <time.h>

 // #pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOW_X 800
#define WINDOW_Y 600
#define MAX_STRING 30
#define NUM_OF_SHAPE 4

enum ESHAPE{ eNOTHING = 0, eLINE, eEllipse, eRECT, eFILL_RECT };
enum { eLEFT = 1, eTOP, eRIGHT, eBOTTOM };
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

struct STString
{
	char m_szStr[MAX_STRING];
	BYTE m_bytCnt{};
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	static STString stStr;
	static BYTE bytCXpos{5}; // Caret's x pos
	static SIZE siSize{};
	static USHORT wLeft{}, wTop{}, wRight{}, wBottom{};
	static ESHAPE eShape{ eNOTHING };
	static BYTE bytRGB[3]{};
	static BYTE bytPenWidth{0};

	switch (iMessage) {
	case WM_CREATE: {
		srand((unsigned)time(NULL));
		CreateCaret(hWnd, NULL, 5, 20);
		ShowCaret(hWnd);
		break;
	}
	case WM_CHAR: {
		switch (wParam) {
		case VK_RETURN: {

			if ((eShape == eNOTHING && (stStr.m_szStr[0] == '+' || stStr.m_szStr[0] == '-')) || eShape == eNOTHING && (stStr.m_szStr[0] != '[' || stStr.m_szStr[stStr.m_bytCnt - 1] != ']')) {
				MessageBox(hWnd, "At least draw figure what u want first \n Ex) [1 2 3 4 5] 1:Line 2: LEFT 3:TOP 4:RIGHT 5: BOTTOM \n [2 3 4 5 6] 2:Ellipsed \n [3 4 5 6 7] 3: Rect \n [4 5 6 7 8] 4: FillRect", "Error!", MB_OK | MB_ICONEXCLAMATION);
				break;
			}

			if (stStr.m_szStr[0] == '+') {
				if (eShape == eLINE) {
					if (bytPenWidth != 255) bytPenWidth++;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				}
				if (wRight < WINDOW_X) {
					wRight += 1;
					wBottom += 1;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			}

			else if (stStr.m_szStr[0] == '-') {
				if (eShape == eLINE) {
					if (bytPenWidth != 0) bytPenWidth--;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				}
				if (wRight > 0) {
					wRight -= 1;
					wBottom -= 1;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			}

			bytRGB[eR] = rand() % 255;
			bytRGB[eG] = rand() % 255;
			bytRGB[eB] = rand() % 255;

			int i{ 3 }, j{};
			BYTE bytCnt{};
			char temp[3];

			switch (atoi(&stStr.m_szStr[1])) {
			case eLINE:	eShape = eLINE; break;
			case eEllipse:	eShape = eEllipse; break;
			case eRECT:	eShape = eRECT; break;
			case eFILL_RECT:	eShape = eFILL_RECT; break;
			}

			while (i < stStr.m_bytCnt) {
				while (stStr.m_szStr[i] != VK_SPACE && stStr.m_szStr[i] != ']') {
					temp[j++] = stStr.m_szStr[i++];
				}
				bytCnt++;
				switch (bytCnt) {
				case eLEFT: wLeft = atoi(temp); break;
				case eTOP: wTop = atoi(temp); break;
				case eRIGHT: wRight = atoi(temp); break;
				case eBOTTOM: wBottom = atoi(temp); break;
				}

				i = i + j;
				if (j == 3) i -= 2;
				if (j == 2) i -= 1;
				j = 0;
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_BACK: {
			if (stStr.m_bytCnt != 0) {
				stStr.m_bytCnt--;
				stStr.m_szStr[stStr.m_bytCnt] = '\0';
				hdc = BeginPaint(hWnd, &ps);
				GetTextExtentPoint(hdc, stStr.m_szStr, stStr.m_bytCnt, &siSize);
				bytCXpos = siSize.cx;
				EndPaint(hWnd, &ps);
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		default: {
			if (stStr.m_bytCnt != MAX_STRING) {
				stStr.m_szStr[stStr.m_bytCnt] = wParam;
				stStr.m_bytCnt++;
				hdc = BeginPaint(hWnd, &ps);
				GetTextExtentPoint(hdc, stStr.m_szStr, stStr.m_bytCnt, &siSize);
				bytCXpos = siSize.cx;
				EndPaint(hWnd, &ps);
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		}
	}
	case WM_PAINT: {

		hdc = BeginPaint(hWnd, &ps);

		Rectangle(hdc, 0, WINDOW_Y - 60, WINDOW_X / 2, WINDOW_Y - 40);
		TextOut(hdc, 5, WINDOW_Y - 58, (LPCSTR)&stStr, stStr.m_bytCnt);
		SetCaretPos(bytCXpos, WINDOW_Y - 60);

		if (eShape == eLINE) {
			hPen = CreatePen(PS_SOLID, bytPenWidth, RGB(0, 0, 0));
			hOldPen = (HPEN)SelectObject(hdc, hPen);
		}

		hBrush = CreateSolidBrush(RGB(bytRGB[eR], bytRGB[eG], bytRGB[eB]));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		switch (eShape) {
		case eLINE: {
			MoveToEx(hdc, wLeft, wTop, NULL);
			LineTo(hdc, wRight, wBottom);
			break;
		}
		case eEllipse: {
			Ellipse(hdc, wLeft, wTop, wRight, wBottom);
			break;
		}
		case eRECT: {
			Rectangle(hdc, wLeft, wTop, wRight, wBottom);
			break;
		}
		case eFILL_RECT: {
			const RECT rect{ wLeft,wTop,wRight,wBottom };
			FillRect(hdc, &rect, RGB(0, 0, 0));
			break;
		}
		
		}

		if (eShape == eLINE) {
			SelectObject(hdc, hOldPen);
			DeleteObject(hPen);
		}
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam); // 위의 세 메시지 외의 나머지 메시지는 OS로

}