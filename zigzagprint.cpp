#include <stdio.h>
#include "BST.h"
#include <string.h>
#include <vector>

/* print a binary tree in zig-zag way 
 For example:
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

zig-zag print: 15 6 18 20 17 7 3 2 4 13 9

 */
void zigzag_print(BSTree* root)
{
	if(!root)return;
	std::vector<BSTree*> Q;
	BSTree* p_temp;
	Q.push_back(root);
	bool l2r = true;
	while(!Q.empty())
	{
		int len_per_level = Q.size();
		for(int i = len_per_level-1; i >=0; i--)
		{
			p_temp = Q[i];
			printf("%d ", Q[len_per_level-i-1]->key);
			if(l2r)
			{
				if(p_temp->lchild)
					Q.push_back(p_temp->lchild);
				if(p_temp->rchild)
					Q.push_back(p_temp->rchild);
			}
			else
			{
				if(p_temp->rchild)
					Q.push_back(p_temp->rchild);
				if(p_temp->lchild)
					Q.push_back(p_temp->lchild);
			}
		}
		printf("\n");
		Q.erase(Q.begin(), Q.begin() + len_per_level);
		l2r = !l2r;
	}
}
