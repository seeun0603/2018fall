#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CHAR_SIZE 10

int LOCCTR; //location counter로 주소를 파악하기 위한 변수
int errorFlag = 0; //에러를 찾기 위한 변수
int symtbCounter = 0;  //symbol table에서 위치를 찾기 위한 변수
int optbCounter = 26; //opcode table에서 위치를 찾기 위한 변수 
int startAddress; // 시작 주소를 저장하는 변수
int programLength; //프로그램의 길이를 저장하기 위한 변수
int count = 0; //파일을 한줄씩 읽어 저장하기 위한 변수

typedef struct OperationCodeObjectProgram {   // optable의 구조체
	char Mnemonic[MAX_CHAR_SIZE];   // 명령어
	unsigned short int  ManchineCode;   // 해당 명령어의 목적 코드
}SIC_OPTAB;

static SIC_OPTAB OPTAB[] = //obtable은 미리 정의되어 있어야하므로 static으로 구현 
{
{ "ADD", 0x18 },
{ "AND", 0x40 },
{ "COMP", 0x28 },
{ "DIV", 0x24 },
{ "J", 0x3C },
{ "JEQ", 0x30 },
{ "JGT", 0x34 },
{ "JLT", 0x38 },
{ "JSUB", 0x48 },
{ "LDA", 0x00 },
{ "LDCH", 0x50 },
{ "LDL", 0x08 },
{ "LDX", 0x04 },
{ "MUL", 0x20 },
{ "OR", 0x44 },
{ "RD", 0xD8 },
{ "RSUB", 0x4F },
{ "STA", 0x0C },
{ "STCH", 0x54 },
{ "STL", 0x14 },
{ "STSW", 0xE8 },
{ "STX", 0x10 },
{ "SUB", 0x1C },
{ "TD", 0xE0 },
{ "TIX", 0x2C },
{ "WD", 0xDC }
};

struct SIC_SYMTAB { //symtable의 구조체
	char Label[10]; //lable 이름을 저장하는 변수
	int Label_Address; //lable의 주소를 저장하는 변수
}SYMTAB[100];

struct ObjectProgram { // 목적 코드를 만들기 위해 파일에서 읽은 것을 저장하는 곳
	int Loc; //그 상태의 위치를 나타내는 변수
	char label[10]; //레이블 저장
	char opcode[10]; //opcode 저장
	char operand[10]; //operand 저장
	char address[10]; // object code를 저장 
}ObjectProgram[100];

int findOpcode(int i) { //읽은 opcode가 optable에 있는 지를 확인해서 opcode를 찾는 함수
	for (int j = 0; j < optbCounter; j++) {
		if (strcmp(ObjectProgram[i].opcode, OPTAB[j].Mnemonic) == 0)
			return j;
	}
	return 0;
}

int findSym(int i) { //읽은 operand가 symbol table에 있는 지 찾는다. 
	for (int j = 0; j < symtbCounter; j++) {
		if (strcmp(ObjectProgram[i].operand, SYMTAB[j].Label) == 0)
			return j;
	}
	printf("심볼테이블이 발견되지않음");
	return 0;
}

/* * * * * PASS 1 * * * * */
int Pass_1() { //PASS_1 과정 


	char *token;
	char buffer[100];
	int a = 0;
	FILE *f = fopen("input.txt", "r");//assembler코드가 기록된 input 파일 열기
	if (f == NULL) { //파일 열기 에러
		fprintf(stderr, "FILE OPEN ERROR\n");
		return 0;
	}
	char seps[] = " \n"; // 토큰분리자 
	char temp_1[10];//토큰으로 자른 변수 임시로 저장하는 곳
	char temp_2[10];
	char temp_3[10];

	while (fgets(buffer, 100, f) != NULL) { //파일에서 한줄씩 가져온다.

		token = strtok(buffer, seps); //토큰으로 잘라 하나씩 가져온다. 
		while (token != NULL) {
			switch (a) {
			case 0: // 0일때 레이블을 읽음
				strcpy(temp_1, token);
				break;
			case 1: // 1일때 명령어 읽음
				strcpy(temp_2, token);
				break;
			case 2: //2일때 오퍼랜드 읽음
				strcpy(temp_3, token);
				break;
			default:
				break;
			}
			a++;
			token = strtok(NULL, seps);
		}
		switch (a) {
		case 2: //오피코드와 오퍼랜드밖에 없는경우
			strcpy(ObjectProgram[count].opcode, temp_1);
			strcpy(ObjectProgram[count].operand, temp_2);
			break;
		case 3: //라벨과 오피코드 그리고 오퍼랜드가 있는경우
			strcpy(ObjectProgram[count].label, temp_1);
			strcpy(ObjectProgram[count].opcode, temp_2);
			strcpy(ObjectProgram[count].operand, temp_3);
			break;
		default:
			break;
		}
		a = 0;
		count++;
	}

	if (strcmp(ObjectProgram[0].opcode, "START") == 0) { //opcode를 통해 start를 찾아서 operand에서 첫 시작 주소를 알아낸다.
		LOCCTR = strtol(ObjectProgram[0].operand, NULL, 16); // 찾은 operand를 16진수로 변경한다.  
	}
	else {
		LOCCTR = 0x00; //start가 아니면 location counter를 바꾼다. 
	}

	startAddress = LOCCTR; //시작주소 지정
	ObjectProgram[0].Loc = LOCCTR; 
	printf("=================================\n");
	printf("LOC\tLABEL\tOPCODE\t  OPERAND\n");
	printf("=================================\n");
	printf("%4.X %8s %8s %10s \n", ObjectProgram[0].Loc, ObjectProgram[0].label, ObjectProgram[0].opcode, ObjectProgram[0].operand);
	//시작하는 위치, 레이블, opcode, operand를 출력한다. 

	for (int i = 1; i < count && strcmp(ObjectProgram[i].opcode, "END") != 0; i++) {
		if (strlen(ObjectProgram[i].label) != 0) { //label이 존재하는 경우
			for (int j = 0; j < symtbCounter; j++) {
				if (strcmp(ObjectProgram[i].opcode, SYMTAB[j].Label) == 0)
					errorFlag = 1; //lable이 중복되면 error flag를 1로 설정
			}

			if (errorFlag == 1) //error flag가 1로 설정되어 있으면 중복 symbol존재 
				printf("중복된 symbol이 존재한다.");
			else { //중복이 존재하지않으면 새로운 lable을 symtable에 저장 
				strcpy(SYMTAB[symtbCounter].Label, ObjectProgram[i].label);
				SYMTAB[symtbCounter].Label_Address = LOCCTR;
				symtbCounter++;
			}
		}

		ObjectProgram[i].Loc = LOCCTR; //현재 위치를 objectprogram에 저장한다.

		if (findOpcode(i)) {
			LOCCTR += 3; //opcode 찾았을때 location counter를 3씩 증가시킨다. 
		}
		else if (strcmp(ObjectProgram[i].opcode, "WORD") == 0) {
			LOCCTR += 3;
		}
		else if (strcmp(ObjectProgram[i].opcode, "RESW") == 0) {
			LOCCTR += (3 * atoi(ObjectProgram[i].operand)); 
		}
		else if (strcmp(ObjectProgram[i].opcode, "RESB") == 0) {
			LOCCTR += atoi(ObjectProgram[i].operand);
		}
		else if (strcmp(ObjectProgram[i].opcode, "BYTE") == 0) {
			LOCCTR += strlen(ObjectProgram[i].operand);
		}
		else { //operation을 발견 못했을 경우 에러 메시지 출력
			printf("Invalid Operation Code!\n");
		}
		printf("%4.X %8s %8s %10s \n", ObjectProgram[i].Loc, ObjectProgram[i].label, ObjectProgram[i].opcode, ObjectProgram[i].operand);
		//objectprogram 출력
	}
	printf("%4.X %8s %8s %10s \n", ObjectProgram[count - 1].Loc, ObjectProgram[count - 1].label, ObjectProgram[count - 1].opcode, ObjectProgram[count - 1].operand); 
	//프로그램의 끝을 나타내는 부분
	printf("=================================\n");
	programLength = LOCCTR - startAddress; //프로그램 계산하는 부분
	printf("프로그램 길이: %X\n", programLength);
	printf("====SYMBOL ObjectProgram====\n");
	for (int i = 0; i < symtbCounter; i++) { //symbol table 출력
		printf("%s\t%.X\n", SYMTAB[i].Label, SYMTAB[i].Label_Address);
	}
	printf("====================\n");
}

/* * * * * PASS 2 * * * * */
void Pass_2() {
	int a, b;
	int n = 10;
	int num = 11; // 1E씩 10개로 끊어서 텍스트레코드에 기록하기위한 초기화 변수
	FILE *ff;
	char filename[] = "output.txt"; // 목적코드 txt파일로 생성

	ff = fopen(filename, "w");
	if (strcmp(ObjectProgram[0].opcode, "START") == 0) //START RECORD
		fprintf(ff, "H^%s\t^%.6X^%.6X", ObjectProgram[0].label, ObjectProgram[0].Loc, programLength + 1); // 헤드레코드 작성
	int obj_count = count - 2; //지시자를 제외하여 오브젝트 코드의 개수를 정함.

	for (int i = 1; i < count; i++) { //오브젝트 카운트에서 RESW와 RESB의 경우를 지운다.
		if (strcmp(ObjectProgram[i].opcode, "RESW") == 0 || strcmp(ObjectProgram[i].opcode, "RESB") == 0)
			obj_count -= 1;
	}

	for (int i = 1; i <= obj_count; i++) { //텍스트 레코드를 1E개의 단위로 잘라서 기록하는 과정
		if (i == 1) {
			if (obj_count <= n) { //목적 코드에 10개를 출력하는 부분 
				fprintf(ff, "\n");
				fprintf(ff, "T^%.6X^%.2X", ObjectProgram[i].Loc, ObjectProgram[obj_count + 1].Loc - ObjectProgram[0].Loc);   //TEXT RECORD
			}
			else {
				fprintf(ff, "\n");
				fprintf(ff, "T^%.6X^%.2X", ObjectProgram[i].Loc, ObjectProgram[n + 1].Loc - ObjectProgram[0].Loc);   //TEXT RECORD
			}

		}
		if (i % num == 0) { // 목적코드에서 줄을 나누어서 출력하는 부분
			if (obj_count - i <= n) {
				fprintf(ff, "\n");
				fprintf(ff, "T^%.6X^%.2X", ObjectProgram[i].Loc, ObjectProgram[obj_count + 2 - i].Loc - ObjectProgram[0].Loc);
			}
			else {
				fprintf(ff, "\n");
				fprintf(ff, "T^%.6X^%.2X", ObjectProgram[i].Loc, ObjectProgram[n + 1].Loc - ObjectProgram[0].Loc);
			}
			num += 10;
		}

		if (b = findOpcode(i)) { // search OPTAB FOR OPCODE
			if (a = findSym(i)) { //오퍼랜드에 심볼이있는지 확인
				char temp1[10]; //명령어 코드와 오퍼랜드 주소의 코드를 붙여서 출력하기 위한 임시 변수
				char temp2[10];
				sprintf(temp1, "%.2X", OPTAB[b].ManchineCode);// 임시변수에 명령어 코드 저장
				sprintf(temp2, "%X", SYMTAB[a].Label_Address);// 임시변수에 오퍼랜드 주소 저장
				strcpy(ObjectProgram[i].address, temp1);
				strcat(ObjectProgram[i].address, temp2);
				fprintf(ff, "^%s", ObjectProgram[i].address); // 목적코드(명령어코드 + 오퍼랜드 주소) 출력
			}

			else { //정의되지않은 심볼 일경우 출력
				printf("ERROR UNDEFINED SYMBOL\n");
			}
		}
		else if (strcmp(ObjectProgram[i].opcode, "BYTE") == 0) { //오피코드가 BYTE라면 문자열을 16진수로 바꾼다.
			for (int j = 0; j < strlen(ObjectProgram[i].opcode) - 1; j++) {
				char buf[10];
				sprintf(buf, "%X", ObjectProgram[i].operand[j]);
				strcat(ObjectProgram[i].address, buf);
			}
			fprintf(ff, "^%s", ObjectProgram[i].address);
		}
		else if (strcmp(ObjectProgram[i].opcode, "WORD") == 0) { //오피코드가 WORD라면 정수그대로 16진수로 기록한다.
			sprintf(ObjectProgram[i].address, "%.6X", atoi(ObjectProgram[i].operand));
			fprintf(ff, "^%s", ObjectProgram[i].address);
		}
	}

	fprintf(ff, "\nE^%.6X\n", ObjectProgram[1].Loc); //END RECORD를 쓰는 부분
}

/* * * * * MAIN * * * * */
int main() {

	Pass_1(); //PASS1 호출
	Pass_2(); //PASS2 호출
}
