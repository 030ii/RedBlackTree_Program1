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

	if (fp == NULL)	// ������ �б� ���н�
	{
		printf("������ �ε忡 �����߽��ϴ�!");
		return -1;
	}

	LBT = createLBT();
	roadData(fp, LBT, curNode);
	
	while (1)
	{
		system("cls");

		alignCenter("���� ȭ��\n");
		printf("\n");
		alignCenter("��������������MENU��������������\n");
		alignCenter("1. ȸ�� ���\n");
		alignCenter("2. ȸ�� �߰�\n");
		alignCenter("3. ���� ����\n");
		alignCenter("0. ��     ��\n");
		alignCenter("��������������������������������\n");
		printf("\n");

		alignCenter("��ư�� �Է��ϼ��� : ");
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