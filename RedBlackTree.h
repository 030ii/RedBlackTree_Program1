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

Tree *createLBT(void);				/* 레드블랙트리 생성 */
Member *createMember(Tree *LBT);	/* 새로운 노드 생성 */

Member *grandparent(Member *Node);	/* 노드의 부모의 부모 노드 */
Member *uncle(Member *Node);		/* 노드의 부모의 형제 노드 */

void insertNode(Tree *LBT, Member *Node);	/* 트리에 노드 삽입 */
void treeFixUp(Tree *LBT, Member *Node);	/* 트리 균형 수정 */

void rotateLeft(Tree *LBT, Member *Node);	/* 트리 좌측 회전 */
void rotateRight(Tree *LBT, Member *Node);	/* 트리 우측 회전 */

void printTree(Tree *LBT, Member *Node);	/* 트리 노드 출력 */
void fprintTree(FILE *fp, Tree *LBT, Member *Node);	/* 트리 노드 파일 출력 */
Member *searchValue(Tree *LBT, Member *Node, int id); /* 노드 검색 */

#endif