// 이진 탐색 트리를 사용한 영어 사전

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE	 100
#define MAX_MEANING_SIZE 200

// 데이터 형식
typedef struct {
	char word[MAX_WORD_SIZE];		// 키필드
	char meaning[MAX_MEANING_SIZE];
} element;
// 노드의 구조
typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
} TreeNode;

// 만약 e1 > e2 -> -1 반환
// 만약 e1 == e2 -> 0  반환 
// 만약 e1 < e2 -> 1 반환
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}
// 이진 탐색 트리 출력 함수
void display(TreeNode *p)
{
	if (p != NULL) {
		printf("(");
		display(p->left);
		printf("%s", p->key.word);
		display(p->right);
		printf(")");
	}
}
// 이진 탐색 트리 탐색 함수

void preorder(TreeNode *root, FILE *fp) {
	TreeNode *p = root;
	char str[10];
	element e;
	if (p) {
		e = p->key;
		strcpy(str, e.word);
		fprintf(fp, "%s ", str);
		preorder(p->left, fp);
		preorder(p->right, fp);
	}
}

void inorder(TreeNode *root, FILE *fp) {
	TreeNode *p = root;
	char str[10];
	element e;
	if (p) {
		e = p->key;
		strcpy(str, e.word);
		inorder(p->left, fp);
		fprintf(fp, "%s ", str);
		inorder(p->right, fp);
	}
}

void postorder(TreeNode *root, FILE *fp) {
	TreeNode *p = root;
	char str[10];
	element e;
	if (p) {
		e = p->key;
		strcpy(str, e.word);
		postorder(p->left, fp);
		postorder(p->right, fp);
		fprintf(fp, "%s ", str);
	}
}

TreeNode *search(TreeNode *root, element key)
{
	TreeNode *p = root;
	while (p != NULL) {
		if (compare(key, p->key) == 0)
			return p;
		else if (compare(key, p->key) < 0)
			p = p->left;
		else
			p = p->right;
	}
	return p; 	// 탐색에 실패했을 경우 NULL 반환
}
// key를 이진 탐색 트리 root에 삽입한다. 
// key가 이미 root안에 있으면 삽입되지 않는다.
void insert_node(TreeNode **root, element key)
{
	TreeNode *p, *t; // p는 부모 노드, t는 자식 노드 
	TreeNode *n;	 // n은 새로운 노드

	t = *root;
	p = NULL;
	// 탐색을 먼저 수행 
	while (t != NULL) {
		if (compare(key, t->key) == 0) return;
		p = t;
		if (compare(key, t->key)<0) t = t->left;
		else t = t->right;
	}
	// item이 트리 안에 없으므로 삽입 가능
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	// 데이터 복사
	n->key = key;
	n->left = n->right = NULL;

	if (p != NULL)
	{
		if (compare(key, p->key) < 0)
			p->left = n;
		else
			p->right = n;
	}
	else
		return *root = n;

	// 부모 노드와 링크 연결
	/*코드 작성*/
	/*부모 노드가 있을 때
	/*compare(element e1, element e2)
	/*부모 노드가 없을 때*/
}
// 삭제 함수
void delete_node(TreeNode **root, element key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;

	// key를 갖는 노드 t를 탐색, p는 t의 부모노드
	p = NULL;
	t = *root;
	while (t != NULL && compare(t->key, key) != 0) {
		p = t;
		t = (compare(key, t->key)<0) ? t->left : t->right;
	}
	if (t == NULL) { 	// 탐색트리에 없는 키
		printf("key is not in the tree");
		return;
	}
	// 단말노드인 경우
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t)
				p->left = NULL;
			else   p->right = NULL;
		}
		else					// 부모노드가 없으면 루트
			*root = NULL;
	}
	// 하나의 자식만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)	// 부모노드를 자식노드와 연결 
				p->left = child;
			else p->right = child;
		}
		else
			*root = child;
	}
	else {		// 두개의 자식을 가지는 경우
		succ_p = t;
		succ = t->right;
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}
		if (succ_p->left == succ) succ_p->left = succ->right;
		else succ_p->right = succ->right;
		t->key = succ->key;
		t = succ;
	}
	free(t);
}

void open_node(TreeNode **root)
{
	FILE *fp;
	element p;
	char str[10];
	fp = (FILE *)fopen("Input.txt", "r");
	if (fp == NULL) {
		printf("파일 열기 실패\n");
		return;
	}
	while (1)
	{
		if (fscanf(fp, "%s", str) == EOF)
			break;
		strcpy(p.word, str);
		fscanf(fp, "%s", str);
		strcpy(p.meaning, str);
		insert_node(&root, p);
	}
	display(root);
	fclose(fp);
}

void save_node(TreeNode *root) {
	FILE *fp;
	element e;
	fp = (FILE *)fopen("output.txt", "w");
	if (fp == NULL) {
		printf("파일 열기 실패\n");
		return;
	}
	while (1) {
		printf("단어 입력:");
		gets(e.word);
		if (strcmp(e.word, "q") == 0)
			break;
		printf("의미 입력:");
		gets(e.meaning);
		insert_node(&root, e);
	}
	fprintf(fp, "preorder>> ");
	preorder(root, fp);

	fprintf(fp, "\ninorder>> ");
	inorder(root, fp);

	fprintf(fp, "\npostorder>> ");
	postorder(root, fp);
}

void help()
{
	printf("**************\n");
	printf("i: 입력\n");
	printf("d: 삭제\n");
	printf("s: 탐색\n");
	printf("p: 출력\n");
	printf("o: 파일 열기\n");
	printf("v: 파일 저장\n");
	printf("q: 종료\n");
	printf("**************\n");
}

void main()
{
	char command;
	element e;
	TreeNode *root = NULL;
	TreeNode *tmp;

	do {
		help();
		command = getchar();
		while (getchar() != '\n');

		switch (command) {
		case 'i':
			printf("단어 입력:");
			gets(e.word);
			printf("의미 입력:");
			gets(e.meaning);
			insert_node(&root, e);
			break;
		case 'd':
			printf("삭제할 단어:");
			gets(e.word);
			delete_node(&root, e);
			break;
		case 's':
			printf("찾을 단어:");
			gets(e.word);
			tmp = search(root, e);
			if (tmp != NULL) {
				printf("의미: %s\n", e.meaning);
				break;
			}
		case 'p':
			display(root);
			break;
		case 'o':
			open_node(root);
			break;
		case 'v':
			save_node(root);
			break;
		}
	} while (command != 'q');
}
