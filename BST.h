#ifndef __BSTREE__
#define __BSTREE__

typedef unsigned int uint;

typedef struct BSTree{
	uint key;
	bool is_visited;
	struct BSTree* parent;
	struct BSTree* lchild;
	struct BSTree* rchild;
}BSTree;


void InOrder_Traverse_R(BSTree*);
void InOrder_Traverse_I(BSTree* root);
void PreOrder_Traverse_I(BSTree* root);
void PostOrder_Traverse_I(BSTree* root);

BSTree* Search_BST_R(BSTree*, unsigned int);
BSTree* Search_BST_I(BSTree*, unsigned int);
BSTree* MAX_BST(BSTree*);
BSTree* MIN_BST(BSTree*);
BSTree* PRE_BST(BSTree*);
BSTree* SUCC_BST(BSTree*);

/* C-Version */
BSTree* Search_nearest_bigger(BSTree*,float);
/* C++ Version */
//template<class T>
//void Search_nearest_bigger(BSTree** root, T value);

void Insert_BST(BSTree** root, uint value);
//void Delete_BST_my(BSTree* root, BSTree* node);
//BSTree* Delete_BST(BSTree** root, BSTree* node);
void Delete_BST(BSTree* &Root, uint key);
#endif
