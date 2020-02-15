#include "stdafx.h"
#include "mylib.h"

void input_scores(float *score, int n)
{
	int c;
	printf("\n");
	printf("������ �Է��ϼ���.\n");
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
	printf("�ְ�����: %f\n", max);
	printf("��������: %f\n", min);
	printf("�հ�����: %f\n", sum);
	printf("�������: %f\n", mean);
	printf("**************************\n");
}

void save_result_file(FILE *outfile, float max, float min, float sum, float mean)
{
	fprintf(outfile, "�ְ� ����: %f\n", max);
	fprintf(outfile, "���� ����: %f\n", min);
	fprintf(outfile, "�հ� ����: %f\n", sum);
	fprintf(outfile, "��� ����: %f\n", mean);
}