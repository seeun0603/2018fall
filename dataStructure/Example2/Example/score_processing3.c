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

void main()
{
	int n;
	float score[30];
	float max, min, sum, mean;
	FILE *infile, *outfile;

	infile = (FILE *)fopen("score.txt", "r");
	if (infile == NULL)
	{
		printf("에러!!!");
		return;
	}

	/*학생수 입력*/
	printf("학생 수?");
	scanf("%d", &n);

	/*파일에다가 점수 입력*/
	input_scores_file(infile, score, n);
	fclose(infile);

	/*점수 계산*/
	max = max_score(score, n);
	min = min_score(score, n);
	sum = sum_score(score, n);
	mean = sum / (float)n;

	/*출력*/
	print_scores(score, n);

	/*점수 출력*/
	print_result(max, min, sum, mean);

	outfile = (FILE *)fopen("result.txt", "w");
	if (outfile == NULL)
	{
		printf("에러!!!");
		return;
	}
	save_result_file(outfile, max, min, sum, mean);
	fclose(outfile);
}