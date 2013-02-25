#include "BST.h"
#include <iostream>
#include <cstdlib>

/*
typedef struct Result{
	bool find1;
	bool find2;
	BSTree* p_find;

	public Result():find1(false),find2(false),p_find(NULL){}
}Result;
*/

/* 
 LCA of two nodes. NULL indicates no LCA
*/
BSTree* LCA(BSTree* root, uint key1, uint key2)
{
	Result r = LCACore(root, key1, key2);
	return r.p_find;
}

Result LCACore(BSTree* root, uint key1, uint key2)
{
	Result result = {false, false, NULL};
	if(!root)
		return result;
	
	Result result_l = LCACore(root->lchild, key1, key2);
	if(result_l.find1 && result_l.find2)
		return result_l;
	
	Result result_r = LCACore(root->rchild, key1, key2);
	if(result_r.find1 && result_r.find2)
		return result_r;
	
	result.find1 = result_l.find1 || result_r.find1;
	result.find2 = result_l.find2 || result_r.find2;
	
	if(root->key == key1)
	{
		result.find1 = true;
	}
	if(root->key == key2)
	{
		result.find2 = true;
	}
	if(result.find1 && result.find2)
	{
		result.p_find = root;
		return result;
	}
	return result;
}
