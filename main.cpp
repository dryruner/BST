#include<iostream>
#include "BST.h"
#include<ctime>
#include<cstdlib>

int main(int argc, char* argv[])
{
	BSTree* root = NULL;
	uint vector[] = {15,6,18,3,7,17,20,2,4,13,9};
//	uint vector[] = {1,2,3,8};
	int i;
	const int length = sizeof(vector)/sizeof(uint);
//	BSTree* p;
	for(i = 0; i < length;i++)
		Insert_BST(&root,vector[i]);
	
	printf("InOrder_R: \n");
	InOrder_Traverse_R(root);	
	
//	printf("\nInOrder_I: \n");
//	InOrder_Traverse_I(root);
	printf("\nInOrder_I2: \n");
	InOrder_Traverse_I2(root);

//	printf("\nPreOrder_I: \n");
//	PreOrder_Traverse_I(root);
	printf("\nPreOrder_I2: \n");
	PreOrder_Traverse_I2(root);

	printf("\nPostOrder_I: \n");
	PostOrder_Traverse_I(root);
	printf("\nPostOrder_I2: \n");
	PostOrder_Traverse_I2(root);
	printf("\nPostOrder_I3: \n");
	PostOrder_Traverse_I3(root);

/*
	printf("\nMax value in BST: %u\n",MAX_BST(root)->key);
	printf("\nMin value in BST: %u\n",MIN_BST(root)->key);
	uint input;
*/	
/*	printf("\nplease input the value you want to search: ");
	scanf("%u",&input);
	BSTree* locate;
	locate = Search_BST_R(root,input);
	printf("\nSearch_R %u's value: %u\n",input,locate->key);
	locate = Search_BST_I(root,input);
	printf("Search_I %u's value: %u\n",input,locate->key);
*/
/*	while(input)
	{
		printf("\nplease input the value you want to delete: ");
		scanf("%u",&input);
		Delete_BST(root, input);
		printf("\nAfter delete %u:\n",input);
		InOrder_Traverse_R(root);
	}
*/

	level_print(root, sizeof(vector) / sizeof(uint));

	uint input;
	while(1)
	{
		printf("\nplease input the value: ");
		scanf("%u",&input);
		if (input == 0)
			break;
		SUCC_BST(root, input);
		PRE_BST(root, input);
//		InOrder_Traverse_R(root);
	}

	printf("\n");
	return 0;
}
