/*
Home: ������ġ�� ����ڰ� �Է��ϴ� ���ڿ� ��� ����
Ctrl: �빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� ���
F1: F1Ű�� ���� �� ���ʹ� ���ڿ��� *�� �ٲ㼭 ��� �ٽ� F1�� ������ ���� ���
F2: ���ڸ� ��� 9�� �ٲ۴�.
F3: ������ e/E�� &�� �ٲ۴�
backspace: ���ڿ��� ���� ���ڸ� �Ѱ��� ����, ���� ���ڿ��� ������ �̵��Ͽ� ���
pagedown: ��µ� ���ڿ����� �� �ٿ� 10���ھ� ���, �� �̻� �Ǵ� ���ڿ����� ������������ �̵��Ͽ� ���
pageup: 10���ھ� ������ ���ڿ��� ������� ���
*/

#include <windows.h>
#include <stdio.h>
#include <time.h>
//#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOW_X 800
#define WINDOW_Y 600
#define MAX_LINE 10
#define SPACE 32
#define NUM_OF_SPACE 4
#define CHAR_DIFFER 32
#define ALPHABET_MIN 65
#define ALPHABET_MAX 90
#define NUM_OF_START 48
#define NUM_OF_END 57
#define NUM_OF_NINE 57
//#define NUM_OF_E 69
#define NUM_OF_REFERENCE 38
HINSTANCE g_hInst;
LPCTSTR lpszClass = "Windows";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	// ������ Ŭ���� ����ü �� ����
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
	// ������ Ŭ���� ���
	RegisterClassEx(&WndClass);
	// ������ ����
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, WINDOW_X, WINDOW_Y, NULL, (HMENU)NULL, hInstance, NULL);
	// ������ ���
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// �̺�Ʈ ���� ó��
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}


struct stStr
{
	char m_szStr[900]{};
	unsigned short m_usCount{};
	unsigned short m_usXpos{};
	unsigned short m_usYpos{};
	bool m_bEncryption = false;
	unsigned short m_usEnd{};
	unsigned short m_usLeft{};
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
	static bool bEncryption = false;
	static bool bNext = false;
	switch (iMessage) {
	case WM_CREATE: {
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		srand((unsigned)time(NULL));
		return 0;
	}
	case WM_CHAR: {
		switch (wParam) {
		case VK_BACK: {
			if (pstStr[usIndex].m_usCount != 0) {
				for (int i = 0; i < pstStr[usIndex].m_usCount; ++i) {
					pstStr[usIndex].m_szStr[i] = pstStr[usIndex].m_szStr[i + 1];
				}
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
			for (int i = 0; i <= usIndex; ++i) ZeroMemory(&pstStr[i], sizeof(stStr));
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
					usXpos = (unsigned short)size.cx + pstStr[usIndex].m_usXpos;
					usYpos = pstStr[usIndex].m_usYpos;
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
			usXpos = rand() % WINDOW_X + 1;
			usYpos = rand() % WINDOW_Y + 1;
			pstStr[usIndex].m_usXpos = usXpos;
			pstStr[usIndex].m_usYpos = usYpos;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_CONTROL: {
			for (int i = 0; i <= usIndex; ++i) {
				for (int j = 0; j <= pstStr[i].m_usCount; ++j) {
					if (pstStr[i].m_szStr[j] >= ALPHABET_MIN && pstStr[i].m_szStr[j] <= ALPHABET_MAX) {
						pstStr[i].m_szStr[j] = pstStr[i].m_szStr[j] + CHAR_DIFFER;
					}
					else if (pstStr[i].m_szStr[j] >= ALPHABET_MIN - CHAR_DIFFER && pstStr[i].m_szStr[j] <= ALPHABET_MAX + CHAR_DIFFER) {
						pstStr[i].m_szStr[j] = pstStr[i].m_szStr[j] - CHAR_DIFFER;
					}
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_F1:{
			if (!bEncryption) {
				bEncryption = true;
				pstStr[usIndex].m_usEnd = pstStr[usIndex].m_usCount;
			}
			else bEncryption = false;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_F2: {
			for (int i = 0; i <= usIndex; ++i) {
				for (int j = 0; j < pstStr[i].m_usCount; ++j) {
					if (pstStr[i].m_szStr[j] >= NUM_OF_START && pstStr[i].m_szStr[j] <= NUM_OF_END) {
						pstStr[i].m_szStr[j] = NUM_OF_NINE;
					}
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_F3:{
			for (int i = 0; i < usIndex; ++i) {
				for (int j = 0; j < pstStr[i].m_usCount; ++j) {
					if (pstStr[i].m_szStr[j] == 69 || pstStr[i].m_szStr[j] == 69 + CHAR_DIFFER) {
						pstStr[i].m_szStr[j] = NUM_OF_REFERENCE;
					}
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break; 
		}
		case VK_NEXT:{
			bNext = true;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_PRIOR: {
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

		if (bEncryption) pstStr[usIndex].m_bEncryption = true;
		else pstStr[usIndex].m_bEncryption = false;

		if (!bNext) {
			for (int i = 0; i <= usIndex; ++i) {
				if (pstStr[i].m_bEncryption) {
					for (int j = pstStr[usIndex].m_usEnd; j < pstStr[i].m_usCount; ++j) {
						pstStr[i].m_szStr[j] = '*';
					}
				}
				TextOut(hdc, pstStr[i].m_usXpos, pstStr[i].m_usYpos, pstStr[i].m_szStr, strlen(pstStr[i].m_szStr));
				SetCaretPos(usXpos, usYpos);
			}
		}
		if (bNext) {
			static char temp[MAX_LINE +1];
			static char temp2[MAX_LINE];
			int nCharCount{};
			int j{};
			int k{};
			int tempYpos{};
			unsigned short nLeft{};
			unsigned short nBeforeLeft{};
			unsigned short usCount{};
			static bool bOneLine = true;
			for (int i = 0; i <= usIndex; ++i) {
				nLeft = pstStr[i].m_usCount;
				ZeroMemory(temp, sizeof(temp));
				while (nLeft != 0) {
					for (j = 0; j <= pstStr[i].m_usCount; ++j, ++k) {
						if (pstStr[i].m_szStr[j] == '\0') {
							nLeft = 0;
							break;
						}
						if (i != 0 && pstStr[i - 1].m_usLeft != 0) {
							bOneLine = false;
							for (int j = 0; j < pstStr[i - 1].m_usLeft; ++j) {
								temp[j] = temp2[j];
								nCharCount++;
								
							}
							//k--;
							pstStr[i - 1].m_usLeft = 0;
						}
							temp[k] = pstStr[i].m_szStr[j];
							nCharCount++;
							nLeft--;
						
						if (nCharCount == MAX_LINE) {
							temp[MAX_LINE] = '\0';
							tempYpos += 20;
							if (usIndex != 0) {
								if (tempYpos == 20) tempYpos += 20 * usIndex;
							}

							TextOut(hdc, 0, tempYpos, temp, strlen(temp));
							SetCaretPos(usXpos, usYpos);
							nCharCount = 0;
							usCount++;
							k = -1;
						}
					}
				}
					pstStr[i].m_usLeft = nCharCount;
					for (int i = 0; i < nCharCount; ++i) {
						temp2[i] = temp[i];
					}
					//if (!bOneLine) {
						temp[nCharCount] = '\0';
						nCharCount = 0;
					//}
				
			}
			tempYpos += 20;
			//if(bOneLine) temp[nCharCount] = '\0';
			TextOut(hdc, 0, tempYpos, temp, strlen(temp));
			SetCaretPos(usXpos, usYpos);
			bNext = false;
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
	return DefWindowProc(hWnd, iMessage, wParam, lParam); // ���� �� �޽��� ���� ������ �޽����� OS��

}