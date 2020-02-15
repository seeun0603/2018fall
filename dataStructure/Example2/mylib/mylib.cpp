#include "stdafx.h"
#include "mylib.h"

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

void input_scores_file(FILE *infile, float score[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		fscanf_s(infile, "%f", &score[i]);
}

void print_scores(float score[], int n)
{
	int c;

	for (c = 0; c<n; c++)
	{
		printf("%f \n", score[c]);
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

void print_result(float max, float min, float sum, float mean)
{
	printf("**************************\n");
	printf("최고점수: %f\n", max);
	printf("최저점수: %f\n", min);
	printf("합계점수: %f\n", sum);
	printf("평균점수: %f\n", mean);
	printf("**************************\n");
}

void save_result_file(FILE *outfile, float max, float min, float sum, float mean)
{
	fprintf(outfile, "최고 점수: %f\n", max);
	fprintf(outfile, "최저 점수: %f\n", min);
	fprintf(outfile, "합계 점수: %f\n", sum);
	fprintf(outfile, "평균 점수: %f\n", mean);
}