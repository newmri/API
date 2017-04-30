#include "CObject.h"
#include "Define.h"

CObject::CObject(){ ZeroMemory(&m_pos, sizeof(m_pos)); }

const COLORREF& CObject::GetColor() { return m_color; }
void CObject::SetColor(const COLORREF& a_color) { m_color = a_color; }

POINT CObject::GetPos() { return m_pos; }
void CObject::SetPos(POINT a_pos) { m_pos = a_pos; }

const RECT& CObject::GetRect() { return m_rect; }
void CObject::SetRect(const RECT& a_rect) { m_rect = a_rect; }