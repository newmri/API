/*
키보드 명령에 따라 그림 그리기
40*40 보드를 그리고 브드의 칸에 맞게 도형을 그림
명령어: E/e: 원을 임의의 위치에 그린다
T/t: 삼각형을 임의의 위치에 그린다
도형의 색은 랜덤
숫자: 그려진 순서대로 도형이 선택, 1번이면 첫번째 그려진 거 선택된 도형은 둘레에표시된다, del 선택된 도형 삭제
화살표: 선택된 도형이 상하좌우 이동
+/- 2배씩 증가, 축소, 도형이 원래 크기보다 작아지면 도형 삭제, 다른 모양의 도형이 나타남
최대 5개 까지 도형이 그려짐
6번째 도형을 그리려고 하면 첫번째 도형이 대체됨
*/

#include <windows.h>
#include <stdio.h>
#include <time.h>

 #pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOW_X 1280
#define WINDOW_Y 800
#define MAX_STRING 30
#define MAX_FIGURE 5
#define MAX_MAP_X 40
#define MAX_MAP_Y 40
#define MAX_NUM_OF_POINT 3
enum ESHAPE { eNOTHING = 0, eEllipse, eTriangle, eDeleted };
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

struct STShape
{
	BYTE m_bytId{};
	ESHAPE m_eShape = eNOTHING;
	USHORT m_wX{}, m_wY{};
	USHORT m_wLeft{}, m_wTop{}, m_wRight{}, m_wBottom{};
	POINT m_ptPoints[MAX_NUM_OF_POINT]{};
	BYTE m_bytRGB[3]{};
	bool m_IsSelected = false;
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	USHORT wLeft{}, wTop{}, wRight{}, wBottom{};
	static STShape stShape[MAX_FIGURE]{};
	static BYTE bytIndex{};
	static BYTE bytId{1};
	switch (iMessage) {
	case WM_CREATE: {
		srand((unsigned)time(NULL));

		break;
	}
	case WM_CHAR: {
		switch (wParam) {
		case 'e':
		case 'E':{
			bool IsOver = false;
			BYTE bytTempIndex{};

			if (bytIndex == MAX_FIGURE) {
				bytTempIndex = bytIndex;
				bytIndex = 0;
				ZeroMemory(&stShape[bytIndex], sizeof(STShape));
				IsOver = true;
			}

				stShape[bytIndex].m_bytId = bytId;
				stShape[bytIndex].m_eShape = eEllipse;
				stShape[bytIndex].m_wX = rand() % MAX_MAP_X;
				stShape[bytIndex].m_wY = rand() % MAX_MAP_Y;

				for (int x = 0; x < stShape[bytIndex].m_wX; ++x, stShape[bytIndex].m_wLeft += (WINDOW_X / MAX_MAP_X) - 1);
				for (int y = 0; y < stShape[bytIndex].m_wY; ++y, stShape[bytIndex].m_wTop += (WINDOW_Y / MAX_MAP_Y) - 1);

				stShape[bytIndex].m_wRight = stShape[bytIndex].m_wLeft + (WINDOW_X / MAX_MAP_X) - 1;
				stShape[bytIndex].m_wBottom = stShape[bytIndex].m_wTop + (WINDOW_Y / MAX_MAP_Y) - 1;

				// Set RGB
				stShape[bytIndex].m_bytRGB[eR] = rand() % 255;
				stShape[bytIndex].m_bytRGB[eG] = rand() % 255;
				stShape[bytIndex].m_bytRGB[eB] = rand() % 255;

				if (IsOver) {
					bytIndex = bytTempIndex;
					stShape[0].m_bytId = 5;
					for (int i = 1; i < bytIndex; ++i) {
						stShape[i].m_bytId--;
					}
				}
				else {
					++bytIndex;
					++bytId;
				}

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case 't':
		case 'T': {
			bool IsOver = false;
			BYTE bytTempIndex{};

			if (bytIndex == MAX_FIGURE) {
				bytTempIndex = bytIndex;
				bytIndex = 0;
				ZeroMemory(&stShape[bytIndex], sizeof(STShape));
				IsOver = true;
			}
				stShape[bytIndex].m_bytId = bytId;
				stShape[bytIndex].m_eShape = eTriangle;
				stShape[bytIndex].m_wX = rand() % MAX_MAP_X;
				stShape[bytIndex].m_wY = rand() % MAX_MAP_Y;

				for (int x = 0; x < stShape[bytIndex].m_wX; ++x, stShape[bytIndex].m_ptPoints[0].x += (WINDOW_X / MAX_MAP_X) - 1);
				for (int y = 0; y < stShape[bytIndex].m_wY - 1; ++y, stShape[bytIndex].m_ptPoints[0].y += (WINDOW_Y / MAX_MAP_Y) - 1);

				// Test: Left -> Right -> Top
				stShape[bytIndex].m_ptPoints[1].x = stShape[bytIndex].m_ptPoints[0].x + (WINDOW_X / MAX_MAP_X) - 1;
				stShape[bytIndex].m_ptPoints[1].y = stShape[bytIndex].m_ptPoints[0].y;
				stShape[bytIndex].m_ptPoints[2].x = stShape[bytIndex].m_ptPoints[0].x + ((WINDOW_X / MAX_MAP_X) - 1) / 2;
				stShape[bytIndex].m_ptPoints[2].y = stShape[bytIndex].m_ptPoints[0].y - (WINDOW_Y / MAX_MAP_Y) - 1;

				// Set RGB
				stShape[bytIndex].m_bytRGB[eR] = rand() % 255;
				stShape[bytIndex].m_bytRGB[eG] = rand() % 255;
				stShape[bytIndex].m_bytRGB[eB] = rand() % 255;

				if (IsOver) {
					bytIndex = bytTempIndex;
					stShape[0].m_bytId = 5;
					for (int i = 1; i < bytIndex; ++i) {
						stShape[i].m_bytId--;
					}
				}
				else {
					++bytIndex;
					++bytId;
				}
	
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':{

			for (int i = 0; i < MAX_FIGURE; ++i) {
				if (stShape[i].m_IsSelected) stShape[i].m_IsSelected = false;	
			}

			for (int i = 0; i < MAX_FIGURE; ++i) {
				if (stShape[i].m_bytId == atoi(reinterpret_cast<const char*>(&wParam))) {
					stShape[i].m_IsSelected = true;
					break;
				}
			}	
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case '+': {
			for (int i = 0; i < MAX_FIGURE; ++i) {
				if (stShape[i].m_IsSelected) {
					if (stShape[i].m_eShape == eEllipse) {
						stShape[i].m_wRight += (WINDOW_X / MAX_MAP_X) - 1;
						stShape[i].m_wBottom += (WINDOW_Y / MAX_MAP_Y) - 1;

					}
					else {
						stShape[i].m_ptPoints[2].x += ((WINDOW_X / MAX_MAP_X) - 1) / 2;
						stShape[i].m_ptPoints[1].x += (WINDOW_X / MAX_MAP_X) - 1;
						stShape[i].m_ptPoints[2].y -= (WINDOW_Y / MAX_MAP_Y) - 1;
					}
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case '-': {
			for (int i = 0; i < MAX_FIGURE; ++i) {
				if (stShape[i].m_IsSelected) {
					if (stShape[i].m_eShape == eEllipse) {
						if (stShape[i].m_wBottom - stShape[i].m_wTop == 19) {
							// This is for transform to another figure
							stShape[i].m_eShape = eTriangle;
							stShape[i].m_ptPoints[0].x = stShape[i].m_wLeft;
							stShape[i].m_ptPoints[0].y = stShape[i].m_wBottom;
							stShape[i].m_ptPoints[1].x = stShape[i].m_ptPoints[0].x + (WINDOW_X / MAX_MAP_X) - 1;
							stShape[i].m_ptPoints[1].y = stShape[i].m_ptPoints[0].y;
							stShape[i].m_ptPoints[2].x = stShape[i].m_ptPoints[0].x + ((WINDOW_X / MAX_MAP_X) - 1) / 2;
							stShape[i].m_ptPoints[2].y = stShape[i].m_ptPoints[0].y - (WINDOW_Y / MAX_MAP_Y) - 1;
							break;
						}
						else {
							stShape[i].m_wRight -= (WINDOW_X / MAX_MAP_X) - 1;
							stShape[i].m_wBottom -= (WINDOW_Y / MAX_MAP_Y) - 1;
						}
			
					}
					else {
						if ((stShape[i].m_ptPoints[1].x - stShape[i].m_ptPoints[2].x) == 16) {
							stShape[i].m_eShape = eEllipse;
							stShape[i].m_wLeft = stShape[i].m_ptPoints[0].x;
							stShape[i].m_wRight = stShape[i].m_wLeft + (WINDOW_X / MAX_MAP_X) - 1;
							stShape[i].m_wTop = stShape[i].m_ptPoints[1].y - ((WINDOW_Y / MAX_MAP_Y) - 1);
							stShape[i].m_wBottom = stShape[i].m_wTop + ((WINDOW_Y / MAX_MAP_Y) - 1);
							break;
						}
						stShape[i].m_ptPoints[2].x -= ((WINDOW_X / MAX_MAP_X) - 1) / 2;
						stShape[i].m_ptPoints[1].x -= (WINDOW_X / MAX_MAP_X) - 1;
						stShape[i].m_ptPoints[2].y += (WINDOW_Y / MAX_MAP_Y) - 1;
					}
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		}
	}
	case WM_KEYDOWN: {
		switch (wParam){
		case VK_DELETE: {
			for (int i = 0; i < bytIndex; ++i) {
				if (stShape[i].m_IsSelected) {
					ZeroMemory(&stShape[i], sizeof(STShape));
					stShape[i].m_eShape = eDeleted;
					if (i == MAX_FIGURE - 1) {
						bytId--;
						bytIndex--;
						break;
					}

					for (int j = i+1; j < bytIndex; ++j) {
						stShape[j].m_bytId--;
						memcpy(&stShape[j - 1], &stShape[j], sizeof(STShape));
					}

					ZeroMemory(&stShape[bytIndex - 1], sizeof(STShape));
					bytId--;
					bytIndex--;

					break;
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case VK_UP: {
			for (int i = 0; i < bytIndex; ++i) {
				if (stShape[i].m_IsSelected) {
					if (stShape[i].m_eShape == eEllipse) {
						stShape[i].m_wTop -= (WINDOW_Y / MAX_MAP_Y) - 1;
						stShape[i].m_wBottom -= (WINDOW_Y / MAX_MAP_Y) - 1;
					}
					else {
						stShape[i].m_ptPoints[2].y -= (WINDOW_Y / MAX_MAP_Y) - 1;
						stShape[i].m_ptPoints[1].y -= (WINDOW_Y / MAX_MAP_Y) - 1;
						stShape[i].m_ptPoints[0].y -= (WINDOW_Y / MAX_MAP_Y) - 1;
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_DOWN: {
			for (int i = 0; i < bytIndex; ++i) {
				if (stShape[i].m_IsSelected) {
					if (stShape[i].m_eShape == eEllipse) {
						stShape[i].m_wTop += (WINDOW_Y / MAX_MAP_Y) - 1;
						stShape[i].m_wBottom += (WINDOW_Y / MAX_MAP_Y) - 1;
					}
					else {
						stShape[i].m_ptPoints[2].y += (WINDOW_Y / MAX_MAP_Y) - 1;
						stShape[i].m_ptPoints[1].y += (WINDOW_Y / MAX_MAP_Y) - 1;
						stShape[i].m_ptPoints[0].y += (WINDOW_Y / MAX_MAP_Y) - 1;
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_LEFT: {
			for (int i = 0; i < bytIndex; ++i) {
				if (stShape[i].m_IsSelected) {
					if (stShape[i].m_eShape == eEllipse) {
						stShape[i].m_wLeft -= (WINDOW_X / MAX_MAP_X) - 1;
						stShape[i].m_wRight -= (WINDOW_X / MAX_MAP_X) - 1;
					}
					else {
						stShape[i].m_ptPoints[2].x -= (WINDOW_X / MAX_MAP_X) - 1;
						stShape[i].m_ptPoints[1].x -= (WINDOW_X / MAX_MAP_X) - 1;
						stShape[i].m_ptPoints[0].x -= (WINDOW_X / MAX_MAP_X) - 1;
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		case VK_RIGHT: {
			for (int i = 0; i < bytIndex; ++i) {
				if (stShape[i].m_IsSelected) {
					if (stShape[i].m_eShape == eEllipse) {
						stShape[i].m_wLeft += (WINDOW_X / MAX_MAP_X) - 1;
						stShape[i].m_wRight += (WINDOW_X / MAX_MAP_X) - 1;
					}
					else {
						stShape[i].m_ptPoints[2].x += (WINDOW_X / MAX_MAP_X) - 1;
						stShape[i].m_ptPoints[1].x += (WINDOW_X / MAX_MAP_X) - 1;
						stShape[i].m_ptPoints[0].x += (WINDOW_X / MAX_MAP_X) - 1;
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		}
	}
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		for (int y = 0; y < MAX_MAP_X; ++y, wTop += (WINDOW_Y / MAX_MAP_Y) -1) {
			for (int x = 0; x < MAX_MAP_X; ++x, wLeft += (WINDOW_X / MAX_MAP_X) -1) {
				wRight = wLeft + (WINDOW_X / MAX_MAP_X) - 1;
				wBottom = wTop + (WINDOW_Y / MAX_MAP_Y) - 1;
				Rectangle(hdc, wLeft, wTop, wRight, wBottom);
			}
			wLeft = 0;
		}
	
	
		for (int nIndex = 0; nIndex < bytIndex; ++nIndex) {
			switch (stShape[nIndex].m_eShape) {
			case eEllipse: {
				if (stShape[nIndex].m_IsSelected) {
					hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
					hOldPen = (HPEN)SelectObject(hdc, hPen);
				}
				hBrush = CreateSolidBrush(RGB(stShape[nIndex].m_bytRGB[eR], stShape[nIndex].m_bytRGB[eG], stShape[nIndex].m_bytRGB[eB]));
				hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

				Ellipse(hdc, stShape[nIndex].m_wLeft, stShape[nIndex].m_wTop, stShape[nIndex].m_wRight, stShape[nIndex].m_wBottom);
				
				if (stShape[nIndex].m_IsSelected) {
					SelectObject(hdc, hOldPen);
					DeleteObject(hPen);
					
				}

				SelectObject(hdc, hOldBrush);
				DeleteObject(hBrush);
				break;
			}
			case eTriangle: {
				POINT vertices[] = { { stShape[nIndex].m_ptPoints[2].x, stShape[nIndex].m_ptPoints[2].y },
				{ stShape[nIndex].m_ptPoints[1].x, stShape[nIndex].m_ptPoints[1].y },
				{ stShape[nIndex].m_ptPoints[0].x, stShape[nIndex].m_ptPoints[0].y } };

				if (stShape[nIndex].m_IsSelected) {
					hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
					hOldPen = (HPEN)SelectObject(hdc, hPen);
				}

				hBrush = CreateSolidBrush(RGB(stShape[nIndex].m_bytRGB[eR], stShape[nIndex].m_bytRGB[eG], stShape[nIndex].m_bytRGB[eB]));
				hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

				Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

				if (stShape[nIndex].m_IsSelected) {
					SelectObject(hdc, hOldPen);
					DeleteObject(hPen);
					
				}

				SelectObject(hdc, hOldBrush);
				DeleteObject(hBrush);
				break;
			}
			default:
				break;

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