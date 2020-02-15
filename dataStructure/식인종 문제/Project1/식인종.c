#include <stdio.h>
typedef struct{
	int can[2];
	int mis[2];
}MACState;

/*
	can mis => cm //선교사 한명 식인종 한명
	can can => c2 // 식인종 두명
	mis mis => m2 // 선교사 두명
	can => c // 식인종 한명
	mis => m // 선교사 한명
*/

int safety_check(MACState state)
{
	int i = 0;
	if (state.mis[i] == 0 || state.can[i] == 0 || state.mis[i] >= state.can[i]) {
		if (state.mis[i + 1] == 0 || state.can[i + 1] == 0 || state.mis[i + 1] >= state.can[i + 1])
			return 1;
	}
	else
		return 0;
}

int goal_check(MACState state)
{
	if (state.can[1] == 3 && state.mis[1] == 3)
		return 1;
	else
		return 0;
}

MACState find_solution(MACState anystate1, MACState goal)
{
	int c;
	int i;
	int answer;

	while (1)
	{
		for (int i = 0; i < 2; i++)//왔다갔다를 반복
		{
			printf("누구 이동(1.cc, 2.cm ,3.c 4.m, 5.mm)>>");
			scanf("%d", &c);

			switch (c)
			{
			case 1:
				anystate1.can[i] -= 2;
				anystate1.can[1 - i] += 2;
				break;
			case 2:
				if((anystate1.can[i] && anystate1.can[1 - i]) < 2)
				anystate1.can[i] -= 1;
				anystate1.mis[i] -= 1;
				anystate1.can[1 - i] += 1;
				anystate1.mis[1 - i] += 1;
				break;
			case 3:
				anystate1.can[i] -= 1;
				anystate1.can[1 - i] += 1;
				break;
			case 4:
				anystate1.mis[i] -= 1;
				anystate1.mis[1 - i] += 1;
				break;
			case 5:
				anystate1.mis[i] -= 2;
				anystate1.mis[1 - i] += 2;
				break;
			}
			
			answer = safety_check(anystate1);
			if (answer == 0) 
			{
				i--;
				continue;
			}

			for (int i = 0; i < 2; i++)
			{
				printf("anysate %d에서 식인종 수: %d, 선교사 수: %d ", i + 1, anystate1.can[i], anystate1.mis[i]);
			}
			printf("\n");

			answer = goal_check(anystate1);
			if (answer == 1)
				return anystate1;
		}
	}
}

int main()
{
	MACState goal = { { 0,3 },{ 0,3 } };
	MACState anystate1 = { { 3,0 },{ 3,0 } };//이동 전 상태
	MACState solution;

	solution = find_solution(anystate1, goal);
}
