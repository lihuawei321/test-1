
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


/*先序遍历二叉树的递归算法*/
void PreOrder(BitTree *bt)
{ if(bt!=NULL)
  { printf("%c",bt->data);    /* 访问根结点 */
    PreOrder(bt->lchild);     /* 先序遍历根结点的左子树 */
    PreOrder(bt->rchild);     /* 先序遍历根结点的右子树 */
  }
}


/* 教材习题5-4-8 交换二叉树中所有度为2 的结点的左右子树 */
exchangetree(BitTree *bt)
{ BitTree *t;
  if(bt!=NULL)
   if(bt->lchild!=NULL&&bt->rchild!=NULL)
   { t=bt->lchild;bt->lchild=bt->rchild;bt->rchild=t;
     exchangetree(bt->lchild);
     exchangetree(bt->rchild);
   }
}




main()
{ BitTree *bt;

  printf("input data:");
  bt=CreBiTree();                            /* 以图5.13为例建立二叉链表 */

  printf("PreOrder result before exchang:\n");
  PreOrder(bt);
  printf("\n");

  exchangetree(bt); 

  printf("PreOrder result after exchang:\n");
  PreOrder(bt);
  printf("\n");
}