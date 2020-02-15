#include <stdio.h>
void main()
{
	int c, n;
	float score[30];
	float max, min, sum = 0, mean = 0;

	// 학생 수 입력
	printf("학생수? ");
	scanf("%d", &n);

	// 점수 입력
	printf("\n\n");
	printf("점수를 입력하세요.\n");
	for (c = 0; c<n; c++)
	{
		scanf("%f", &score[c]);
	}

	// 최고점수 계산
	max = score[0];
	for (int i = 1; i < n; i++)
	{
		if (score[i] > max)
			max = score[i];
	}

	// 최저점수 계산
	min = score[0];
	for (int i = 1; i < n; i++)
	{
		if (score[i] < min)
			min = score[i];
	}

	// 합계점수 계산
	for (int i = 0; i < n; i++)
		sum += score[i];

	// 평균점수 계산
	mean = sum / n;

	/* 점수 출력 */
	printf("**************************\n");
	printf("최고점수: %f\n", max);
	printf("최저점수: %f\n", min);
	printf("합계점수: %f\n", sum);
	printf("평균점수: %f\n", mean);
	printf("**************************\n");
}