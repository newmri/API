#pragma once

#include<vector>

#include "CCharacter.h"

class CPlayer : public CCharacter
{
public:
	virtual void Move(const EMove& a_eMove);
private:
	std::vector<STItem> m_vItemList;
};