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
	//이진트리 원리로 노드 삽입
	RBT_InsertNodeHelper(tree, new_node);

	//새 노드 정의
	new_node->color = RED;
	new_node->left = null_leaf_node;
	new_node->right = null_leaf_node;
	
	//새 노드 리밸런싱
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

	//부모노드의 left를 자식노드의 오른쪽 노드와 연결
	parent->left = left_child->right;

	//자식노드의 오르쪽 자식 노드의 부모 노드를 parent 노드 연결
	if (left_child->right != null_leaf_node)
	{
		left_child->right->parent = parent;
	}

	//left 노드의 부모노드 업데이트(parent의 부모노드와 연결)
	left_child->parent = parent->parent;

	//부모노드가 root 노드인 경우
	if (parent->parent == NULL)
	{
		(*root) = left_child;//자식노드를 root 노드로 설정
	}
	else//root 노드가 아닌 경우
	{
		//할아버지 노드의 왼쪽 자식노드가 부모노드인 경우
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

	//부모노드의 left를 자식노드의 오른쪽 노드와 연결
	parent->right = right_child->left;

	//자식노드의 왼쪽 자식 노드의 부모 노드를 parent 노드 연결
	if (right_child->left != null_leaf_node)
	{
		right_child->left->parent = parent;
	}

	//right 노드의 부모노드 업데이트(parent의 부모노드와 연결)
	right_child->parent = parent->parent;

	//부모노드가 root 노드인 경우
	if (parent->parent == NULL)
	{
		(*root) = right_child;//자식노드를 root 노드로 설정
	}
	else//root 노드가 아닌 경우
	{
		//할아버지 노드의 왼쪽 자식노드가 부모노드인 경우
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
	현재 노드(cur_node)가 RED인 경우, 
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
			else//uncle(삼촌)노드의 색깔이 BLACK인 경우
			{
				//삼촌이 검은색이며, 새로 삽입한 노드가 부모 노드의 오른쪽 자식인 경우
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
			else//uncle(삼촌)노드의 색깔이 BLACK인 경우
			{
				//삼촌이 검은색이며, 새로 삽입한 노드가 부모 노드의 오른쪽 자식인 경우
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

	//base case : 현재 노드가 NULL인 경우 혹은  null_leaf_node인 경우
	if (node == NULL || node == null_leaf_node)
		return;
	if (node->color == BLACK)
	{
		black_count++;
	}
	//현재노드의 부모 노드가 존재하는 경우(즉, 루트 노드 제외)
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


	//현재 노드의 자식노드가 양 쪽 다 존재하지 않은 경우
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