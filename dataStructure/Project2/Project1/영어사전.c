// ���� Ž�� Ʈ���� ����� ���� ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE	 100
#define MAX_MEANING_SIZE 200

// ������ ����
typedef struct {
	char word[MAX_WORD_SIZE];		// Ű�ʵ�
	char meaning[MAX_MEANING_SIZE];
} element;
// ����� ����
typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
} TreeNode;

// ���� e1 > e2 -> -1 ��ȯ
// ���� e1 == e2 -> 0  ��ȯ 
// ���� e1 < e2 -> 1 ��ȯ
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}
// ���� Ž�� Ʈ�� ��� �Լ�
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
// ���� Ž�� Ʈ�� Ž�� �Լ�

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
	return p; 	// Ž���� �������� ��� NULL ��ȯ
}
// key�� ���� Ž�� Ʈ�� root�� �����Ѵ�. 
// key�� �̹� root�ȿ� ������ ���Ե��� �ʴ´�.
void insert_node(TreeNode **root, element key)
{
	TreeNode *p, *t; // p�� �θ� ���, t�� �ڽ� ��� 
	TreeNode *n;	 // n�� ���ο� ���

	t = *root;
	p = NULL;
	// Ž���� ���� ���� 
	while (t != NULL) {
		if (compare(key, t->key) == 0) return;
		p = t;
		if (compare(key, t->key)<0) t = t->left;
		else t = t->right;
	}
	// item�� Ʈ�� �ȿ� �����Ƿ� ���� ����
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	// ������ ����
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

	// �θ� ���� ��ũ ����
	/*�ڵ� �ۼ�*/
	/*�θ� ��尡 ���� ��
	/*compare(element e1, element e2)
	/*�θ� ��尡 ���� ��*/
}
// ���� �Լ�
void delete_node(TreeNode **root, element key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;

	// key�� ���� ��� t�� Ž��, p�� t�� �θ���
	p = NULL;
	t = *root;
	while (t != NULL && compare(t->key, key) != 0) {
		p = t;
		t = (compare(key, t->key)<0) ? t->left : t->right;
	}
	if (t == NULL) { 	// Ž��Ʈ���� ���� Ű
		printf("key is not in the tree");
		return;
	}
	// �ܸ������ ���
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t)
				p->left = NULL;
			else   p->right = NULL;
		}
		else					// �θ��尡 ������ ��Ʈ
			*root = NULL;
	}
	// �ϳ��� �ڽĸ� ������ ���
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)	// �θ��带 �ڽĳ��� ���� 
				p->left = child;
			else p->right = child;
		}
		else
			*root = child;
	}
	else {		// �ΰ��� �ڽ��� ������ ���
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
		printf("���� ���� ����\n");
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
		printf("���� ���� ����\n");
		return;
	}
	while (1) {
		printf("�ܾ� �Է�:");
		gets(e.word);
		if (strcmp(e.word, "q") == 0)
			break;
		printf("�ǹ� �Է�:");
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
	printf("i: �Է�\n");
	printf("d: ����\n");
	printf("s: Ž��\n");
	printf("p: ���\n");
	printf("o: ���� ����\n");
	printf("v: ���� ����\n");
	printf("q: ����\n");
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
			printf("�ܾ� �Է�:");
			gets(e.word);
			printf("�ǹ� �Է�:");
			gets(e.meaning);
			insert_node(&root, e);
			break;
		case 'd':
			printf("������ �ܾ�:");
			gets(e.word);
			delete_node(&root, e);
			break;
		case 's':
			printf("ã�� �ܾ�:");
			gets(e.word);
			tmp = search(root, e);
			if (tmp != NULL) {
				printf("�ǹ�: %s\n", e.meaning);
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
