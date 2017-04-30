#pragma once

#include "CObject.h"

struct STPenInfo
{
	COLORREF color;
	BYTE width;

	STPenInfo()
	{
		ZeroMemory(&color, sizeof(color));
		width = 0;
	}
};

class CPanel : public CObject
{

public:
	void IsMouseOver();
	void Draw();

	const std::string& GetString();
	void SetString(const std::string& a_str);

	const STPenInfo& GetPenInfo();
	void SetPenInfo(const STPenInfo& a_stPenInfo);
private:
	std::string m_str;
	STPenInfo m_stPenInfo;
};