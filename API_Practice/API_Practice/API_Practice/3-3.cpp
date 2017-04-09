// 신호등 이용, 이동하는 도형 그리기
// 화면을 y값으로 3등분, 각 등분에 임의의 크기의 사각형 그림, 각 도형의 이동 속도는 다름
// 맨 위의 사각형은 왼쪽에서 오른쪽으로 이동
// 중간 사각형은 오른쪽에서 왼쪽으로 이동
// 맨 아래의 사각형은 왼쪽에서 오른쪽으로 이동
// 신호등 기능: 화면에 파랑색/노랑색/빨강색의 신호등이 그려져있음 키보드에 의해 신호등이 선택됨 선택된 신호등 가장자리에 선택 표시
// b/B: 이동 시작 y:Y 3초 후 정지 r/R: 바로 정지
// 왼쪽 또는 오른쪽 가장자리에 도달시 반대편 가장자리에 나타남 이때, 화면에 안그려 지는 일부분은 반대 편에 그려짐
#include <windows.h>
#include <stdio.h>
#include <time.h>
#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOW_X 1280
#define WINDOW_Y 800
#define MAX_CAR 3
#define MOVE 100
enum { TOP_CAR, MIDDLE_CAR, BOTTOM_CAR, STOP };
enum ELIGHT {eNOTHING, eBLUE, eYELLOW, eRED };
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


class CCar
{
public:
	void SetPoint(const RECT& a_rect, const USHORT& a_wType)
	{
		m_rect = a_rect;
		switch (a_wType) {
		case TOP_CAR:
			m_wTopY = m_rect.bottom / 4;
			m_wBottomY = m_rect.bottom / 4 + MOVE / 2;
			break;
		case MIDDLE_CAR:
			m_wTopY = m_rect.bottom / 2;
			m_wBottomY = m_rect.bottom / 2 + MOVE / 2;
			m_wRightX = m_rect.right;
			m_wLeftX = m_rect.right - MOVE;
			break;
		case BOTTOM_CAR:
			m_wTopY = m_rect.bottom - 150;
			m_wBottomY = a_rect.bottom - MOVE;
			break;
		}
	}
	void Draw(const HDC& a_hdc) {
		Rectangle(a_hdc, m_wLeftX, m_wTopY, m_wRightX, m_wBottomY);
	}
	void Draw(const HDC& a_hdc, const bool& a_IsStopped) {
		if(a_IsStopped) Rectangle(a_hdc, m_wRLeftX, m_wRTopY, m_wRRightX, m_wRBottomY);
	}
	void Move()
	{	
		if (!m_bToLeft) {
			if (m_rect.right - m_wLeftX < MOVE) {
				m_bDrawRemained = true;

				m_wRightX = m_wRightX - m_rect.right;
				m_wLeftX = 0;
			}
			else { m_wLeftX += MOVE; m_wRightX += MOVE; }
		}

		else {
			if (m_wLeftX < MOVE) {
				m_bDrawRemained = true;
				m_wRightX = m_wLeftX;
				m_wLeftX = m_rect.left;
			}
			else { m_wLeftX -= MOVE; m_wRightX -= MOVE; }
		}
	}
	bool IsRemainedToDraw() { return m_bDrawRemained; }
	void CheckRemainedToDraw()
	{
		if (!m_bToLeft) {
			if ((m_rect.right - m_wLeftX) < MOVE) {
				m_wRLeftX = m_wLeftX; m_wRRightX = m_wRightX;
				m_wRBottomY = m_wBottomY; m_wRTopY = m_wTopY;
				m_bDrawRemained = true;
				m_wRightX = m_wRightX - m_rect.right;
				m_wLeftX = 0;
			}
		}
		else {
			if (m_wLeftX == m_rect.right - 64) {
				m_wRLeftX = m_rect.left;
				m_wRRightX = MOVE - 64;
				m_wRBottomY = m_wBottomY; m_wRTopY = m_wTopY;
				m_bDrawRemained = true;
			}
		}
	}
	void DrawWhiteRect(const HDC& a_hdc)
	{
		if (!m_bToLeft) {
			Rectangle(a_hdc, m_wLeftX, m_wTopY + 1, m_wRightX - 10, m_wBottomY - 1);
			m_wRightX = MOVE;
		}
		
		else {
			Rectangle(a_hdc, m_wRLeftX, m_wRTopY + 1, m_wRRightX - 10, m_wRBottomY - 1);
			m_wLeftX = m_rect.right - 64;
			m_wRightX = m_wLeftX + MOVE;
		}
		
		m_bDrawRemained = false;
	}
	void SetToLeft() { m_bToLeft = true; }
	bool GetToLeft() { return m_bToLeft; }
private:
	USHORT m_wLeftX{}, m_wRightX{ MOVE }, m_wTopY{}, m_wBottomY{};
	USHORT m_wRLeftX{}, m_wRRightX{}, m_wRTopY{}, m_wRBottomY{};
	RECT m_rect;
	bool m_bDrawRemained = false;
	bool m_bToLeft = false;
	
};

class CTrafficLight
{
public:
	void SetPoint(const RECT& a_rect)
	{
		m_rect = a_rect;

		m_eLight = eNOTHING;
		m_wLeftX = m_rect.right / 2 - MOVE;
		m_wRightX = m_wLeftX + MOVE + 30;
		m_wTopY = m_rect.top + 10;
		m_wBottomY = m_wTopY + MOVE / 2;
	}
	
	void Draw(const HDC& a_hdc)
	{
		Rectangle(a_hdc, m_wLeftX, m_wTopY, m_wRightX, m_wBottomY);

		DrawBlue(a_hdc);
		DrawYellow(a_hdc);
		DrawRed(a_hdc);

		HBRUSH hOldBrush = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(a_hdc, hOldBrush);
	}
	void SetLight(const ELIGHT& a_eLight) { m_eLight = a_eLight; }
private:
	void DrawBlue(const HDC& a_hdc)
	{
		HPEN hPen, hOldPen;

		if (m_eLight == eBLUE) {
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
			hOldPen = (HPEN)SelectObject(a_hdc, hPen);
		}
		HBRUSH hBrush = CreateSolidBrush(RGB(1, 0, 255)); // Blue
		HBRUSH hOldBrush = (HBRUSH)SelectObject(a_hdc, hBrush);
		Ellipse(a_hdc, m_wLeftX + 10, m_wTopY + 10, m_wLeftX + 40, m_wBottomY - 10);
		SelectObject(a_hdc, hOldBrush);
		DeleteObject(hBrush);

		if (m_eLight == eBLUE) {
			SelectObject(a_hdc, hOldPen);
			DeleteObject(hPen);
		}
	}
	void DrawYellow(const HDC& a_hdc)
	{
		HPEN hPen, hOldPen;

		if (m_eLight == eYELLOW) {
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
			hOldPen = (HPEN)SelectObject(a_hdc, hPen);
		}

		HBRUSH hBrush = CreateSolidBrush(RGB(255, 228, 0)); // Yellow
		HBRUSH hOldBrush = (HBRUSH)SelectObject(a_hdc, hBrush);
		Ellipse(a_hdc, m_wLeftX + 50, m_wTopY + 10, m_wLeftX + 80, m_wBottomY - 10);
		SelectObject(a_hdc, hOldBrush);
		DeleteObject(hBrush);

		if (m_eLight == eYELLOW) {
			SelectObject(a_hdc, hOldPen);
			DeleteObject(hPen);
		}
	}
	void DrawRed(const HDC& a_hdc)
	{
		HPEN hPen, hOldPen;

		if (m_eLight == eRED) {
			hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
			hOldPen = (HPEN)SelectObject(a_hdc, hPen);
		}

		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Red
		HBRUSH hOldBrush = (HBRUSH)SelectObject(a_hdc, hBrush);
		Ellipse(a_hdc, m_wLeftX + 90, m_wTopY + 10, m_wLeftX + 120, m_wBottomY - 10);
		SelectObject(a_hdc, hOldBrush);
		DeleteObject(hBrush);

		if (m_eLight == eRED) {
			SelectObject(a_hdc, hOldPen);
			DeleteObject(hPen);
		}
	}
private:
	USHORT m_wLeftX{}, m_wRightX{}, m_wTopY{}, m_wBottomY{};
	RECT m_rect;
	ELIGHT m_eLight;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	static RECT rect;
	static CCar cCars[MAX_CAR];
	static int nSpeed{ 100 };
	static CTrafficLight cTrafficLight;
	static bool bMoveCar = true;
	static bool bIsStopped = false;
	switch (iMessage) {
	case WM_CREATE: {
		srand((unsigned)time(NULL));
		GetClientRect(hWnd, &rect);

		cTrafficLight.SetPoint(rect);

		cCars[TOP_CAR].SetPoint(rect, TOP_CAR);
		cCars[MIDDLE_CAR].SetPoint(rect, MIDDLE_CAR);
		cCars[BOTTOM_CAR].SetPoint(rect, BOTTOM_CAR);

		for(int i=0; i< MAX_CAR; ++i) SetTimer(hWnd, i, nSpeed * (i+1), NULL);

		break;
	}

	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);

		cTrafficLight.Draw(hdc);

		for (int i = 0; i < MAX_CAR; ++i) {
			cCars[i].Draw(hdc);

			if (cCars[i].IsRemainedToDraw()) {

				if (bIsStopped) cCars[i].Draw(hdc, bIsStopped);

				// Erase Left
				hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
				hOldPen = (HPEN)SelectObject(hdc, hPen);
				cCars[i].DrawWhiteRect(hdc);
				SelectObject(hdc, hOldPen);
				DeleteObject(hPen);

			}

		}
		EndPaint(hWnd, &ps);
		break;
	}
	
	case WM_CHAR: {
		switch (wParam) {
		case 'r':
		case 'R':
			for (int i = 0; i < MAX_CAR; ++i) {
				KillTimer(hWnd, i);
				cCars[i].CheckRemainedToDraw();
			}
			bIsStopped = true;
			cTrafficLight.SetLight(eRED);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'y':
		case 'Y':
			cTrafficLight.SetLight(eYELLOW);
			SetTimer(hWnd, STOP, 3000, NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'e':
		case 'E':
			for (int i = 0; i < MAX_CAR; ++i) SetTimer(hWnd, i, nSpeed  * (i + 1), NULL);
			bIsStopped = false;
			cTrafficLight.SetLight(eBLUE);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
	}

	case WM_TIMER: {
		switch (wParam) {
		case TOP_CAR:
			cCars[TOP_CAR].Move();
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MIDDLE_CAR:
			cCars[MIDDLE_CAR].SetToLeft();
			cCars[MIDDLE_CAR].Move();
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case BOTTOM_CAR:
			cCars[BOTTOM_CAR].Move();
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case STOP:
			KillTimer(hWnd, STOP);
			for (int i = 0; i < MAX_CAR; ++i) {
				KillTimer(hWnd, i);
				cCars[i].CheckRemainedToDraw();
			}
			bIsStopped = true;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
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