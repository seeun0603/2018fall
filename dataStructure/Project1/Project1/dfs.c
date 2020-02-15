#include<stdio.h>
#define MAX_VERTICES 50
#define True 1
#define False 0
int visit[MAX_VERTICES];
int parent[MAX_VERTICES];

typedef struct GraphType
{
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

//그래프 초기화
void graph_init(GraphType *g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++) {
			g->adj_mat[r][c] = 0;
		}
	}
}

//정점 삽입 연산
void insert_vertex(GraphType *g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

//간선 삽입 연산
void insert_edge(GraphType *g, int start, int end)
{
	if (start >= g->n || end >= g->n)
	{
		fprintf(stderr, "그래피: 정점의 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

//깊이 우선 탐색 프로그램
void dfs_mat(GraphType *g, int start, int goal)
{
	int w;
	visit[start] = True;
	printf("%d ", start);

	if (start == goal)
		return;

	for (w = 0; w < g->n; w++)
	{
		if (g->adj_mat[start][w] && !visit[w]) {
			parent[start] = True;
			dfs_mat(g, w, goal);
		}
		if (parent[start] == True)
			return;
	}
}

void main()
{
	int i,start,goal;
	GraphType g;

	graph_init(&g);

	for (i = 0; i < 9; i++)
		insert_vertex(&g, i);
	insert_edge(&g, 0, 4);
	insert_edge(&g, 0, 5);
	insert_edge(&g, 0, 3);
	insert_edge(&g, 1, 4);
	insert_edge(&g, 1, 7);
	insert_edge(&g, 2, 4);
	insert_edge(&g, 2, 5);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 2, 8);
	insert_edge(&g, 3, 6);
	insert_edge(&g, 4, 5);
	insert_edge(&g, 5, 6);
	insert_edge(&g, 6, 7);
	insert_edge(&g, 6, 8);
	printf("출발점과 도착점 입력>>");
	scanf("%d %d", &start, &goal);
	dfs_mat(&g, start, goal );
}