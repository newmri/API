#include "Question5.h"

Question5::Question5()
{
	m_lvalue = 0;
	m_rvalue = 0;
	m_result = 0;
	m_errchk = false;
	
}

void Question5::CheckError()
{
	


	

	for (int i = 0; i < MAX_SIZE; ++i) {


		if (1 & i == 1) {
			if ('*' != m_equation[i] && '/' != m_equation[i] && '+' != m_equation[i] && '-' != m_equation[i]) {
				m_errchk = true;
				return;
			}
		}

		else if(1 & i == 0){
			if ('*' == m_equation[i] || '/' == m_equation[i] || '+' == m_equation[i] || '-' == m_equation[i]) {
				m_errchk = true;
				return;
			}
			}
		

	
	}

	

	

}

bool Question5::GetEquation()
{
		cout << "Input numbers: ";

		cin >> m_equation;
		CheckError();
		
		if (m_errchk) {
			cout << "Error has been ocuured bud! Ex) 1+2+3+4" << endl;
			return false;
		}

	DevideEquation();
	return true;


}

void Question5::DevideEquation()
{

	for (int i = 0; i < MAX_SIZE; ++i) {
		switch (m_equation[i]) {
		case '*':
			m_temparray[i - 1] = atoi(&m_equation[i - 1]);
			m_temparray[i] = 7;
			m_temparray[i + 1] = atoi(&m_equation[i + 1]);
			break;
		case '/':
			m_temparray[i - 1] = atoi(&m_equation[i - 1]);
			m_temparray[i] = 6;
			m_temparray[i + 1] = atoi(&m_equation[i + 1]);
			break;
		case '+':
			m_temparray[i - 1] = atoi(&m_equation[i - 1]);
			m_temparray[i] = 5;
			m_temparray[i + 1] = atoi(&m_equation[i + 1]);
			break;
		case '-':
			m_temparray[i - 1] = atoi(&m_equation[i - 1]);
			m_temparray[i] = 4;
			m_temparray[i + 1] = atoi(&m_equation[i + 1]);
			break;
		}

	}

	unsigned int tmp{};
	unsigned int tem2{};
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE - i - 1; j++) {
			if (j & 1 == 1) {
				if (m_temparray[j] < m_temparray[j + 2]) {
					tmp = m_temparray[j];
					m_temparray[j] = m_temparray[j + 2];
					m_temparray[j + 2] = tmp;

					tem2 = m_temparray[j - 1];
					m_temparray[j - 1] = m_temparray[j + 1];
					m_temparray[j + 1] = tem2;

					tem2 = m_temparray[j +1];
					m_temparray[j + 1] = m_temparray[j + 3];
					m_temparray[j + 3] = tem2;
				}
			}
		}
	}

	
	
	for (int i = 0; i < MAX_SIZE; ++i) {
		cout << m_temparray[i] << endl;
	}
	//m_temparray[MAX_SIZE] = '\0';
	//cout << m_temparray << endl;
	}



	


void Question5::CalculateByOperator()
{
	

	for (int i = 0; i < MAX_SIZE; ++i) {
		
		if (!(2 & i == 1)) {


		}
		
		switch (m_temparray[1]) {

		case '*':
			m_result = m_lvalue*m_rvalue;
			break;
		case '/':
			m_result = m_lvalue / m_rvalue;
			break;
		case '+':
			m_result = m_lvalue + m_rvalue;
			break;
		case '-':
			m_result = m_lvalue - m_rvalue;
			break;

		}

	}

	//cout << m_result << endl;

}