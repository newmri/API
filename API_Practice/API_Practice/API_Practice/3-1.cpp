#include <windows.h>
#include <stdio.h>
#include <time.h>
#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")
//for(theta =0; theta < 2pi; theta +=0.1)
// x: r * cos seta
// y: r * sin seta
#define WINDOW_X 1280
#define WINDOW_Y 800
#define FIRST_X 40
#define FIRST_Y 40
#define INCREMENT 40
#define MAX_SPEED 0
#define MIN_SPEED 1000
#define MAX_NPC 10
enum { P_TIMER, JUMP_TIMER, NEW_WARM_TIMER, MOVE_NPC_TIMER };
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

struct STWarms
{
	USHORT m_wHeadTopY{ FIRST_Y }, m_wHeadBottomY{ FIRST_Y * 2};
	USHORT m_wHeadLeftX{ FIRST_X }, m_wHeadRightX{ FIRST_X + INCREMENT };

	USHORT m_wBodyTopY{ FIRST_Y }, m_wBodyBottomY{ FIRST_Y * 2 };
	USHORT m_wBodyLeftX{}, m_wBodyRightX{ FIRST_X };

	bool bGoToLeft = false;
	bool bGoToBottom = false;
	bool bHM = true; // Horizontal Migration
	bool bJumpOn = false;
	bool bIsCreated = false;
	bool bHaveBody = false;
	bool bLeftGrowHead = false;
	bool bRightGrowHead = false;
};

struct STWarmsSwap
{
	USHORT m_wTopY{ FIRST_Y }, m_wBottomY{ FIRST_Y * 2 };
	USHORT m_wLeftX{}, m_wRightX{ FIRST_X };
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, hOldPen;

	static RECT rectView;
	static STWarms stWarms;
	static int nSpeed{ 100 };
	static STWarms stNPC[MAX_NPC];
	static BYTE bytCntNPC{};
	switch (iMessage) {
	case WM_CREATE: {
		srand((unsigned)time(NULL));
		GetClientRect(hWnd, &rectView);
		SetTimer(hWnd, P_TIMER, nSpeed, NULL);
		SetTimer(hWnd, NEW_WARM_TIMER, nSpeed * 100, NULL);
		break;
	}

	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		// Draw warms
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		Ellipse(hdc, stWarms.m_wHeadLeftX, stWarms.m_wHeadTopY, stWarms.m_wHeadRightX, stWarms.m_wHeadBottomY);
		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);

		hPen = CreatePen(PS_SOLID, 1, RGB(1, 0, 255));
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		Ellipse(hdc, stWarms.m_wBodyLeftX, stWarms.m_wBodyTopY, stWarms.m_wBodyRightX, stWarms.m_wBodyBottomY);
		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);

		// Draw NPC
		for (int i = 0; i < MAX_NPC; ++i) {
			if (stNPC[i].bIsCreated) {
				hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				hOldPen = (HPEN)SelectObject(hdc, hPen);
				Ellipse(hdc, stNPC[i].m_wHeadLeftX, stNPC[i].m_wHeadTopY, stNPC[i].m_wHeadRightX, stNPC[i].m_wHeadBottomY);
				SelectObject(hdc, hOldPen);
				DeleteObject(hPen);

				if (stNPC[i].bHaveBody) {
					hPen = CreatePen(PS_SOLID, 1, RGB(1, 0, 255));
					hOldPen = (HPEN)SelectObject(hdc, hPen);
					Ellipse(hdc, stNPC[i].m_wBodyLeftX, stNPC[i].m_wBodyTopY, stNPC[i].m_wBodyRightX, stNPC[i].m_wBodyBottomY);
					SelectObject(hdc, hOldPen);
					DeleteObject(hPen);

				}
			}
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT: stWarms.bHM = true; stWarms.bGoToLeft = true; 
			if (stWarms.m_wHeadBottomY - stWarms.m_wHeadTopY != 40) {
				stWarms.m_wHeadBottomY -= 10;
				stWarms.m_wHeadTopY += 10;
				stWarms.m_wHeadLeftX += 20;
			}
			stWarms.m_wBodyLeftX = stWarms.m_wHeadRightX; stWarms.m_wBodyRightX = stWarms.m_wBodyLeftX + INCREMENT; 
			stWarms.m_wBodyTopY = stWarms.m_wHeadTopY; stWarms.m_wBodyBottomY = stWarms.m_wHeadBottomY; 
			InvalidateRect(hWnd, NULL, TRUE); break;
		case VK_RIGHT: stWarms.bHM = true; stWarms.bGoToLeft = false;
			if (stWarms.m_wHeadBottomY - stWarms.m_wHeadTopY != 40) {
				stWarms.m_wHeadBottomY -= 10;
				stWarms.m_wHeadTopY += 10;
				stWarms.m_wHeadRightX -= 20;
			}

			stWarms.m_wBodyLeftX = stWarms.m_wHeadLeftX - INCREMENT; stWarms.m_wBodyRightX = stWarms.m_wHeadLeftX;
			stWarms.m_wBodyTopY = stWarms.m_wHeadTopY; stWarms.m_wBodyBottomY = stWarms.m_wHeadBottomY;
			InvalidateRect(hWnd, NULL, TRUE); break;
		case VK_UP: stWarms.bHM = false; stWarms.bGoToBottom = false;
			if (stWarms.bRightGrowHead) {
				stWarms.m_wHeadBottomY -= 10;
				stWarms.m_wHeadTopY += 10;
				stWarms.m_wHeadLeftX += 20;
				stWarms.bRightGrowHead = false;
			}
			if(stWarms.m_wHeadBottomY - stWarms.m_wHeadTopY != 40){
				stWarms.m_wHeadBottomY -= 10;
				stWarms.m_wHeadTopY += 10;
				stWarms.m_wHeadRightX -= 20;
				stWarms.bLeftGrowHead = false;
			}
			stWarms.m_wBodyTopY = stWarms.m_wHeadBottomY; stWarms.m_wBodyBottomY = stWarms.m_wBodyTopY + INCREMENT;
			stWarms.m_wBodyLeftX = stWarms.m_wHeadLeftX; stWarms.m_wBodyRightX = stWarms.m_wHeadRightX; 
			InvalidateRect(hWnd, NULL, TRUE); break;
		case VK_DOWN: stWarms.bHM = false; stWarms.bGoToBottom = true;
			if (stWarms.bRightGrowHead) {
				stWarms.m_wHeadBottomY -= 10;
				stWarms.m_wHeadTopY += 10;
				stWarms.m_wHeadLeftX += 20;
				stWarms.bRightGrowHead = false;
			}
			if (stWarms.m_wHeadBottomY - stWarms.m_wHeadTopY != 40) {
				stWarms.m_wHeadBottomY -= 10;
				stWarms.m_wHeadTopY += 10;
				stWarms.m_wHeadRightX -= 20;
				stWarms.bLeftGrowHead = false;
			}
			stWarms.m_wBodyBottomY = stWarms.m_wHeadTopY; stWarms.m_wBodyTopY = stWarms.m_wBodyBottomY - INCREMENT;
			stWarms.m_wBodyLeftX = stWarms.m_wHeadLeftX; stWarms.m_wBodyRightX = stWarms.m_wHeadRightX; 
			InvalidateRect(hWnd, NULL, TRUE); break;
		case VK_SPACE:
			if (!stWarms.bJumpOn) {
				if (stWarms.m_wHeadTopY != 0) {
					stWarms.bJumpOn = true;
					stWarms.m_wHeadTopY -= INCREMENT;
					stWarms.m_wHeadBottomY -= INCREMENT;
					stWarms.m_wBodyTopY -= INCREMENT;
					stWarms.m_wBodyBottomY -= INCREMENT;

					for (int i = 0; i < MAX_NPC; ++i) {
						if (stNPC[i].bIsCreated) {
							stNPC[i].m_wHeadTopY -= INCREMENT;
							stNPC[i].m_wHeadBottomY -= INCREMENT;
							stNPC[i].m_wBodyTopY -= INCREMENT;
							stNPC[i].m_wBodyBottomY -= INCREMENT;
						}
					}
					KillTimer(hWnd, P_TIMER);
					KillTimer(hWnd, MOVE_NPC_TIMER);
					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
			break;
		}
	case WM_KEYUP:
		switch (wParam) {
		case VK_SPACE: SetTimer(hWnd, JUMP_TIMER, nSpeed*4, NULL); break;
		}
	case WM_CHAR: {
		switch (wParam) {
		case '+': if(nSpeed > MAX_SPEED) SetTimer(hWnd, P_TIMER, nSpeed-=10, NULL); break;
		case '-': if (nSpeed < MIN_SPEED) SetTimer(hWnd, P_TIMER, nSpeed += 10, NULL); break;
		}
	}

	case WM_TIMER:{
		switch (wParam) {
		case  P_TIMER: {
			if (!stWarms.bJumpOn) {
				// To Right
				if ((!stWarms.bGoToLeft) && stWarms.bHM) {
					if (stWarms.m_wHeadBottomY - stWarms.m_wHeadTopY == 40) {
						stWarms.m_wHeadBottomY += 10;
						stWarms.m_wHeadTopY -= 10;
						stWarms.m_wHeadRightX += 20;
						stWarms.bRightGrowHead = true;
					}
					else {
						stWarms.m_wHeadBottomY -= 10;
						stWarms.m_wHeadTopY += 10;
						stWarms.m_wHeadRightX -= 20;
						stWarms.bRightGrowHead = false;
					}

					stWarms.m_wHeadLeftX += INCREMENT;
					stWarms.m_wHeadRightX += INCREMENT;
					stWarms.m_wBodyLeftX += INCREMENT;
					stWarms.m_wBodyRightX += INCREMENT;
				}
				// To Left
				else if ((stWarms.bGoToLeft) && stWarms.bHM) {
					if (stWarms.m_wHeadBottomY - stWarms.m_wHeadTopY == 40) {
						stWarms.m_wHeadBottomY += 10;
						stWarms.m_wHeadTopY -= 10;
						stWarms.m_wHeadLeftX -= 20;
						stWarms.bLeftGrowHead = true;
					}
					else {
						stWarms.m_wHeadBottomY -= 10;
						stWarms.m_wHeadTopY += 10;
						stWarms.m_wHeadLeftX += 20;
						stWarms.bLeftGrowHead = false;
					}

					stWarms.m_wHeadLeftX -= INCREMENT;
					stWarms.m_wHeadRightX -= INCREMENT;
					stWarms.m_wBodyLeftX -= INCREMENT;
					stWarms.m_wBodyRightX -= INCREMENT;

					if (stWarms.m_wHeadLeftX == 60 && stWarms.m_wHeadBottomY - stWarms.m_wHeadTopY != 40) {
						stWarms.m_wHeadBottomY -= 10;
						stWarms.m_wHeadTopY += 10;
						stWarms.m_wHeadLeftX += 20;
						stWarms.bLeftGrowHead = false;
						
					}

				}

				// Right and Left
				if ((stWarms.m_wHeadRightX + INCREMENT > rectView.right) && stWarms.bHM) {
					if (stWarms.m_wHeadBottomY - stWarms.m_wHeadTopY != 40) {
						stWarms.m_wHeadBottomY -= 10;
						stWarms.m_wHeadTopY += 10;
						stWarms.m_wHeadRightX -= 20;
						stWarms.bRightGrowHead = false;
					}
					stWarms.bGoToLeft = true;
					stWarms.m_wHeadLeftX -= INCREMENT;
					stWarms.m_wHeadRightX -= INCREMENT;
					stWarms.m_wBodyLeftX = stWarms.m_wHeadRightX;
					stWarms.m_wBodyRightX = stWarms.m_wBodyLeftX + INCREMENT;
				}
			
				if ((stWarms.m_wHeadLeftX - INCREMENT < rectView.left) && stWarms.bHM) {
					stWarms.bGoToLeft = false;
					stWarms.m_wHeadLeftX += INCREMENT;
					stWarms.m_wHeadRightX += INCREMENT;
					stWarms.m_wBodyLeftX = stWarms.m_wHeadLeftX - INCREMENT;
					stWarms.m_wBodyRightX = stWarms.m_wHeadLeftX;
				}

				// To Up
				if ((!stWarms.bGoToBottom) && (!stWarms.bHM)) {
					stWarms.m_wHeadTopY -= INCREMENT;
					stWarms.m_wHeadBottomY -= INCREMENT;
					stWarms.m_wBodyTopY -= INCREMENT;
					stWarms.m_wBodyBottomY -= INCREMENT;

				}
				// To Down
				else if ((stWarms.bGoToBottom) && (!stWarms.bHM)) {
					stWarms.m_wHeadTopY += INCREMENT;
					stWarms.m_wHeadBottomY += INCREMENT;
					stWarms.m_wBodyTopY += INCREMENT;
					stWarms.m_wBodyBottomY += INCREMENT;

				}

				// Top and Bottom
				if ((stWarms.m_wHeadTopY - (INCREMENT) < rectView.top) && (!stWarms.bGoToBottom) && (!stWarms.bHM)) {
					stWarms.bGoToBottom = true;
					stWarms.m_wBodyTopY -= INCREMENT;
					stWarms.m_wBodyBottomY -= INCREMENT;
					stWarms.m_wHeadTopY = stWarms.m_wBodyBottomY;
					stWarms.m_wHeadBottomY = stWarms.m_wHeadTopY + INCREMENT;

				}
				else if ((stWarms.m_wHeadBottomY + INCREMENT > rectView.bottom) && (stWarms.bGoToBottom) && (!stWarms.bHM)) {
					stWarms.bGoToBottom = false;
					stWarms.m_wHeadTopY -= INCREMENT;
					stWarms.m_wHeadBottomY -= INCREMENT;
					stWarms.m_wBodyTopY = stWarms.m_wHeadBottomY;
					stWarms.m_wBodyBottomY = stWarms.m_wBodyTopY + INCREMENT;
				}

			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case JUMP_TIMER: {
			if (stWarms.bJumpOn) {
				stWarms.m_wHeadTopY += INCREMENT;
				stWarms.m_wHeadBottomY += INCREMENT;
				stWarms.m_wBodyTopY += INCREMENT;
				stWarms.m_wBodyBottomY += INCREMENT;

				for (int i = 0; i < MAX_NPC; ++i) {
					if (stNPC[i].bIsCreated) {
						stNPC[i].m_wHeadTopY += INCREMENT;
						stNPC[i].m_wHeadBottomY += INCREMENT;
						stNPC[i].m_wBodyTopY += INCREMENT;
						stNPC[i].m_wBodyBottomY += INCREMENT;
					}
				}
				stWarms.bJumpOn = false;

				KillTimer(hWnd, JUMP_TIMER);

				SetTimer(hWnd, P_TIMER, nSpeed, NULL);
				SetTimer(hWnd, MOVE_NPC_TIMER, nSpeed * 3, NULL);

				InvalidateRect(hWnd, NULL, TRUE);	
			}
			break;
		}
		case NEW_WARM_TIMER: {

			stNPC[bytCntNPC].bIsCreated = true;
			stNPC[bytCntNPC].bHaveBody = rand() % 2;

			if(bytCntNPC < MAX_NPC) bytCntNPC++;

			SetTimer(hWnd, MOVE_NPC_TIMER, nSpeed * 3, NULL);

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case MOVE_NPC_TIMER: {
			for (int i = 0; i < MAX_NPC; ++i) {
				if (stNPC[i].bIsCreated) {
					if (i == 0) {
						if (stNPC[i].m_wHeadLeftX < stWarms.m_wHeadLeftX) {
							// Move To Right
							stNPC[i].m_wBodyLeftX = stNPC[i].m_wHeadLeftX - INCREMENT;
							stNPC[i].m_wBodyRightX = stNPC[i].m_wHeadLeftX;

							stNPC[i].m_wHeadLeftX += INCREMENT;
							stNPC[i].m_wHeadRightX += INCREMENT;
							stNPC[i].m_wBodyLeftX += INCREMENT;
							stNPC[i].m_wBodyRightX += INCREMENT;
						}
						else if (stNPC[i].m_wHeadLeftX > stWarms.m_wHeadLeftX) {
							// Move to Left
							stNPC[i].m_wBodyLeftX = stNPC[i].m_wHeadRightX;
							stNPC[i].m_wBodyRightX = stNPC[i].m_wBodyLeftX + INCREMENT;

							stNPC[i].m_wHeadLeftX -= INCREMENT;
							stNPC[i].m_wHeadRightX -= INCREMENT;
							stNPC[i].m_wBodyLeftX -= INCREMENT;
							stNPC[i].m_wBodyRightX -= INCREMENT;
						}

						if (stNPC[i].m_wHeadTopY < stWarms.m_wHeadTopY) {
							// Move To Bttom
							stNPC[i].m_wHeadTopY += INCREMENT;
							stNPC[i].m_wHeadBottomY += INCREMENT;
							stNPC[i].m_wBodyTopY += INCREMENT;
							stNPC[i].m_wBodyBottomY += INCREMENT;

						}

						else if (stNPC[i].m_wHeadTopY > stWarms.m_wHeadTopY) {
							// Move To Up
							stNPC[i].m_wHeadTopY -= INCREMENT;
							stNPC[i].m_wHeadBottomY -= INCREMENT;
							stNPC[i].m_wBodyTopY -= INCREMENT;
							stNPC[i].m_wBodyBottomY -= INCREMENT;
						}
					}
					else {
						if (stNPC[i].m_wHeadLeftX < stNPC[i-1].m_wHeadLeftX) {
							// Move to Right
							stNPC[i].m_wBodyLeftX = stNPC[i].m_wHeadLeftX - INCREMENT;
							stNPC[i].m_wBodyRightX = stNPC[i].m_wHeadLeftX;

							stNPC[i].m_wHeadLeftX += INCREMENT;
							stNPC[i].m_wHeadRightX += INCREMENT;
							stNPC[i].m_wBodyLeftX += INCREMENT;
							stNPC[i].m_wBodyRightX += INCREMENT;

						}
						else if (stNPC[i].m_wHeadLeftX > stNPC[i - 1].m_wHeadLeftX) {
							// Move to Left
							stNPC[i].m_wBodyLeftX = stNPC[i].m_wHeadRightX;
							stNPC[i].m_wBodyRightX = stNPC[i].m_wBodyLeftX + INCREMENT;

							stNPC[i].m_wHeadLeftX -= INCREMENT;
							stNPC[i].m_wHeadRightX -= INCREMENT;
							stNPC[i].m_wBodyLeftX -= INCREMENT;
							stNPC[i].m_wBodyRightX -= INCREMENT;

						}

						if (stNPC[i].m_wHeadTopY < stNPC[i - 1].m_wHeadTopY) {
							// Move to Up
							stNPC[i].m_wHeadTopY += INCREMENT;
							stNPC[i].m_wHeadBottomY += INCREMENT;
							stNPC[i].m_wBodyTopY += INCREMENT;
							stNPC[i].m_wBodyBottomY += INCREMENT;
						}

						else if (stNPC[i].m_wHeadTopY > stNPC[i - 1].m_wHeadTopY) {
							// Move to Bottom
							stNPC[i].m_wHeadTopY -= INCREMENT;
							stNPC[i].m_wHeadBottomY -= INCREMENT;
							stNPC[i].m_wBodyTopY -= INCREMENT;
							stNPC[i].m_wBodyBottomY -= INCREMENT;
						}

					}
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		}
		break;
		}
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam); // 위의 세 메시지 외의 나머지 메시지는 OS로

}