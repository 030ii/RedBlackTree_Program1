#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma warning(disable:4996)

/* �����Ʈ�� ���� */
Tree *createLBT(void)
{
	Tree *newTree;
	Member *newNIL;

	// ���ο� Ʈ���� �� �ȿ� �� �� ��带 �����
	newTree = malloc(sizeof(Tree));
	newNIL = malloc(sizeof(Member));

	// �� ����� �Ӽ��� �����ϰ�, Ʈ���� �� ��� ������ �Ҵ��Ѵ�
	newNIL->color = BLACK;
	newTree->NIL = newNIL;
	newTree->root = newTree->NIL;

	return newTree;
}

/* ��� ���� */
Member *createMember(Tree *LBT)
{
	Member *newMember = malloc(sizeof(Member));

	newMember->color = RED;
	newMember->left = LBT->NIL;
	newMember->right = LBT->NIL;

	return newMember;
}

/* ���ο� ��� ���� */
void insertNode(Tree *LBT, Member *Node)
{
	Member *curNode, *tempNode;

	// ���� ��尡 ��Ʈ����� ���
	if (LBT->root == LBT->NIL){
		LBT->root = Node;
		Node->parent = NULL;
		return;
	}

	// ���� ��尡 �� ��ġ�� ã�� NIL���� ��ü
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

/* �����Ʈ�� ���� ���� */
void treeFixUp(Tree *LBT, Member *Node)
{
	Member *p = Node->parent;
	Member *u = uncle(Node);
	Member *g = grandparent(Node);
	
	// case1 : ������ ��尡 ��Ʈ ����� ���
	if (Node == LBT->root)
	{
		Node->color = BLACK;
		return;
	}
	// case2 : ������ ��尡 ��Ʈ ����� �ڽ� ����� ���
	else if (p->color == BLACK)
	{
		return;
	}
	// case3 : ������ ���� �θ� ����� ���� �������� ���
	else if (Node->color == RED && p->color == RED)
	{
		// case 3-1 : ���� ��尡 �������� ���
		if (u->color == BLACK)
		{
			// case 3-1-1 : ���� ���� �θ� ����� ������ �ݴ��� ���
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

			// case 3-1-2 : ���� ���� �θ� ����� ������ ������ ���
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
		// case 3-2 : ���� ��尡 �������� ���
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

// ���� ����� �θ��� �θ� ���
Member *grandparent(Member *Node)
{
	if ((Node != NULL) && (Node->parent != NULL))
		return Node->parent->parent;
	else
		return NULL;
}

// ���� ����� �θ��� ���� ���
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

// ���� �θ� ����� ��ġ�� �������� ����
void rotateLeft(Tree *LBT, Member *Node)
{
	Member *p = Node->parent;
	Member *g = grandparent(Node);
	Member *temp = Node->left;

	// �θ� ��Ʈ ����� ���
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


// ���� �θ� ����� ��ġ�� ���������� ����
void rotateRight(Tree *LBT, Member *Node)
{
	Member *p = Node->parent;
	Member *g = grandparent(Node);
	Member *temp = Node->right;

	// �θ� ��Ʈ ����� ���
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

// Ʈ�� ���
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