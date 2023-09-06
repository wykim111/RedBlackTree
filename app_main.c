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

void RBT_Destroy(Red_Black_TreeNode* Node)
{
	printf("RBT_Destroy :: free\n");

	free(Node);
}


Red_Black_TreeNode* RBT_SearchNode(Red_Black_TreeNode* tree, int target)
{
	if (tree == null_leaf_node)
	{
		return NULL;
	}

	if (tree->data > target)
	{
		return RBT_SearchNode(tree->left, target);
	}
	else if (tree->data < target)
	{
		return RBT_SearchNode(tree->right, target);
	}
	else
	{
		return tree;
	}

}
/*
	RBT ����
*/
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
			RBT_InsertNodeHelper(&(*tree)->right, new_node);
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
			RBT_InsertNodeHelper(&(*tree)->left, new_node);
		}
	}


}

Red_Black_TreeNode* RBT_SearchMinNode(Red_Black_TreeNode* tree)
{
	if (tree == null_leaf_node)
	{
		return null_leaf_node;
	}

	if (tree->left == null_leaf_node)
	{
		return tree;
	}
	else
	{
		return RBT_SearchMinNode(tree->left);
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

			if (uncle->color == RED)
			{
				cur_node->parent->color = BLACK;
				uncle->color = BLACK;
				cur_node->parent->parent->color = RED;

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

			if (uncle->color == RED)
			{
				cur_node->parent->color = BLACK;
				uncle->color = BLACK;
				cur_node->parent->parent->color = RED;

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
/*
	succ : �������(Doubly Black)�� ���� ����.
*/
void RBT_RebuildAfterRemove(Red_Black_TreeNode** root, Red_Black_TreeNode* succ)
{
	Red_Black_TreeNode* sibling = NULL;

	//��Ʈ����̰ų�, ������ ������� �������� �Ѿ�� ���� ����
	while (succ->parent != NULL && succ->color == BLACK)
	{
		//��ü ��尡 �θ����� left�� ��ġ�� ���
		if (succ == succ->parent->left)
		{
			sibling = succ->parent->right;//���� ���

			//������ �������� ���
			if (sibling->color == RED)
			{
				/*
					1. ������ ������, �θ� ���������� ����
					2. �θ� �������� ��ȸ��
					3. ���� ��� ��带 ���������� ó��
				*/
				sibling->color = BLACK;
				succ->parent->color = RED;
				RBT_RotateLeft(root, succ->parent);//�θ� �������� ��ȸ��
				sibling = succ->parent->right;//���� ��� ����

			}
			else//������ �������� ���
			{
				//����/������ ��� ������ �ڽ�(��ī)��尡 �������� ���
				if ((sibling->left->color == BLACK) && (sibling->right->color == BLACK))
				{
					sibling->color = RED;
					succ = succ->parent;
				}
				else//���� Ȥ�� ������  ������ �ڽ�(��ī)��尡 �������� ���
				{
					/*
						�ش� ��ɿ� ���� ����
						- ���� ��ī ���� RED Ȥ�� BLACK�� �� �� �����Ƿ� ���� �˻�
						- ������ ��ī ���� RED�̵� RIGHT�̵� ��� ������ �ٲٸ� ��(������� ����).
					
					*/

					if (sibling->left->color == RED)//������ ���� �ڽ�(��ī)�� �������� ���
					{
						sibling->left->color = BLACK;
						sibling->color = RED;
						RBT_RotateRight(root,sibling);
						sibling = succ->parent->right;
					}

					//������ ������ �ڽ�(��ī)�� �������� ���
					sibling->color = sibling->parent->color;
					succ->parent->color = BLACK;
					sibling->right->color = BLACK;
					RBT_RotateLeft(root, succ->parent);
					succ = (*root);
					
				}
				
			}
		}
		else//��ü ��尡 �θ����� right�� ��ġ�� ���
		{			
			//������尡 �θ� ����� ���ʿ� �����ϴ� ���
			sibling = succ->parent->left;

			if (sibling->color == RED)
			{
				sibling->color = BLACK;
				succ->parent->color = RED;
				RBT_RotateRight(root, succ->parent);
				sibling = succ->parent->left;
			}
			else//���� ������ BLACK�� ���
			{
				if ((sibling->left->color == BLACK) && (sibling->right->color == BLACK))
				{
					sibling->color = RED;
					succ = succ->parent;
				}
				else
				{
					if (sibling->right->color == RED)
					{
						sibling->right->color = BLACK;
						sibling->color = RED;

						RBT_RotateLeft(root, sibling);
						sibling = succ->parent->left;
					}

					sibling->color = succ->parent->color;
					succ->parent->color = BLACK;
					sibling->left->color = BLACK;
					RBT_RotateRight(root, succ->parent);
					succ = (*root);

				}

			}

			
		}
	}

	succ->color = BLACK;
}


Red_Black_TreeNode* RBT_RemoveNode(Red_Black_TreeNode** root, int data)
{
	//������ ��ġ ���
	Red_Black_TreeNode* remove_node = NULL;
	//������ �� ����� ���
	Red_Black_TreeNode* succ_node = NULL;
	//data�� �����ϴ� ��� 
	Red_Black_TreeNode* target = RBT_SearchNode(*root,data);

	if (target == NULL)
	{
		return NULL;
	}

	if ((target->left == null_leaf_node) || (target->right == null_leaf_node))
	{
		remove_node = target;
	}
	else
	{
		remove_node = RBT_SearchMinNode(target->right);//�ִ� ����� left�� ���� ���� Ʈ�� ����߿��� ����.
		target->data = remove_node->data;
	}

	if (remove_node->left != null_leaf_node)
	{
		succ_node = remove_node->left;
	}
	else
	{
		succ_node = remove_node->right;
	}

	succ_node->parent = remove_node->parent;

	if (remove_node->parent == NULL)//�θ��尡 ��Ʈ ����� ���
	{
		(*root) = succ_node;
	}
	else
	{
		//��ü ��� ����
		if (remove_node == remove_node->parent->left)
		{
			remove_node->parent->left = succ_node;
		}
		else
		{
			remove_node->parent->right = succ_node;
		}
	}

	if (remove_node->color == BLACK)
	{
		//rebuild tree
		//RBT_RebuildAfterRemove(root, succ_node);
	}

	return remove_node;
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

	null_leaf_node = RBT_Create_Node(0);
	null_leaf_node->color = BLACK;


	while (1)
	{
		int cmd;

		show_menu();
		
		scanf("%d", &cmd);
		getchar();

		switch (cmd)
		{
			case 1:
			{
				int input_num = 0;

				printf("enter create node\n");
				
				printf("input_num : ");
				scanf("%d", &input_num);
				getchar();

				RBT_InsertNode(&Tree, RBT_Create_Node(input_num));
			}
			break;
			case 2:
			{
				int remove_num = 0;

				printf("enter remove node\n");

				printf("remove_num : ");
				scanf("%d", &remove_num);

				Node = RBT_RemoveNode(&Tree, remove_num);




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