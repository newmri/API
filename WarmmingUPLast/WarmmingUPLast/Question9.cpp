#include "Question9.h"


Question9::Question9()
{
	m_len = 0;

}

void Question9::GetNumber()
{
	cout << "Input number:";

	cin >> m_num;

	memcpy(m_oldnum, m_num, MAX_NUM);

}

void Question9::Process()
{
	bool first = true;
	for (int i = 0; i < MAX_NUM; ++i) {
		if ('\0' == m_num[i]) m_len = i;
	}
	
	int temparr[MAX_NUM];
	int count = 1;
	for (int i = m_len-1; i != 0; --i, ++count) {
		
		
		   if (0 == count % 3 && i != m_len -1) {
				m_num[i-1] = ',';
				

				for (int j = m_len; j >= 0; --j) {
					m_num[j + 1] = m_num[j];
					
				}
				for (int j = i -1; j >= 0; --j) {
					m_num[j] = m_oldnum[j];
				}

				first = false;
				count = 0;
			}

		  
	}
	if (10 <= m_len) {
		m_num[m_len + 2] = m_oldnum[m_len - 1];
		m_num[m_len + 3] = '\0';
	}

	else m_num[m_len+2] = '\0';



	
}

void Question9::ShowResult()
{
	cout << m_num << endl;
}