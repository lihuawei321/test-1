
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



/* 教材习题5-4-2 已知一棵二叉树以二叉链表结构存储，试编制算法计算给定结点所在的层次 */
int levelnode(BitTree *bt,ElemType x)
{ static int h=1,flag=0;
  if(bt!=NULL)
    if(bt->data==x)
    { flag=1;return h;}
    else
    { h++;
      levelnode(bt->lchild,x);
      if(!flag)
      { h++;
        levelnode(bt->rchild,x);
        h--;
      }
    }
  else {--h;return 0;}
}




main()
{ BitTree *bt;
  ElemType x;
  int n;
  printf("input data:");
  bt=CreBiTree();                  /* 以图5.13为例建立二叉链表 */
  
  printf("input x:");
  scanf("%*c%c",&x);

  n=levelnode(bt,x);
  if(n) printf("%c in %d level\n",x,n);
  else printf("%c not exist!\n",x);
}


