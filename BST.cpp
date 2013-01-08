#include "BST.h"
#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;
/*            
               root
                ↓
                15
               /  \
              6    18
             / \   / \
            3   7 17  20
           / \   \
          2   4  13
                /
               9

InOrder: 
	[2 3 4 6 7 9 13 15 17 18 20] ; in a non-decreasing sequence
	

typedef struct BSTree{
	int key;
	bool is_visited;
	BSTree* lchild;
	BSTree* rchild;
}BSTree;

 
*/


/* Recursive version */
void InOrder_Traverse_R(BSTree* root)
{
	if(root != NULL)
	{
		InOrder_Traverse_R(root->lchild);
		printf("%u ",root->key);
		InOrder_Traverse_R(root->rchild);
	}
}

/* Non-recursive version */
void InOrder_Traverse_I(BSTree* root)
{
	stack<BSTree*> S;
	S.push(root);
	BSTree* p_t;
	while(!S.empty())
	{
		p_t = S.top();
		if(p_t->lchild && p_t->lchild->is_visited == false)
			S.push(p_t->lchild);
		else
		{
			printf("%u ", p_t->key);
			p_t->is_visited = true;
			S.pop();
			
			if(p_t->rchild && p_t->rchild->is_visited == false)
				S.push(p_t->rchild);
		}
	}
}

/**
 Non-recursive version of Pre-Order traverse of BST, using C++ STL (stack) to implement
 */
void PreOrder_Traverse_I(BSTree* root)
{
	stack<BSTree*> S;
	S.push(root);
	BSTree* p_t;
	while(!S.empty())
	{
		p_t = S.top();
		if(p_t->is_visited == false)
		{
			printf("%u ", p_t->key);
			p_t->is_visited = true;
		}
		if(p_t->lchild && p_t->lchild->is_visited == false)
			S.push(p_t->lchild);
		else{
			S.pop();
			if(p_t->rchild && p_t->rchild->is_visited == false)
				S.push(p_t->rchild);
		}
	}
}


/**
 Non-recursive version of Post-Order traverse of BST, using C++ STL (stack) to implement
 */
void PostOrder_Traverse_I(BSTree* root)
{
	stack<BSTree*> S;
	S.push(root);
	BSTree* p_t;
	while(!S.empty())
	{
		p_t = S.top();
		if(p_t->lchild && p_t->lchild->is_visited == false)
			S.push(p_t->lchild);
		else if(p_t->rchild && p_t->rchild->is_visited == false)
			S.push(p_t->rchild);
		else
		{
			printf("%u ", p_t->key);
			p_t->is_visited = true;
			S.pop();
		}
	}
}

/* 
Return: NULL on no found; BSTree* pointer to that node if found
   Recursive Version 
 */
BSTree* Search_BST_R(BSTree* root, uint value)
{
	if(!root || (root->key == value)) 
		return root; // Note: both found and no-found could be concluded to this case
	if(value < root->key)
		return Search_BST_R(root->lchild,value);
	else
		return Search_BST_R(root->rchild,value);
}


/* 
Return: BSTree* pointer to that node;
		or NULL if no found
		
		Search BST by the key

 Non-Recursive Version
 */
BSTree* Search_BST_I(BSTree* root, uint value)
{
	BSTree* p = root;
	while(p)
	{
		if(p->key == value)
			return p;
		else if(value < p->key)
			p = p->lchild;
		else
			p = p->rchild;
	}
	return p;
}


/*
Return: pointer to the Max_key Node 
 */
BSTree* MAX_BST(BSTree* root)
{
	while(root->rchild)
		root = root->rchild;
	return root;
}


/*
Return: pointer to the Min_key Node
 */
BSTree* MIN_BST(BSTree* root)
{
	while(root->lchild)
		root = root->lchild;
	return root;
}




/* Predecessor and Successor are defined in InOrder traverse's
   sequence:
   if InOrder sequence is 1 2 3 5 7 9; then 5's pre is 3;
   5's succ is 7.(i.e. a's prede doesn't mean its parent; a's 
   succ doesn't mean its children.)
Return: pointer to the predecessor of node; or NULL if no predecessor.
Note: node shouldn't be NULL; you should ensure that node has a predecessor.
Time: O(h), h is height of BST
 */
BSTree* PRE_BST(BSTree* node)
{
	if(node->lchild) /* if the node has left-tree, then return
						the node of maximum key of left-tree */
		return MAX_BST(node->lchild);
	/* 
	else:
		case study: find 17's pre 15
	 */
	BSTree* up = node->parent;
	while(up && (up->lchild == node))
	{
		node = up;
		up = node->parent;
	}
	return up;
}

/*
   A top-down implementation of finding a key's predecessor without using parent pointer
   It also recieves the key which actually isn't in BST, and gives the "logical" predecessor
   of that key.
 */
void PRE_BST(BSTree* root, uint key)
{
	if(!root)
	{
		printf("BST empty, no predecessor for key: %u\n", key);
		return;
	}
	BSTree* p_pre = NULL;
	while(root)
	{
		if(root->key >= key)
		{
			root = root->lchild;
		}
		else
		{
			p_pre = root;
			root = root->rchild;
		}
	}
	if(!p_pre)
		printf("%u doesn't have predecessor\n", key);
	else
		printf("%u's predecessor is: %u\n", key, p_pre->key);
}

/*
Note: node shouldn't be NULL
You should ensure that node has a successor; or if not, it returns NULL.
Time: O(h),h is height of BST
 */
BSTree* SUCC_BST(BSTree* node)
{
	if(node->rchild) /* if node has right-tree, then return the node
						which has the minimum value in the right tree */
		return MIN_BST(node->rchild);
	/* 
	else :
		search upward until find that root locates in the 
		left child tree of up, 
		case study:(find 13's succ 15).
	*/
	BSTree* up = node->parent; 
	while(up && up->rchild == node)
	{
		node = up;
		up = node->parent;
	}
	return up;
}

/* 
   A top-down implementation of finding a key's successor without using parent pointer 
   It also receives the key which actually isn't in BST and gives the "logical" successor
   of that key.
 */
void SUCC_BST(BSTree* root, uint key)
{
	if(!root)
	{
		printf("BST empty, no successor for key: %u\n", key);
		return;
	}
	BSTree* p_succ = NULL;
	while(root)
	{
		if(root->key > key)
		{
			p_succ = root;
			root = root->lchild;
		}
		else
		{
			root = root->rchild;
		}
	}
	if(!p_succ)
		printf("%u doesn't have successor\n", key);
	else
		printf("%u's successor is: %u\n", key, p_succ->key);
}

/* A helpful function in malloc lab */
/*BSTree* Search_nearest_bigger(BSTree* root, uint value)
{
	BSTree* y = NULL;
	BSTree* result;
	while(root)
	{
		y = root;
		if(root->key == value)
			return root;
		else if(value < root->key)
			root = root->lchild;
		else
			root = root->rchild;
	}
	BSTree* temp = malloc(sizeof(BSTree));
	temp->key = value;
	temp->parent = y;
	temp->lchild = NULL;
	temp->rchild = NULL;
	if(temp->key < y->key)
	{
		y->lchild = temp;
	}
	else
	{
		y->rchild = temp;
	}
	result = SUCC_BST(temp);
	free(temp);
	return result;
}*/


/* another version, GOOD! */
BSTree* Search_nearest_bigger(BSTree* root, float value)
{
	if(root == NULL) // special case: if BST is empty, return NULL directly
		return NULL;
	BSTree* y = NULL;
	while(root)
	{
		y = root;
		if(root->key == value)
			return root;
		else if(value < root->key)
			root = root->lchild;
		else
			root = root->rchild;
	}
	if(value < y->key)
		return y;
	else
	{
		while(y && (y->key < value))
		{
			y = y->parent;
		}
		return y;
	}
}

/*
Lemma: 				the new inserted node is always the leaf node
Time complexity:	O(h); h is the height of BST
*/
void Insert_BST(BSTree** root, uint value)
{
	BSTree* node = (BSTree*)malloc(sizeof(BSTree));
	node->key = value;
	node->is_visited = false;
	node->lchild = NULL;
	node->rchild = NULL;
	node->parent = NULL;

	BSTree* x = *root;
	BSTree* y = NULL; // y is the parent of x, even when x is root(root->parent == NULL)
	/* find the place to insert, y denotes the right place */
	while(x != NULL)
	{
		y = x; // y is always the parent of x
		if(node->key <= x->key)
			x = x->lchild;
		else
			x = x->rchild;
	}
	node->parent = y;
	if(y == NULL)   //special case: if current tree is empty(x == NULL so while() doesn't execute)
		*root = node; 
	else
	{
		if(node->key <= y->key)
			y->lchild = node;
		else
			y->rchild = node;
	}
}

/* Delete without using parent pointer. */
void Delete_BST(BSTree* &Root, uint key)
{
	BSTree* p_root = NULL;
	BSTree* root = Root;
	if(!root)
	{
		printf("Tree empty, delete failed!\n");
		return;
	}
	while(root)
	{
		if(key < root->key)
		{
			p_root = root;
			root = root->lchild;
		}
		else if(key > root->key)
		{
			p_root = root;
			root = root->rchild;
		}
		else // find key item
		{
			if(!root->lchild)  //left child is empty
			{
				if(!p_root) // so the node we wanna delete is Root
					Root = root->rchild;
				else{
					if(p_root->lchild == root)
						p_root->lchild = root->rchild;
					else
						p_root->rchild = root->rchild;
				}
				free(root);
			}
			else if(!root->rchild) // right child is empty and left child is non-empty
			{
				if(!p_root)
					Root = root->lchild;
				else
				{
					if(p_root->lchild == root)
						p_root->lchild = root->lchild;
					else
						p_root->rchild = root->lchild;
				}
				free(root);
			}
			else // case 3: has 2 non-empty child
			{
				BSTree* p_succ = root->rchild;
				BSTree* p_root = root;
				while(p_succ->lchild)
				{
					p_root = p_succ;
					p_succ = p_succ->lchild;
				}
				root->key = p_succ->key; // replace key
				if(p_root->rchild == p_succ)
					p_root->rchild = p_succ->rchild;
				else
					p_root->lchild = p_succ->rchild;
				free(p_succ);
			}
			return;
		}
	}
	printf("key doesn't exist, delete failed!\n");
	return;
}
