#include "RedBlackTree.h"

Red_Black_TreeNode* null_leaf_node;

char* color_str[2] = { "RED","BLACK" };

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

void RBT_InsertNode(Red_Black_TreeNode** tree, Red_Black_TreeNode* new_node)
{
	//����Ʈ�� ������ ��� ����
	RBT_InsertNodeHelper(tree, new_node);

	//�� ��� ����
	new_node->color = RED;
	new_node->left = null_leaf_node;
	new_node->right = null_leaf_node;
	
	//�� ��� ���뷱��
	RBT_RebuildAfterInsert(tree, new_node);
}

void RBT_InsertNodeHelper(Red_Black_TreeNode** tree, Red_Black_TreeNode* new_node)
{
	if ((*tree) == NULL)//root node
	{
		(*tree) = new_node;
		return;
	}

	if ((*tree)->data < new_node->data)//move right of tree
	{
		if ((*tree)->right == null_leaf_node)
		{
			(*tree)->right = new_node;
			new_node->parent = *tree;
		}
		else
		{
			RBT_InsertNodeHelper(&((*tree)->right), new_node);
		}
	}
	else if ((*tree)->data > new_node->data) // move left of tree
	{
		if ((*tree)->left == null_leaf_node)
		{
			(*tree)->left = new_node;
			new_node->parent = *tree;
		}
		else
		{
			RBT_InsertNodeHelper(&((*tree)->left), new_node);
		}
	}


}

void RBT_RotateRight(Red_Black_TreeNode** root, Red_Black_TreeNode* parent)//rotate LL
{
	Red_Black_TreeNode* left_child = parent->left;

	//�θ����� left�� �ڽĳ���� ������ ���� ����
	parent->left = left_child->right;

	//�ڽĳ���� ������ �ڽ� ����� �θ� ��带 parent ��� ����
	if (left_child->right != null_leaf_node)
	{
		left_child->right->parent = parent;
	}

	//left ����� �θ��� ������Ʈ(parent�� �θ���� ����)
	left_child->parent = parent->parent;

	//�θ��尡 root ����� ���
	if (parent->parent == NULL)
	{
		(*root) = left_child;//�ڽĳ�带 root ���� ����
	}
	else//root ��尡 �ƴ� ���
	{
		//�Ҿƹ��� ����� ���� �ڽĳ�尡 �θ����� ���
		if (parent == parent->parent->left)
		{
			parent->parent->left = left_child;
		}
		else
		{
			parent->parent->right = left_child;
		}
	}

	left_child->right = parent;
	parent->parent = left_child;
}

void RBT_RotateLeft(Red_Black_TreeNode** root, Red_Black_TreeNode* parent)//rotate RR
{
	Red_Black_TreeNode* right_child = parent->right;

	//�θ����� left�� �ڽĳ���� ������ ���� ����
	parent->right = right_child->left;

	//�ڽĳ���� ���� �ڽ� ����� �θ� ��带 parent ��� ����
	if (right_child->left != null_leaf_node)
	{
		right_child->left->parent = parent;
	}

	//right ����� �θ��� ������Ʈ(parent�� �θ���� ����)
	right_child->parent = parent->parent;

	//�θ��尡 root ����� ���
	if (parent->parent == NULL)
	{
		(*root) = right_child;//�ڽĳ�带 root ���� ����
	}
	else//root ��尡 �ƴ� ���
	{
		//�Ҿƹ��� ����� ���� �ڽĳ�尡 �θ����� ���
		if (parent == parent->parent->left)
		{
			parent->parent->left = right_child;
		}
		else
		{
			parent->parent->right = right_child;
		}
	}

	right_child->left = parent;
	parent->parent = right_child;
}


/*
	���� ���(cur_node)�� RED�� ���, 
*/
void RBT_RebuildAfterInsert(Red_Black_TreeNode** root, Red_Black_TreeNode* cur_node)
{
	while ((cur_node != (*root)) && (cur_node->parent->color == RED))
	{
		if (cur_node->parent == cur_node->parent->parent->left)
		{
			Red_Black_TreeNode* uncle = cur_node->parent->parent->right;

			if (uncle == NULL)
			{
				return;
			}

			if (uncle->color == RED)
			{
				cur_node->parent->color = BLACK;
				uncle->color = BLACK;
				cur_node->parent->parent = RED;

				cur_node = cur_node->parent->parent;

			}
			else//uncle(����)����� ������ BLACK�� ���
			{
				//������ �������̸�, ���� ������ ��尡 �θ� ����� ������ �ڽ��� ���
				if (cur_node == cur_node->parent->right)
				{
					cur_node = cur_node->parent;
					RBT_RotateLeft(root, cur_node);
				}

				cur_node->parent->color = BLACK;
				cur_node->parent->parent->color = RED;

				RBT_RotateRight(root, cur_node->parent->parent);
			}
		}
		else
		{
			Red_Black_TreeNode* uncle = cur_node->parent->parent->left;

			if (uncle == NULL)
			{
				return;
			}

			if (uncle->color == RED)
			{
				cur_node->parent->color = BLACK;
				uncle->color = BLACK;
				cur_node->parent->parent = RED;

				cur_node = cur_node->parent->parent;

			}
			else//uncle(����)����� ������ BLACK�� ���
			{
				//������ �������̸�, ���� ������ ��尡 �θ� ����� ������ �ڽ��� ���
				if (cur_node == cur_node->parent->left)
				{
					cur_node = cur_node->parent;
					RBT_RotateRight(root, cur_node);
				}

				cur_node->parent->color = BLACK;
				cur_node->parent->parent->color = RED;

				RBT_RotateLeft(root, cur_node->parent->parent);
			}
		}
	}

	(*root)->color = BLACK;
}

void RBT_PrintTree(Red_Black_TreeNode* node, int depth, int black_count)
{
	char ch = 'H';
	int v = -1;
	char buffer_cnt[100];
	
	char* set_color = NULL;

	memset(buffer_cnt, 0, 100);

	//base case : ���� ��尡 NULL�� ��� Ȥ��  null_leaf_node�� ���
	if (node == NULL || node == null_leaf_node)
		return;
	if (node->color == BLACK)
	{
		black_count++;
	}
	//�������� �θ� ��尡 �����ϴ� ���(��, ��Ʈ ��� ����)
	if (node->parent != NULL)
	{
		v = node->parent->data;

		if (node->parent->left == node)
		{
			ch = 'L';
		}
		else
		{
			ch = 'R';
		}
	}


	//���� ����� �ڽĳ�尡 �� �� �� �������� ���� ���
	if ((node->left == null_leaf_node) && (node->right == null_leaf_node))
	{
		sprintf(buffer_cnt, "---------- %d", black_count);
	}
	else
	{
		sprintf(buffer_cnt, "");
	}

	for (int i = 0; i < depth; i++)
	{
		printf("	");
	}

	set_color = (node->color == RED) ? color_str[0] : color_str[1];

	printf("%d %s [%c,%d] %s\n", node->data,set_color, ch, v, buffer_cnt);

	RBT_PrintTree(node->left, depth + 1, black_count);
	RBT_PrintTree(node->right, depth + 1, black_count);
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
				int input_num = 0;

				printf("enter create node\n");
				
				printf("input_num : ");
				scanf("%d", &input_num);

				RBT_InsertNode(&Tree, RBT_Create_Node(input_num));
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
				printf("enter  display tree\n");
				RBT_PrintTree(Tree, 0, 0);
				printf("\n");

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