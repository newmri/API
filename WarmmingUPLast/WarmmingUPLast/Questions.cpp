#include "Questions.h"
#define MAX_NUM 1000


void ShowMultipleResult(void)
{
	int num = 0;

	printf("3�� ��� ");
	for (int i = 0; i <= MAX_NUM; i++) {
		if (i % 3 == 0) {
			num += i;
			printf("%d, ", i);
		}
	}
	printf("�հ�: %d \n", num);
	num = 0;

	printf("7�� ��� ");
	for (int i = 0; i <= MAX_NUM; i++) {
		if (i % 7 == 0) {
			num += i;
			printf("%d, ", i);
		}
	}
	printf("�հ�: %d \n", num);
	num = 0;

	printf("3�� ����̰ų� 7�� ����� ���� �հ�: ");
	for (int i = 0; i <= MAX_NUM; i++) {
		if (i % 3 == 0 || i % 7 == 0) num += i;
	}
	printf("�հ�: %d \n", num);
}