#include <windows.h>
#include <atlstr.h>

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
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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
	RECT rect;
	CString cStr;
	int x{}, y{};
	int nBlankX{}, nBlankY{};
	int nLeftEnd{}, nRightEnd{800};
	switch (iMessage) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (int i = 1; i <= 40; ++i) {
			rect.top = y;
			rect.bottom = y += 77;

			for (int j = 1; j<=20; ++j) {
				cStr.Format("(%d, %d)", i, j);
				rect.left = x;
				rect.right = x += 114;
				
				if(rect.left >= nLeftEnd && rect.left < nRightEnd - 114)
				DrawText(hdc, cStr, cStr.GetLength(), &rect, DT_CENTER);
			}
			nLeftEnd += 114;
			nRightEnd -= 114;
			x = 0;
		}

		y = 600;
		x = 0;
		nLeftEnd = 0;
		nRightEnd = 800;

		for (int i = 1; i <= 40; ++i) {
			rect.bottom = y;
			rect.top = y-=77;
			for (int j = 1; j <= 20; ++j) {
				cStr.Format("(%d, %d)", i, j);
				rect.left = x;
				rect.right = x += 114;

				if (rect.left >= nLeftEnd && rect.left < nRightEnd - 114)
					DrawText(hdc, cStr, cStr.GetLength(), &rect, DT_CENTER);
			}
			nLeftEnd += 114;
			nRightEnd -= 114;
			x = 0;

		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam); // ���� �� �޽��� ���� ������ �޽����� OS��
}