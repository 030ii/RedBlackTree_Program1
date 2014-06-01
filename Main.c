#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma warning(disable:4996)

int main(void)
{
	FILE *fp;
	Tree *LBT = NULL;
	Member *curNode = NULL;
	int input;

	system("color F8");

	fp = fopen("data.txt", "r");

	if (fp == NULL)	// 데이터 읽기 실패시
	{
		printf("데이터 로드에 실패했습니다!");
		return -1;
	}

	LBT = createLBT();
	roadData(fp, LBT, curNode);
	
	while (1)
	{
		system("cls");

		alignCenter("시작 화면\n");
		printf("\n");
		alignCenter("───────MENU───────\n");
		alignCenter("1. 회원 목록\n");
		alignCenter("2. 회원 추가\n");
		alignCenter("3. 파일 저장\n");
		alignCenter("0. 종     료\n");
		alignCenter("────────────────\n");
		printf("\n");

		alignCenter("버튼을 입력하세요 : ");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			menu1_member_view(LBT);
			break;
		case 2:
			menu2_member_add(LBT);
			break;
		case 0:
			return 0;
		}
	}
	
	return 0;
}