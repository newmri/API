#include "Questions.h"
#define MAX_NUM 1000


void ShowMultipleResult(void)
{
	int num = 0;

	printf("3의 배수 ");
	for (int i = 0; i <= MAX_NUM; i++) {
		if (i % 3 == 0) {
			num += i;
			printf("%d, ", i);
		}
	}
	printf("합계: %d \n", num);
	num = 0;

	printf("7의 배수 ");
	for (int i = 0; i <= MAX_NUM; i++) {
		if (i % 7 == 0) {
			num += i;
			printf("%d, ", i);
		}
	}
	printf("합계: %d \n", num);
	num = 0;

	printf("3의 배수이거나 7의 배수의 수의 합계: ");
	for (int i = 0; i <= MAX_NUM; i++) {
		if (i % 3 == 0 || i % 7 == 0) num += i;
	}
	printf("합계: %d \n", num);
}