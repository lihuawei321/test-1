
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



/* 教材【例5.13】查找值为x的结点。找到带回该结点的指针，否则带回空指针 */
int find=0;                  /* 设置查找标记：0表示未找到，1表示找到 */
void searchtree(BitTree *bt,ElemType x,BitTree **p)
{ if(bt!=NULL&&!find)
    if(bt->data==x)
    { find=1;*p=bt;}               /* 找到,通过p带回该结点的指针 */
    else
    { *p=NULL;                     /* 未找到，通过p带回空指针 */
      searchtree(bt->lchild,x,p);  /* 在左子树查找 */
      searchtree(bt->rchild,x,p);  /* 在右子树查找 */
    }
}




main()
{ BitTree *bt,*p;
  ElemType x;
  printf("input data:");
  bt=CreBiTree();             /* 以图5.13为例建立二叉链表 */

  printf("input x:");
  scanf("%*c%c",&x);
  searchtree(bt,x,&p);
  if(find)  printf("%c exist\n",p->data);
  else printf("%c not exist\n",x);
}
