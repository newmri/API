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

}
