
/* 二叉树的结点结构 */

#include "stdio.h"
typedef char ElemType;         /* 数据域值类型 */
typedef struct Node
{ ElemType data;               /* 数据域 */
  struct Node *lchild,*rchild; /* 左、右指针域,分别存储左、右孩子的存储位置 */
}BitTree;



/* 先序建立二叉树*/

BitTree *CreBiTree(void)
{ BitTree *bt;ElemType x;
scanf("%c",&x);                /* 读入数据 */
  if(x==' ') bt=NULL;            /* 输入空格符,安排空指针 */
  else
  { bt=(BitTree *)malloc(sizeof(BitTree));
    bt->data=x;                  /* 生成新结点 */
    bt->lchild=CreBiTree();      /* 建立左子树 */
    bt->rchild=CreBiTree();      /* 建立右子树 */
  }
  return bt;                     /* 返回根结点的指针 */
}



/*教材【例5.10】统计二叉树中叶子结点的个数 */

int leafcount(BitTree *bt)
{ static int n=0;         /* 定义一个静态局部变量用来存放叶子结点的个数 */
  if(bt!=NULL)
  { if(bt->lchild==NULL&&bt->rchild==NULL) /* 若左、右为空，则为叶子结点 */
       n++;
    leafcount(bt->lchild);/* 统计左子树叶子结点个数 */
    leafcount(bt->rchild);/* 统计右子树叶子结点个数 */
  }
  return n;
}


main()
{ BitTree *bt;
  int n;
  
  printf("input data:");
  bt=CreBiTree(); /* 以图5.13为例建立二叉链表 */
  n=leafcount(bt);
  printf("the number of leaf nodes is:");
  printf("%d\n",n);

}


