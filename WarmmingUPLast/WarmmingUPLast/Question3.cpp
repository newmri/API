#include "Question3.h"

void Question3::GetSentence()
{
	cout << "Input sentence: ";
	cin.ignore();
	getline(cin, m_sentence);

}

void Question3::ShowSentence()
{
	cout << "You entered " << m_sentence << endl;

}

void Question3::ModifySentence()
{
	string tempstr;
	string resultstr;
	int paddingnum{};

	srand((unsigned)time(NULL));

	for (string::iterator itor = m_sentence.begin(); itor != m_sentence.end(); ++itor) {
		char temp = *itor;
		if (temp >= SMALL_MIN && temp <= SMALL_MAX) temp += CHAR_DIFFER;
		else if (temp >= CAPITAL_MIN && temp <= CAPITAL_MAX) temp -= CHAR_DIFFER;

		tempstr = temp;
		resultstr.append(tempstr);

		temp = (rand() % RAND_ADD) + RAND_MIN;

		while (!('!' == temp || '@' == temp || '#' == temp || '$' == temp || '%' == temp))
			temp = (rand() % RAND_ADD) + RAND_MIN;

		tempstr = temp;
		resultstr.append(tempstr);
	}

	cout << "Result is: " << resultstr << endl;
}
