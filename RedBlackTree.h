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
#include<string.h>

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
Red_Black_TreeNode* RBT_SearchNode(Red_Black_TreeNode* tree, int target);
void RBT_InsertNode(Red_Black_TreeNode** tree, Red_Black_TreeNode* new_node);
void RBT_InsertNodeHelper(Red_Black_TreeNode** tree, Red_Black_TreeNode* new_node);
Red_Black_TreeNode* RBT_SearchMinNode(Red_Black_TreeNode* tree);
void RBT_RotateRight(Red_Black_TreeNode** root, Red_Black_TreeNode* parent);//rotate LL
void RBT_RotateLeft(Red_Black_TreeNode** root, Red_Black_TreeNode* parent);//rotate RR
void RBT_RebuildAfterInsert(Red_Black_TreeNode** root, Red_Black_TreeNode* cur_node);

void RBT_RebuildAfterRemove(Red_Black_TreeNode** root, Red_Black_TreeNode* succ);
Red_Black_TreeNode* RBT_RemoveNode(Red_Black_TreeNode** root, int data);
void RBT_Destroy(Red_Black_TreeNode* Node);
void show_menu();

#endif