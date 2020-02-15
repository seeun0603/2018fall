#include <mylib.h>
#include<stdlib.h>

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