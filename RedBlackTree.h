/*
	���� �� Ʈ�� ��Ģ

	1. ��� ���� ������ �ƴϸ� �������̴�.
	2. ��Ʈ���� �������̴�.
	3. ���� ���� �������̴�.
	4. ���� ����� �ڽĵ��� ��� �������̴�. ������ ���� ����� �ڽ��� �������� �ʿ�� ����(�ְ���)
	5. ��Ʈ��忡�� ��� �� ��� ���̿� �ִ� ������ ����� ���� ��� �����ϴ�.

*/

#ifndef _RED_BLACK_TREE_H
#define _RED_BLACK_TREE_H

#include<stdio.h>
#include<stdlib.h>

#define RED 0
#define BLACK 1

typedef struct _red_black_treenode
{
	int data;
	int color;

	struct _red_black_treenode* parent;
	struct _red_black_treenode* right;
	struct _red_black_treenode* left;


}Red_Black_TreeNode;

Red_Black_TreeNode* RBT_Create_Node(int data);
void show_menu();

#endif