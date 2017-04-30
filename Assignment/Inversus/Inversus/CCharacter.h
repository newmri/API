#pragma once

#include "CObject.h"

enum EMove { UP, DOWN, LEFT, RIGHT };

class CCharacter : public CObject
{
public:
	virtual void Move() = 0;
	void ChkCollision();
};