#include "RedBlackTree.h"

Red_Black_TreeNode* leaf_node = NULL;


Red_Black_TreeNode* RBT_Create_Node(int data)
{
	Red_Black_TreeNode* new_node = (Red_Black_TreeNode*)malloc(sizeof(Red_Black_TreeNode));

	new_node->color = BLACK;
	new_node->data = data;

	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

void show_menu()
{
	printf("(1) create Node\n");
	printf("(2) remove Node\n");
	printf("(3) search Node\n");
	printf("(4) display tree\n");
	printf("(5) quit\n");

	printf("\ninput cmd number:");
}
int main()
{
	Red_Black_TreeNode* Tree = NULL;
	Red_Black_TreeNode* Node = NULL;

	while (1)
	{
		int cmd;

		show_menu();
		
		scanf("%d", &cmd);

		switch (cmd)
		{
			case 1:
			{
				printf("enter create node\n");
			}
			break;
			case 2:
			{

			}
			break;
			case 3:
			{

			}
			break;
			case 4:
			{

			}
			break;
			case 5:
			{
				printf("enter exit\n");
			}
			return 0;
			default:
			{

			}
			break;
		}

	}


	return 0;
}