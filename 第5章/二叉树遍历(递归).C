
/* 二叉树的结点结构 */

#include "stdio.h"
typedef char ElemType;         /* 数据域值类型 */
typedef struct Node
{ ElemType data;               /* 数据域 */
  struct Node *lchild,*rchild; /* 左、右指针域,分别存储左、右孩子的存储位置 */
}BitTree;



/* 先序建立二叉树 */

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


/* 先序遍历二叉树的递归算法 */
void PreOrder(BitTree *bt)
{ if(bt!=NULL)
  { printf("%c",bt->data);    /* 访问根结点 */
    PreOrder(bt->lchild);     /* 先序遍历根结点的左子树 */
    PreOrder(bt->rchild);     /* 先序遍历根结点的右子树 */
  }
}


/* 中序遍历二叉树的递归算法 */
void InOrder(BitTree *bt)
{ if(bt!=NULL)
  { InOrder(bt->lchild);     /* 中序遍历根结点的左子树 */
    printf("%c",bt->data);   /* 访问根结点 */
    InOrder(bt->rchild);     /* 中序遍历根结点的右子树 */
  }
}


/* 后序遍历二叉树的递归算法 */
void PostOrder(BitTree *bt)
{ if(bt!=NULL)
  { PostOrder(bt->lchild);   /* 后序遍历根结点的左子树 */
    PostOrder(bt->rchild);   /* 后序遍历根结点的右子树 */
    printf("%c",bt->data);   /* 访问根结点 */
  }
}



main()
{ BitTree *bt;
  printf("input data:");
  bt=CreBiTree();             /* 可以图5.13为例建立二叉链表 */

  printf("PreOrder result:");
  PreOrder(bt);
  printf("\n");

  printf("InOrder result:");
  InOrder(bt);
  printf("\n");

  printf("PostOrder result:");
  PostOrder(bt);
  printf("\n");
}