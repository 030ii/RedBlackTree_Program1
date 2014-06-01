#ifndef __REDBLACKTREE_H__
#define __REDBLACKTREE_H__

#define BLACK 1
#define RED -1

typedef struct member{
	int color; // 0 = black, 1 = red
	struct member *parent;
	struct member *left;
	struct member *right;
	int id;
	char name[10];
	char addr[256];
	char phone[15];
}Member;

typedef struct tree{
	struct member *root;
	struct member *NIL;
}Tree;

Tree *createLBT(void);				/* �����Ʈ�� ���� */
Member *createMember(Tree *LBT);	/* ���ο� ��� ���� */

Member *grandparent(Member *Node);	/* ����� �θ��� �θ� ��� */
Member *uncle(Member *Node);		/* ����� �θ��� ���� ��� */

void insertNode(Tree *LBT, Member *Node);	/* Ʈ���� ��� ���� */
void treeFixUp(Tree *LBT, Member *Node);	/* Ʈ�� ���� ���� */

void rotateLeft(Tree *LBT, Member *Node);	/* Ʈ�� ���� ȸ�� */
void rotateRight(Tree *LBT, Member *Node);	/* Ʈ�� ���� ȸ�� */

void printTree(Tree *LBT, Member *Node);	/* Ʈ�� ��� ��� */
void fprintTree(FILE *fp, Tree *LBT, Member *Node);	/* Ʈ�� ��� ���� ��� */
Member *searchValue(Tree *LBT, Member *Node, int id); /* ��� �˻� */

#endif