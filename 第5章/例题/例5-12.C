
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



/* 教材【例5.12】求二叉树的高度 */
int hightree(BitTree *bt)
{ int H,H1,H2;
  if(bt==NULL) H=0;                /* 空树,高度为0,此为递归结束条件 */
  else                             /* 非空树 */
  { H1=hightree(bt->lchild);       /* 计算左子树的高度 */
    H2=hightree(bt->rchild);       /* 计算右子树的高度 */
    H=(H1>H2?H1:H2)+1;/* 左右子树高度的最大值再加1(根结点)是树的高度 */
  }
  return H;
}



main()
{ BitTree *bt;
  printf("input data:");
  bt=CreBiTree();                  /* 以图5.13为例建立二叉链表 */
  
  printf("the height of binary tree is:");
  printf("%d\n",hightree(bt));
}


