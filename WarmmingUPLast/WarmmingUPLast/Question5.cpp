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
	
	/*if (MAX_SIZE != m_equation.size()) {
		m_errchk = true;
		return;
	}*/

	//string::iterator itor = m_equation.begin();

	//for (int i = 0; i < MAX_SIZE; ++i) {


	//	if (1 & i == 1) {
	//		if ('*' != *itor && '/' != *itor && '+' != *itor && '-' != *itor) {
	//			m_errchk = true;
	//			return;
	//		}
	//	}

	//	else if(1 & i == 0){
	//		if ('*' == *itor || '/' == *itor || '+' == *itor || '-' == *itor) {
	//			m_errchk = true;
	//			return;
	//		}
	//		}
	//	

	//	++itor;
	//}

	

	

}

bool Question5::GetEquation()
{
	cout << "Input numbers: ";

	scanf_s(m_equation, "%c");
	CheckError();

	if (m_errchk) {
		cout << "Error has been ocuured bud! Ex) 1+2+3+4" << endl;
		//m_equation.clear();
		return false;
	}

	return true;


}

void Question5::DevideEquation()
{
	/*string::iterator itor = m_equation.begin();

	for (int i = 0; i < MAX_SIZE; ++i, ++itor) {
		
			if ('*' == *itor) {
				m_temparray[i - 1] = itor[i - 2];
				m_temparray[i] = itor[i-1];
				m_temparray[i+1] = itor[i];

				m_itor = itor;
				return;
			}
			
	}*/
}

void Question5::CalculateByOperator()
{
	DevideEquation();

	m_lvalue = atoi(&m_temparray[0]);
	m_rvalue = atoi(&m_temparray[2]);

	switch (m_temparray[1]) {

	case '*':
		m_result = m_lvalue*m_rvalue;
		break;
	case '/':
		m_result = m_lvalue/m_rvalue;
		break;
	case '+':
		m_result = m_lvalue+m_rvalue;
		break;
	case '-':
		m_result = m_lvalue-m_rvalue;
		break;

	}

	//cout << m_result << endl;

}