#pragma once

#include <list>

#include "CObject.h"

#define MAP_SIZE_X 19
#define MAP_SIZE_Y 13

class CGameManager
{
public:
	static CGameManager* GetInstance()
	{
		if (m_Instance == nullptr) m_Instance = new CGameManager;
		return m_Instance;
	}

	void Init(HWND& a_hWnd, HINSTANCE& a_hInst)
	{
		m_hWnd = a_hWnd;
		m_hInst = a_hInst;

		GetClientRect(a_hWnd, &m_clntrt);
	}

	HWND getHWND() { return m_hWnd; }

	//const HDC& GetHDC() { m_hdc = GetDC(m_hWnd);  return m_hdc; }
	//void ReleaseHDC() { ReleaseDC(m_hWnd, m_hdc); }

	HINSTANCE GethInst() { return m_hInst; }
	void SetInst(HINSTANCE& a_hInst) { m_hInst = a_hInst; }

	RECT GetRect() { return m_clntrt; }
	void SetRect(RECT& a_rect) { m_clntrt = a_rect; }

	static bool Destroy()
	{
		if (m_Instance){ delete m_Instance; return true; }
		return false;
	}

	BYTE(*GetMap())[MAP_SIZE_X] { return m_bytMap; }
	
	UINT GetScore() { return m_uScore; }

	std::list<CObject*>& GetList() { return m_List; }

private:
	CGameManager() {};
	CGameManager(const CGameManager&) = delete;
	void operator=(const CGameManager&) = delete;

	static CGameManager* m_Instance;

private:
	BYTE m_bytMap[MAP_SIZE_Y][MAP_SIZE_X];
	UINT m_uScore;
	std::list<CObject*> m_List;

private:
	HWND m_hWnd;
	HDC m_hdc;
	HINSTANCE m_hInst;
	RECT m_clntrt;
};

