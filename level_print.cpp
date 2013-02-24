#include <stdio.h>
#include "BST.h"
#include <string.h>

/* 
   print a binary tree level by level.
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
Output: 15 6 18 3 7 17 20 2 4 13 9. 
  
   @param: N stands for the number of nodes of tree 
 */
void level_print(BSTree* root, int N)
{
	BSTree* queue[N]; // use arrays to implement Queue! Since there're N nodes so Queue.size() <= N!
	BSTree* p_temp;
	int front = 0;
	int rear = 0;
	int level = 0;
	int num = 1;  // Note: num is very importent in the level traversal
	int i;
	queue[rear++] = root;
	while(front < rear)
	{
		level++;
		printf("Level %d: ", level);
		for(i = 0; i < num; i++)
		{
			p_temp = queue[front++]; //dequeue
			printf("%d ", p_temp->key);
			if(p_temp->lchild)
				queue[rear++] = p_temp->lchild;
			if(p_temp->rchild)
				queue[rear++] = p_temp->rchild;
		}
		printf("\n");
		num = rear - front;
	}
}
