#include<stdio.h>
#include<stdlib.h>

void input_scores(float *score, int n)
{
	int c;
	printf("\n");
	printf("점수를 입력하세요.\n");
	for (c = 0; c<n; c++)
	{
		scanf_s("%f", &score[c]);
	}
}

float max_score(float *score, int n)
{
	float max;
	if (n == 1)return *(score + (n - 1));
	max = max_score(score, n - 1);
	if (*(score + (n - 1)) > max)
	{
		max = *(score + (n - 1));
		return max;
	}
	else return max;
}

float min_score(float *score, int n)
{
	float min;
	if (n == 1)return *(score + (n - 1));
	min = min_score(score, n - 1);
	if (*(score + (n - 1)) < min)
	{
		min = *(score + (n - 1));
		return min;
	}
	else return min;
}

float sum_scores(float *score, int n)
{
	float sum;
	if (n == 1) return *(score + (n - 1));
	return (sum_scores(score, n - 1) + *(score + (n - 1)));
}

void print_result(float max, float min, float sum, float mean)
{
	printf("**************************\n");
	printf("최고점수: %f\n", max);
	printf("최저점수: %f\n", min);
	printf("합계점수: %f\n", sum);
	printf("평균점수: %f\n", mean);
	printf("**************************\n");
}

void main()
{
	int n;
	float *score;
	float max, min, sum, mean;

	printf("학생수? ");
	scanf_s("%d", &n);

	score = (float *)malloc(n * sizeof(float));
	if (score == NULL)
	{
		printf("메모리 할당 오류\n");
		return;
	}

	input_scores(score, n);

	max = max_score(score, n);
	min = min_score(score, n);
	sum = sum_scores(score, n);
	mean = sum / (float)n;

	print_result(max, min, sum, mean);
}