#include "BST.h"
#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;
/*            
			  root
			    ↓
				15
			  /    \
			 6      18
		   /  \    /  \
		  3    7  17   20
         / \    \
        2   4    13
                /
               9

InOrder: 
	[2 3 4 6 7 9 13 15 17 18 20] ; in a non-decreasing sequence
	

typedef struct BSTree{
	int key;
	bool is_visited;
	BSTree* parent;
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
Description: insert a node(by key value) into BST
if node wasn't constructed, you should construct/init it in this way:
	
	BSTree* node = (BSTree*)malloc(sizeof(BSTree));
	node->key = value;
	node->is_visited = false;
	node->lchild = NULL;
	node->rchild = NULL;
	node->parent = NULL;

Lemma: 				the new inserted node is always the leaf node!
Time complexity:	O(h); h is the height of BST
Note:				have to return root pointer, or should modify 1st argument BSTree* root to BSTree* &root(reference is used in C++ only!)
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
		if(node->key < x->key)
			x = x->lchild;
		else
			x = x->rchild;
	}
	node->parent = y;
	if(y == NULL)   //special case: if current tree is empty(x == NULL so while() doesn't execute)
		*root = node; 
	else
	{
		if(node->key < y->key)
			y->lchild = node;
		else
			y->rchild = node;
	}
}

/* 
Lemma:		If one node in BST has two children(both not NULL), then its successor has no left child 
			&& its predecessor has no right child.(It's easy to understand). This lemma is useful in 
			the 3rd case in Delete_BST
Notice: 	Since Insert && Delete operation changed the structure of BST, i.e. root pointer 
			maybe points to another node, so we have to pass the reference of root(in C++)
			or use a pointer to the root pointer!(二级指针)
 */

BSTree* Delete_BST(BSTree** root, BSTree* node)
{
	BSTree *x,*y;
	if(!node->lchild || !node->rchild)
		y = node;
	else
		y = SUCC_BST(node); // y point to the node actually be deleted and y has at most one child(lemma)

	// x is y's child, or x is NULL if y is leaf node
	if(y->lchild)
		x = y->lchild;
	else
		x = y->rchild;
	//let x->parent points to y->parent; if x is NULL, everything is done, since y must be leaf node 
	if(x)
		x->parent = y->parent;
	
	if(!y->parent) // if y is root
		(*root) = x;
	else if(y == y->parent->lchild)
		y->parent->lchild = x;
	else
		y->parent->rchild = x;
	
	if(y != node)  // if the actually deleted node isn't node itself
		node->key = y->key; // This is a trick, see another version below
	
	return y;	
}