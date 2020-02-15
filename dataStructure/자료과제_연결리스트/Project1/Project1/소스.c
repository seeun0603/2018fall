#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_CHAR_PER_LINE 1000
#define MAX_NAME 256
#define FALSE 0
#define True 1
void warning(char *);
void error(char *);

typedef struct {
	char a[MAX_CHAR_PER_LINE];
}element;

typedef struct ListNode {
	element data;
	struct ListNode *link;
}ListNode;

typedef struct {
	ListNode *head; //��� ������
	int length; //����� ����
}ListType;

void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL)//����ִ� ����Ʈ
	{
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL)//ù��° ���� ����
	{
		new_node->link = *phead;
		*phead = new_node;
	}
	else
	{
		new_node->link = p->link;
		p->link = new_node;
	}
}

void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
	if (p == NULL)
		*phead = (*phead)->link; //������ ��尡 ����
	else
		p->link = removed->link;
	free(removed);
}

void init(ListType *list)//buffer �ʱ�ȭ
{
	if (list == NULL) return;
	list->length = 0;
	list->head = NULL;
}

ListNode *get_node_at(ListType *list, int pos)//����� ��ġ�� ��ȯ
{
	int i;
	ListNode *tmp_node = list->head;
	if (pos < 0) return NULL;
	for (i = 0; i < pos; i++)
		tmp_node = tmp_node->link;
	return tmp_node;
}

int get_length(ListType *list)
{
	return list->length;
}

void add(ListType *list, int position, element data)
{
	ListNode *p;
	if ((position >= 0) && (position <= list->length))
	{
		ListNode *node = (ListNode *)malloc(sizeof(ListNode));
		if (node == NULL) error("�޸� �Ҵ� ����");
		node->data = data;
		p = get_node_at(list, position - 1);
		insert_node(&(list->head), p, node);
		list->length++;
	}
}

void add_last(ListType *list, element data)
{
	add(list, get_length(list), data);
}

void add_first(ListType *list, element data)
{
	add(list, 0, data);
}

int is_empty(ListType *list)
{
	if (list->head == NULL) return 1;//���� ��尡 ����
	else return 0;
}

void delete(ListType *list, int pos)
{
	if (!is_empty(list) && (pos >= 0) && (pos < list->length))//list�� ���� x, �ڸ��� list������ ���� ������
	{
		ListNode *p = get_node_at(list, pos - 1);
		remove_node(&(list->head), p, (p != NULL) ? p->link : NULL);
		list->length--;
	}
}

element get_entry(ListType *list, int pos)//����� ��ġ�� ã�� �� �� ����� ������ ���� ��ȯ�Ѵ�.
{
	ListNode *p;
	if (pos >= list->length)
		error("��ġ ����");
	p = get_node_at(list, pos);
	return p->data;
}

void clear(ListType *list)
{
	int i;
	for (i = 0; i < list->length; i++)
		delete(list, i);
}

void display(ListType *buffer)
{
	int i;
	ListNode *tmp_node;
	tmp_node = buffer->head;

	printf("**************\n");
	for (i = 0; i < buffer->length; i++)
	{
		printf("%s", (tmp_node->data).a);
		tmp_node = tmp_node->link;
	}
	printf("**************\n");
}

void warning(char *message)
{
	fprintf(stderr, "%s\n", message);
}

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void help()
{
	printf("**************\n");
	printf("i : �Է�\n");
	printf("d : ����\n");
	printf("f : ã��\n");
	printf("v : �Ųٷ�\n");
	printf("c : �ٲٱ�\n");
	printf("r : �����б�\n");
	printf("w : ���Ͼ���\n");
	printf("q : ����\n");
	printf("**************\n");
}

ListNode *reverse_line(ListNode *head)
{
	ListNode *p, *q = NULL, *r;
	p = head;

	while (p != NULL)
	{
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}

	return q;
}

void change_line(ListType *buffer)
{
	char name[MAX_NAME];
	int line;

	printf("�ٲٴ� ������ �Է�>>");
	scanf("%d", &line);

	printf("�ٲٴ� ���� �Է�>>");
	rewind(stdin);
	fgets(name, MAX_NAME, stdin);

	strcpy((get_node_at(buffer, line)->data).a, name);
	display(buffer);
}

void find_line(ListType *buffer)
{
	char name[MAX_NAME];
	ListNode *p;
	p = buffer->head;

	printf("ã�� ���ڿ��� �Է�>>");
	scanf("%s", name);

	for (int i = 0; i < buffer->length; i++)
	{
		if (strstr((get_node_at(buffer, i)->data).a, name) != NULL)
			printf("%d��°\n", i);
		p = p->link;
	}
}

void read_file(ListType *buffer)
{
	char fname[MAX_NAME];
	FILE *fd;
	element p;

	if (!is_empty(buffer)) {
		clear(buffer);
	}
	init(buffer);

	printf("���� �̸�: ");
	scanf("%s", fname); //�����̸��� Ȯ���ڱ��� ���ش�.
	if ((fd = fopen(fname, "r")) == NULL)
	{
		error("������ �� �� �����ϴ�.");
		return;
	}
	while (fgets(p.a, MAX_CHAR_PER_LINE, fd))
	{
		add_last(buffer, p);
	}
	fclose(fd);
	display(buffer);
}

void write_file(ListType *buffer)
{
	FILE *fd;
	char fname[MAX_NAME];
	element p;
	int i;

	printf("�����̸�");
	scanf("%s", fname);  //Ȯ���� ���� ���ش�. fname.txt
	if ((fd = fopen(fname, "w")) == NULL)
	{

		printf("������ �� �� �����ϴ�.\n");
		return;
	}
	for (i = 0; i < get_length(buffer); i++)
	{
		p = get_entry(buffer, i);
		fputs(p.a, fd);

	}
	fclose(fd);
	display(buffer);
}

void delete_line(ListType *buffer)
{
	int position;

	if (is_empty(buffer))
		printf("���� ������ �����ϴ�.\n");
	else
	{
		printf("���� ���� �Է�:");
		scanf("%d", &position);
		delete(buffer, position);
	}
	display(buffer);
}

void insert_line(ListType *buffer)
{
	int position;
	char line[MAX_CHAR_PER_LINE];
	element p;

	printf("�Է��� ��ȣ�� �Է��ϼ���:");
	scanf("%d", &position);
	rewind(stdin);
	printf("������ �Է��ϼ���:");
	fgets(line, MAX_CHAR_PER_LINE, stdin);
	//gets(line);

	strcpy(p.a, line);
	add(buffer, position, p);

	display(buffer);
}

void do_command(ListType *buffer, char command)
{
	switch (command)
	{
	case 'i':
		insert_line(buffer);
		break;
	case 'd':
		delete_line(buffer);
		break;
	case 'r':
		read_file(buffer);
		break;
	case 'w':
		write_file(buffer);
		break;
	case 'c':
		change_line(buffer);
		break;
	case 'v':
		(*buffer).head = reverse_line((*buffer).head);
		display(buffer);
		break;
	case 'f':
		find_line(buffer);
		break;
	case 'q':
		break;
	default:
		printf("�߸� �Է��߽��ϴ�.\n");
		break;
	}
}

void main() {
	char command;
	ListType buffer;

	init(&buffer);
	do {
		help();
		printf("�޴��� ����>>");
		command = getchar();
		do_command(&buffer, command);
		rewind(stdin);
	} while (command != 'q');
}