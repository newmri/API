#include <windows.h>
#include <stdio.h>

// #pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOW_X 800
#define WINDOW_Y 600
#define MAX_LINE 10
#define SPACE 32
#define NUM_OF_SPACE 4
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


struct stStr
{
	char m_szStr[100]{};
	unsigned short m_usCount{};
	unsigned short m_usXpos{};
	unsigned short m_usYpos{};
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static stStr* pstStr = new stStr[MAX_LINE];
	static unsigned short usIndex{};
	static SIZE size;
	static unsigned short usXpos{ 0 }, usYpos{};
	static unsigned short usLeft{};
	switch (iMessage) {
	case WM_CREATE: {
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		return 0;
	}
	case WM_CHAR: {
		switch (wParam) {
		case VK_BACK: {
			if (pstStr[usIndex].m_usCount != 0) {
				pstStr[usIndex].m_usCount--;
				pstStr[usIndex].m_szStr[pstStr[usIndex].m_usCount] = '\0';
				hdc = BeginPaint(hWnd, &ps);
				GetTextExtentPoint(hdc, pstStr[usIndex].m_szStr, strlen(pstStr[usIndex].m_szStr), &size);
				usXpos = (unsigned short)size.cx;
				EndPaint(hWnd, &ps);
			}
			else {
				if (usIndex != 0) {
					usIndex--;
					usYpos -= 20;
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_RETURN: {
			pstStr[usIndex].m_szStr[pstStr[usIndex].m_usCount] = '\0';
			pstStr[usIndex + 1].m_usYpos = pstStr[usIndex].m_usYpos + 20;
			if (usIndex != MAX_LINE - 1) {
				usIndex++;
				usYpos += 20;
				usXpos = 0;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

		case VK_ESCAPE: {
			for(int i=0; i <= usIndex; ++i) ZeroMemory(&pstStr[i], sizeof(stStr));
			usIndex = 0;
			usXpos = 0;
			usYpos = 0;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_TAB: {
			for (int i = 0; i < NUM_OF_SPACE; ++i) {
				pstStr[usIndex].m_szStr[pstStr[usIndex].m_usCount++] = SPACE;
			}
			pstStr[usIndex].m_szStr[pstStr[usIndex].m_usCount] = '\0';
			hdc = BeginPaint(hWnd, &ps);
			GetTextExtentPoint(hdc, pstStr[usIndex].m_szStr, strlen(pstStr[usIndex].m_szStr), &size);
			usXpos = (unsigned short)size.cx;
			EndPaint(hWnd, &ps);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

		default:
			if (pstStr[usIndex].m_usCount != 99) {
				if (usLeft == 0) {
					pstStr[usIndex].m_szStr[pstStr[usIndex].m_usCount++] = wParam;
					hdc = BeginPaint(hWnd, &ps);
					GetTextExtentPoint(hdc, pstStr[usIndex].m_szStr, strlen(pstStr[usIndex].m_szStr), &size);
					usXpos = (unsigned short)size.cx;
					EndPaint(hWnd, &ps);
				}
				else {
					pstStr[usIndex].m_szStr[pstStr[usIndex].m_usCount - usLeft] = wParam;
					hdc = BeginPaint(hWnd, &ps);
					GetTextExtentPoint(hdc, pstStr[usIndex].m_szStr, strlen(pstStr[usIndex].m_szStr), &size);
					usXpos = (unsigned short)size.cx;
					EndPaint(hWnd, &ps);
					usLeft = 0;
				}
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
	}
	case WM_KEYDOWN: {
		switch (wParam) {
		case VK_HOME: {
			usXpos = 0;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_DELETE: {
			ZeroMemory(&pstStr[usIndex], sizeof(stStr));

			if (usIndex != 0) {
				hdc = BeginPaint(hWnd, &ps);
				GetTextExtentPoint(hdc, pstStr[usIndex - 1].m_szStr, strlen(pstStr[usIndex - 1].m_szStr), &size);
				usXpos = (unsigned short)size.cx;
				EndPaint(hWnd, &ps);
				usYpos = pstStr[usIndex - 1].m_usYpos;
				usIndex--;
			}
			else  usXpos = 0;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		}
		case VK_UP: {
			if (usIndex != 0) {
				usYpos -= 20;
				pstStr[usIndex].m_usYpos -= 20;
				usIndex--;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		case VK_DOWN: {
			pstStr[usIndex].m_szStr[pstStr[usIndex].m_usCount] = '\0';
			pstStr[usIndex + 1].m_usYpos = pstStr[usIndex].m_usYpos + 20;
			usYpos += 20;
			usIndex++;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_LEFT: {
			TEXTMETRIC tm;
			hdc = BeginPaint(hWnd, &ps);
			GetTextMetrics(hdc, &tm);
			EndPaint(hWnd, &ps);
			usXpos -= tm.tmAveCharWidth;
			usLeft++;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_RIGHT: {
			TEXTMETRIC tm;
			hdc = BeginPaint(hWnd, &ps);
			GetTextMetrics(hdc, &tm);
			EndPaint(hWnd, &ps);
			usXpos += tm.tmAveCharWidth;
			pstStr[usIndex].m_szStr[pstStr[usIndex].m_usCount++] = SPACE;
			pstStr[usIndex].m_szStr[pstStr[usIndex].m_usCount] = '\0';
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		}
	}
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i <= usIndex; ++i) {
			TextOut(hdc, pstStr[i].m_usXpos, pstStr[i].m_usYpos, pstStr[i].m_szStr, strlen(pstStr[i].m_szStr));
			SetCaretPos(usXpos, usYpos);
		}
		
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		delete[] pstStr;
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam); // 위의 세 메시지 외의 나머지 메시지는 OS로
	
}