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
	RBT 삽입
*/
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

			if (uncle->color == RED)
			{
				cur_node->parent->color = BLACK;
				uncle->color = BLACK;
				cur_node->parent->parent->color = RED;

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

			if (uncle->color == RED)
			{
				cur_node->parent->color = BLACK;
				uncle->color = BLACK;
				cur_node->parent->parent->color = RED;

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
/*
	succ : 이증흑색(Doubly Black)을 갖고 있음.
*/
void RBT_RebuildAfterRemove(Red_Black_TreeNode** root, Red_Black_TreeNode* succ)
{
	Red_Black_TreeNode* sibling = NULL;

	//루트노드이거나, 빨간색 노드한테 검은색이 넘어가면 루프 종료
	while (succ->parent != NULL && succ->color == BLACK)
	{
		//대체 노드가 부모노드의 left에 위치한 경우
		if (succ == succ->parent->left)
		{
			sibling = succ->parent->right;//형제 노드

			//형제가 빨간색인 경우
			if (sibling->color == RED)
			{
				/*
					1. 형제를 검은색, 부모를 빨간색으로 변경
					2. 부모를 기준으로 좌회전
					3. 이중 흑색 노드를 검은색으로 처리
				*/
				sibling->color = BLACK;
				succ->parent->color = RED;
				RBT_RotateLeft(root, succ->parent);//부모를 기준으로 좌회전
				sibling = succ->parent->right;//형제 노드 참조

			}
			else//형제가 검은색인 경우
			{
				//왼쪽/오른쪽 모두 형제의 자식(조카)노드가 검은색인 경우
				if ((sibling->left->color == BLACK) && (sibling->right->color == BLACK))
				{
					sibling->color = RED;
					succ = succ->parent;
				}
				else//왼쪽 혹은 오른쪽  형제의 자식(조카)노드가 빨간색인 경우
				{
					/*
						해당 기능에 대한 고찰
						- 왼쪽 조카 노드는 RED 혹은 BLACK이 될 수 있으므로 조건 검사
						- 오른쪽 조카 노드는 RED이든 RIGHT이든 모두 블랙으로 바꾸면 됨(결과론적 관점).
					
					*/

					if (sibling->left->color == RED)//형제의 왼쪽 자식(조카)가 빨간색인 경우
					{
						sibling->left->color = BLACK;
						sibling->color = RED;
						RBT_RotateRight(root,sibling);
						sibling = succ->parent->right;
					}

					//형제의 오른쪽 자식(조카)이 빨간색인 경우
					sibling->color = sibling->parent->color;
					succ->parent->color = BLACK;
					sibling->right->color = BLACK;
					RBT_RotateLeft(root, succ->parent);
					succ = (*root);
					
				}
				
			}
		}
		else//대체 노드가 부모노드의 right에 위치한 경우
		{			
			//형제노드가 부모 노드의 왼쪽에 존재하는 경우
			sibling = succ->parent->left;

			if (sibling->color == RED)
			{
				sibling->color = BLACK;
				succ->parent->color = RED;
				RBT_RotateRight(root, succ->parent);
				sibling = succ->parent->left;
			}
			else//형제 색깔이 BLACK인 경우
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
	//삭제할 위치 노드
	Red_Black_TreeNode* remove_node = NULL;
	//삭제한 뒤 대신할 노드
	Red_Black_TreeNode* succ_node = NULL;
	//data가 존재하는 노드 
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
		remove_node = RBT_SearchMinNode(target->right);//최단 노드의 left는 가장 값이 트리 노드중에서 작음.
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

	if (remove_node->parent == NULL)//부모노드가 루트 노드인 경우
	{
		(*root) = succ_node;
	}
	else
	{
		//대체 노드 연결
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