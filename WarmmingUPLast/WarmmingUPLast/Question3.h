#pragma once

#include <string>
#include <ctime>
#include "Common.h"

enum {  RAND_ADD=31, CHAR_DIFFER = 32, RAND_MIN = 33, SMALL_MIN = 65, SMALL_MAX = 95, CAPITAL_MIN = 97, CAPITAL_MAX = 122 };

class Question3
{
private:
	string m_sentence;
public:
	void GetSentence();
	void ShowSentence();
	void ModifySentence();

};