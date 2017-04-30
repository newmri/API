#include "Define.h"

#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

HINSTANCE g_hInst;
LPCTSTR lpszClass = "INVERSUS";

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 1280, 800, NULL, (HMENU)NULL, hInstance, NULL);
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

void EnterIntroScene();
void EnterInGameScene();

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �޽��� ó���ϱ�
	switch (uMsg) {
	case WM_CREATE:
		GAMEMANAGER->Init(hWnd, g_hInst);
		EnterIntroScene();
		SetTimer(hWnd, 1, 30, TimerProc);
		
		break;
	case WM_GETMINMAXINFO: {
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WINDOWS_SIZE_X;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WINDOWS_SIZE_Y;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WINDOWS_SIZE_X;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WINDOWS_SIZE_Y;
		return FALSE;
	}
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); // ���� �� �޽��� ���� ������ �޽����� OS��
}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{

	for (CObject* d : GAMEMANAGER->GetList()){
		CPanel* tempPanel = dynamic_cast<CPanel*>(d);
		tempPanel->Draw();
	}
	//InvalidateRect(hWnd, NULL, TRUE);
}

void EnterIntroScene()
{
	RECT rect;
	LONG uY{500};
	STPenInfo stPenInfo;

	CObject* cTitle = new CPlainPanel;
	cTitle->SetPos(POINT{ 0,200 });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 250;
	cTitle->SetRect(rect);
	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	CPlainPanel* pPTitle = dynamic_cast<CPlainPanel*>(cTitle);
	pPTitle->SetString("I N V E R S U S");
	stPenInfo.color = RGB(255, 255, 255);
	stPenInfo.width = 100;
	pPTitle->SetPenInfo(stPenInfo);
	GAMEMANAGER->GetList().push_back(cTitle);
	
	cTitle = new CActivePanel;
	cTitle->SetPos(POINT{ 0, uY });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 50;
	cTitle->SetRect(rect);
	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	CActivePanel* pATitle = dynamic_cast<CActivePanel*>(cTitle);
	pATitle->SetString("N E W  G A M E");
	stPenInfo.color = RGB(255, 255, 255);
	stPenInfo.width = 30;
	pATitle->SetPenInfo(stPenInfo);
	GAMEMANAGER->GetList().push_back(cTitle);
	uY += 70;
	
	cTitle = new CActivePanel;
	cTitle->SetPos(POINT{ 0, uY });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 50;
	cTitle->SetRect(rect);
	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	pATitle = dynamic_cast<CActivePanel*>(cTitle);
	pATitle->SetString("H E L P");
	pATitle->SetPenInfo(stPenInfo);
	GAMEMANAGER->GetList().push_back(cTitle);
	uY += 70;

	cTitle = new CActivePanel;
	cTitle->SetPos(POINT{ 0, uY });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 50;
	cTitle->SetRect(rect);
	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	pATitle = dynamic_cast<CActivePanel*>(cTitle);
	pATitle->SetString("E X I T");
	pATitle->SetPenInfo(stPenInfo);
	GAMEMANAGER->GetList().push_back(cTitle);

}

void EnterInGameScene()
{

}