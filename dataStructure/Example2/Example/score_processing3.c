#include<stdio.h>

void input_scores_file(FILE *infile, float score[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		fscanf(infile, "%f", &score[i]);
}

float max_score(float score[], int n)
{
	float max;
	if (n == 1)return score[n - 1];
	max = max_score(score, n - 1);
	if (score[n - 1] > max)
	{
		max = score[n - 1];
		return max;
	}
	else return max;
}

float min_score(float score[], int n)
{
	float min;
	if (n == 1)return score[n - 1];
	min = min_score(score, n - 1);
	if (score[n - 1] < min)
	{
		min = score[n - 1];
		return min;
	}
	else return min;
}

float sum_score(float score[], int n)
{
	float sum;
	if (n == 1) return score[n - 1];
	return (sum_score(score, n - 1) + score[n - 1]);
}

void input_scores(float score[], int n)
{
	int c;

	for (c = 0; c<n; c++)
	{
		scanf("%f", &score[c]);
	}
}

void print_scores(float score[], int n)
{
	int c;

	for (c = 0; c<n; c++)
	{
		printf("%f \n", score[c]);
	}
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

void main()
{
	int n;
	float score[30];
	float max, min, sum, mean;
	FILE *infile, *outfile;

	infile = (FILE *)fopen("score.txt", "r");
	if (infile == NULL)
	{
		printf("����!!!");
		return;
	}

	/*�л��� �Է�*/
	printf("�л� ��?");
	scanf("%d", &n);

	/*���Ͽ��ٰ� ���� �Է�*/
	input_scores_file(infile, score, n);
	fclose(infile);

	/*���� ���*/
	max = max_score(score, n);
	min = min_score(score, n);
	sum = sum_score(score, n);
	mean = sum / (float)n;

	/*���*/
	print_scores(score, n);

	/*���� ���*/
	print_result(max, min, sum, mean);

	outfile = (FILE *)fopen("result.txt", "w");
	if (outfile == NULL)
	{
		printf("����!!!");
		return;
	}
	save_result_file(outfile, max, min, sum, mean);
	fclose(outfile);
}