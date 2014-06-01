#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma warning(disable:4996)

/* 레드블랙트리 생성 */
Tree *createLBT(void)
{
	Tree *newTree;
	Member *newNIL;

	// 새로운 트리와 그 안에 들어갈 빈 노드를 만든다
	newTree = malloc(sizeof(Tree));
	newNIL = malloc(sizeof(Member));

	// 빈 노드의 속성을 지정하고, 트리의 빈 노드 영역에 할당한다
	newNIL->color = BLACK;
	newTree->NIL = newNIL;
	newTree->root = newTree->NIL;

	return newTree;
}

/* 노드 생성 */
Member *createMember(Tree *LBT)
{
	Member *newMember = malloc(sizeof(Member));

	newMember->color = RED;
	newMember->left = LBT->NIL;
	newMember->right = LBT->NIL;

	return newMember;
}

/* 새로운 노드 삽입 */
void insertNode(Tree *LBT, Member *Node)
{
	Member *curNode, *tempNode;

	// 현재 노드가 루트노드일 경우
	if (LBT->root == LBT->NIL){
		LBT->root = Node;
		Node->parent = NULL;
		return;
	}

	// 현재 노드가 들어갈 위치를 찾아 NIL노드와 교체
	curNode = LBT->root;
	tempNode = curNode;
	while (curNode != LBT->NIL)
	{
		tempNode = curNode;
		if (curNode->id > Node->id)
			curNode = tempNode->left;
		else
			curNode = tempNode->right;
	}

	Node->parent = tempNode;
	if (tempNode->id > Node->id)
		tempNode->left = Node;
	else
		tempNode->right = Node;


	return;
}

/* 레드블랙트리 오류 수정 */
void treeFixUp(Tree *LBT, Member *Node)
{
	Member *p = Node->parent;
	Member *u = uncle(Node);
	Member *g = grandparent(Node);
	
	// case1 : 삽입한 노드가 루트 노드인 경우
	if (Node == LBT->root)
	{
		Node->color = BLACK;
		return;
	}
	// case2 : 삽입한 노드가 루트 노드의 자식 노드인 경우
	else if (p->color == BLACK)
	{
		return;
	}
	// case3 : 삽입한 노드와 부모 노드의 색이 빨간색인 경우
	else if (Node->color == RED && p->color == RED)
	{
		// case 3-1 : 삼촌 노드가 검은색인 경우
		if (u->color == BLACK)
		{
			// case 3-1-1 : 현재 노드와 부모 노드의 방향이 반대인 경우
			if (Node == p->left && p == g->right)
			{
				rotateRight(LBT, Node);
				Node = p;
			}
			else if (Node == p->right && p == g->left)
			{
				rotateLeft(LBT, Node);
				Node = p;
			}

			// case 3-1-2 : 현재 노드와 부모 노드의 방향이 직선인 경우
			p->color = BLACK;
			if (p == g->left)
			{
				rotateRight(LBT, p);
			}
			else if (p == g->right)
			{
				rotateLeft(LBT, p);
			}
		}
		// case 3-2 : 삼촌 노드가 빨간색인 경우
		else
		{
			p->color = BLACK;
			u->color = BLACK;
			g->color = RED;
			treeFixUp(LBT, g);
		}
	}

	return;
}

// 현재 노드의 부모의 부모 노드
Member *grandparent(Member *Node)
{
	if ((Node != NULL) && (Node->parent != NULL))
		return Node->parent->parent;
	else
		return NULL;
}

// 현재 노드의 부모의 형제 노드
Member *uncle(Member *Node)
{
	Member *g = grandparent(Node);

	if (g == NULL)
		return NULL;
	if (Node->parent == Node->left)
		return g->right;
	else
		return g->left;
}

// 노드와 부모 노드의 위치를 왼쪽으로 돌림
void rotateLeft(Tree *LBT, Member *Node)
{
	Member *p = Node->parent;
	Member *g = grandparent(Node);
	Member *temp = Node->left;

	// 부모가 루트 노드인 경우
	if (g == NULL)
	{
		LBT->root = Node;
	}
	else
	{
		if (p == g->left)
			g->left = Node;
		else
			g->right = Node;
	}

	Node->parent = g;
	Node->left = p;
	p->parent = Node;
	p->right = temp;
}


// 노드와 부모 노드의 위치를 오른쪽으로 돌림
void rotateRight(Tree *LBT, Member *Node)
{
	Member *p = Node->parent;
	Member *g = grandparent(Node);
	Member *temp = Node->right;

	// 부모가 루트 노드인 경우
	if (g == NULL)
	{
		LBT->root = Node;
	}
	else
	{
		if (p == g->left)
			g->left = Node;
		else
			g->right = Node;
	}

	Node->parent = g;
	Node->right = p;
	p->parent = Node;
	p->left = temp;
}

// 트리 출력
void printTree(Tree *LBT, Member *Node)
{
	if (Node->left != LBT->NIL)
	{
		printTree(LBT, Node->left);
	}
	printf("%d\t\t%s\t\t%s\t\t%s\n", Node->id, Node->name, Node->addr, Node->phone);
	if (Node->right != LBT->NIL)
	{
		printTree(LBT, Node->right);
	}
	return;
}

Member *searchValue(Tree *LBT, Member *Node, int id)
{
	while (Node != LBT->NIL && Node->id != id)
	{
		if (Node->id > id)
			Node = Node->left;
		else
			Node = Node->right;
	}

	if (Node == LBT->NIL)
		Node = NULL;

	return Node;
}