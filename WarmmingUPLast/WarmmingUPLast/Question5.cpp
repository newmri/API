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

	
	return true;


}

void Question5::DevideEquation()
{

	/*
	* = 42
	+ = 43
	- = 45
	/ = 47
	*/
	for (int i = 0; i < MAX_SIZE; ++i) {
		
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