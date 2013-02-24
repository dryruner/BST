#include <stdio.h>
#include "BST.h"
#include <string.h>
#include <queue>
#include <stack>

/* 
 Convert a binary tree to its mirror iteratively:
 For example:
               root
                ↓
                15
               /  \
              6    18
             / \     \
            3   7    20

After mirroring:
               root
                ↓
                15
               /  \
              18    6
             /     / \
            20    7   3
 */
void mirror_tree(BSTree* root)
{
	if(!root)
		return;
	std::stack<BSTree*> S;
	BSTree* p_temp;
	BSTree* p_swap;
	S.push(root);
	while(!S.empty())
	{
		p_temp = S.top();
		S.pop();
		p_swap = p_temp->lchild;
		p_temp->lchild = p_temp->rchild;
		p_temp->rchild = p_swap;
		if(p_temp->lchild)
			S.push(p_temp->lchild);
		if(p_temp->rchild)
			S.push(p_temp->rchild);
	}
}
