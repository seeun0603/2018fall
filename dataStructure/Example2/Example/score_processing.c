#include <stdio.h>
void main()
{
	int c, n;
	float score[30];
	float max, min, sum = 0, mean = 0;

	// �л� �� �Է�
	printf("�л���? ");
	scanf("%d", &n);

	// ���� �Է�
	printf("\n\n");
	printf("������ �Է��ϼ���.\n");
	for (c = 0; c<n; c++)
	{
		scanf("%f", &score[c]);
	}

	// �ְ����� ���
	max = score[0];
	for (int i = 1; i < n; i++)
	{
		if (score[i] > max)
			max = score[i];
	}

	// �������� ���
	min = score[0];
	for (int i = 1; i < n; i++)
	{
		if (score[i] < min)
			min = score[i];
	}

	// �հ����� ���
	for (int i = 0; i < n; i++)
		sum += score[i];

	// ������� ���
	mean = sum / n;

	/* ���� ��� */
	printf("**************************\n");
	printf("�ְ�����: %f\n", max);
	printf("��������: %f\n", min);
	printf("�հ�����: %f\n", sum);
	printf("�������: %f\n", mean);
	printf("**************************\n");
}