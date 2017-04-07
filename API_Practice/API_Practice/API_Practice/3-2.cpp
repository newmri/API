#include <windows.h>
#include <stdio.h>

#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOW_X 800
#define WINDOW_Y 600

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



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, hOldPen;

	static RECT rect;
	switch (iMessage) {
	case WM_CREATE: {
		GetClientRect(hWnd, &rect);
		SetTimer(hWnd, 1, 100, NULL);
		break;
	}

	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, rect.right / 4, rect.bottom / 4, rect.right / 4 + 10, rect.bottom / 4 + 10);
		Ellipse(hdc, (rect.right) - (rect.right / 4), rect.bottom / 4, ((rect.right) - (rect.right / 4)) + 10, rect.bottom / 4 + 10);
		Ellipse(hdc, rect.right / 4, (rect.bottom) - (rect.bottom / 4), rect.right / 4 + 10, ((rect.bottom) - (rect.bottom / 4)) + 10);
		Ellipse(hdc, (rect.right) - (rect.right / 4), (rect.bottom) - (rect.bottom / 4), ((rect.right) - (rect.right / 4)) + 10, ((rect.bottom) - (rect.bottom / 4)) + 10);
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_TIMER: {

		//InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam); // ���� �� �޽��� ���� ������ �޽����� OS��

}