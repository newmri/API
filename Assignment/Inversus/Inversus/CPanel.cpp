#include "Define.h"
#include <atlstr.h>
void CPanel::Draw()
{
	HDC hdc = GetDC(GAMEMANAGER->getHWND());
	HBRUSH hBrush, hOldBrush;
	HFONT hFont, hOldFont;

	hBrush = CreateSolidBrush(m_color);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	hFont = CreateFont(m_stPenInfo.width, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("±Ã¼­"));

	hOldFont = (HFONT)SelectObject(hdc, hFont);

	Rectangle(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, m_stPenInfo.color);
	DrawText(hdc, m_str.c_str(), m_str.length(), &m_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldFont);
	DeleteObject(hBrush);
	DeleteObject(hFont);
	ReleaseDC(GAMEMANAGER->getHWND(), hdc);
}

const std::string& CPanel::GetString() { return m_str; }
void CPanel::SetString(const std::string& a_str) { m_str = a_str; }

const STPenInfo& CPanel::GetPenInfo() { return m_stPenInfo; }
void CPanel::SetPenInfo(const STPenInfo& a_stPenInfo) { m_stPenInfo = a_stPenInfo; }