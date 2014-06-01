#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma warning(disable:4996)

// 문자 가운데 정렬
void alignCenter(char txt[])
{
	int i;
	int size = (strlen(WIDTH) - strlen(txt)) / 2;
	for (i = 0; i < size; i++)
	{
		printf(" ");
	}
	printf("%s", txt);
}

// 색상 글자 출력
void textColor(char txt[],int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | color);
	printf("%s", txt);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 8);
}

// 텍스트 문서에서 데이터 로드
void roadData(FILE *fp, Tree *LBT, Member *curNode)
{
	char buff[1024];
	int i = 0;
	char *id, *name, *addr, *phone;


	while (fgets(buff, sizeof(buff), fp))
	{
		buff[strlen(buff) - 1] = '\0';	// 버퍼의 마지막 개행을 공백문자로 바꿈

		// 데이터 파일의 첫 행(열머리) 제외
		if (i == 0){
			i++;
			continue;
		}

		// 버퍼의 문자열을 탭으로 나누어 데이터에 저장
		id = strtok(buff, "\t");
		name = strtok(NULL, "\t");
		addr = strtok(NULL, "\t");
		phone = strtok(NULL, "\t");
		printf("%s %s %s %s\n", id, name, addr, phone);

		// 구조체에 공간 할당, 노드 색상, 부모/자식노드 정보 저장
		curNode = createMember(LBT);

		// 데이터를 구조체에 저장
		curNode->id = atoi(id);
		strcpy(curNode->name, name);
		strcpy(curNode->addr, addr);
		strcpy(curNode->phone, phone);

		// 구조체를 트리에 삽입
		insertNode(LBT, curNode);
		treeFixUp(LBT, curNode);
	}

	return;
}


// 메뉴1 : 회원보기
void menu1_member_view(Tree *tree)
{
	int input;
	system("cls");

	alignCenter("1. 회원 목록\n");
	printf(WIDTH);
	printf("아이디\t\t 이름\t\t\t주소\t\t\t  휴대전화\n");
	printf(WIDTH);

	printTree(tree, tree->root);
	
	printf(WIDTH);
	printf("\n");
	alignCenter("MENU\n");
	alignCenter("0. 종료\n");

	alignCenter("버튼을 입력하세요 : ");
	scanf("%d", &input);
	switch (input)
	{
	case 0:
		return;
	}

	return;
}

// 메뉴2 : 회원추가
void menu2_member_add(Tree *tree)
{
	int id;
	char buff[256];
	char name[10], addr[256], phone[15];
	Member *newNode;
	Member *idIsValid;
	int phoneIsValid,addrIsValid;
	int i = 0, j, m, n;

	// ID
	do{
		printf("\n");
		printf("\t\t\t1. ID (* 6자리의 숫자를 입력하세요)\n");
		printf("\t\t\t  : ");
		scanf("%d",&id);
		idIsValid = searchValue(tree, tree->root, id);

		if (id > 200000 || id < 130000)	textColor("\t\t\t* 오류 : 130000~200000 까지의 숫자만 입력 가능합니다.\n",12);
		
		if (idIsValid != NULL)	textColor("\t\t\t* 오류 : 중복되는 아이디가 존재합니다.\n",12);

	}while (id > 200000 || id < 130000 || idIsValid != NULL);


	// name
	printf("\n");
	printf("\t\t\t2. 이름\n");;
	printf("\t\t\t  : ");
	scanf_s("%s", &name, 10);


	// address
	do{
		addrIsValid = 0;
		printf("\n");
		printf("\t\t\t3. 주소\n");;
		printf("\t\t\t  : ");
		fflush(stdin);
		strcpy(addr, gets_s(buff, 256));

		while (addr[i] != '\0')
		{
			if (addr[i] != ' ')
			{
				addrIsValid = 1;
				break;
			}
			i++;
		}

		if (!addrIsValid) textColor("\t\t\t* 오류 : 주소를 입력하세요.\n", 12);
	} while (!addrIsValid);


	// phone number
	do{
		phoneIsValid = 1;
		printf("\n");
		printf("\t\t\t4. 전화번호(* 000-0000-0000 형식으로 입력하세요)\n");;
		printf("\t\t\t  : ");
		scanf_s("%s", &phone, 15);
		
		n = 0;
		m = 0;
		j = 0;
		while (phoneIsValid == 1 && phone[j] != '\0')
		{
			if (phone[j] == '-')
			{
				n++;
				if (m == 0)
				{
					phoneIsValid = 0;
					break;
				}
				m = 0;
			}
			else if (phone[j] < 48 || phone[j] > 57)
			{
				phoneIsValid = 0;
				break;
			}
			else
			{
				m++;
			}
			j++;
		}
		if (n > 2) phoneIsValid = 0;
		
		if (!phoneIsValid)	textColor("\t\t\t* 오류 : 형식이 올바르지 않습니다.\n", 12);
		
	} while (!phoneIsValid);

	// 구조체에 공간 할당, 노드 색상, 부모/자식노드 정보 저장
	newNode = createMember(tree);

	// 데이터를 구조체에 저장
	newNode->id = id;
	strcpy(newNode->name, name);
	strcpy(newNode->addr, addr);
	strcpy(newNode->phone, phone);

	// 구조체를 트리에 삽입
	insertNode(tree, newNode);
	treeFixUp(tree, newNode);

	return;
}
