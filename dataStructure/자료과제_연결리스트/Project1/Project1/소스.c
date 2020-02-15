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
	ListNode *head; //헤드 포인터
	int length; //노드의 개수
}ListType;

void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL)//비어있는 리스트
	{
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL)//첫번째 노드로 삽입
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
		*phead = (*phead)->link; //제거할 노드가 없음
	else
		p->link = removed->link;
	free(removed);
}

void init(ListType *list)//buffer 초기화
{
	if (list == NULL) return;
	list->length = 0;
	list->head = NULL;
}

ListNode *get_node_at(ListType *list, int pos)//노드의 위치를 반환
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
		if (node == NULL) error("메모리 할당 오류");
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
	if (list->head == NULL) return 1;//지울 노드가 없음
	else return 0;
}

void delete(ListType *list, int pos)
{
	if (!is_empty(list) && (pos >= 0) && (pos < list->length))//list가 공백 x, 자리도 list범위를 넘지 않을때
	{
		ListNode *p = get_node_at(list, pos - 1);
		remove_node(&(list->head), p, (p != NULL) ? p->link : NULL);
		list->length--;
	}
}

element get_entry(ListType *list, int pos)//노드의 위치를 찾은 후 그 노드의 데이터 값을 반환한다.
{
	ListNode *p;
	if (pos >= list->length)
		error("위치 오류");
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
	printf("i : 입력\n");
	printf("d : 삭제\n");
	printf("f : 찾기\n");
	printf("v : 거꾸로\n");
	printf("c : 바꾸기\n");
	printf("r : 파일읽기\n");
	printf("w : 파일쓰기\n");
	printf("q : 종료\n");
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

	printf("바꾸는 라인을 입력>>");
	scanf("%d", &line);

	printf("바꾸는 내용 입력>>");
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

	printf("찾을 문자열을 입력>>");
	scanf("%s", name);

	for (int i = 0; i < buffer->length; i++)
	{
		if (strstr((get_node_at(buffer, i)->data).a, name) != NULL)
			printf("%d번째\n", i);
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

	printf("파일 이름: ");
	scanf("%s", fname); //파일이름과 확장자까지 써준다.
	if ((fd = fopen(fname, "r")) == NULL)
	{
		error("파일을 열 수 없습니다.");
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

	printf("파일이름");
	scanf("%s", fname);  //확장자 까지 써준다. fname.txt
	if ((fd = fopen(fname, "w")) == NULL)
	{

		printf("파일을 열 수 없습니다.\n");
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
		printf("지울 라인이 없습니다.\n");
	else
	{
		printf("지울 라인 입력:");
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

	printf("입력행 번호를 입력하세요:");
	scanf("%d", &position);
	rewind(stdin);
	printf("내용을 입력하세요:");
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
		printf("잘못 입력했습니다.\n");
		break;
	}
}

void main() {
	char command;
	ListType buffer;

	init(&buffer);
	do {
		help();
		printf("메뉴를 선택>>");
		command = getchar();
		do_command(&buffer, command);
		rewind(stdin);
	} while (command != 'q');
}