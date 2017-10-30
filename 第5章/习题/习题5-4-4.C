#include "stdio.h"
/* 线索二叉树的结点结构 */
typedef char ElemType;
typedef struct node
{ ElemType data;
  struct node *lchild;
  struct node *rchild;
  int ltag;
  int rtag;
}BiThrTree;

#include "stdio.h"

/* 先序建立二叉树 */
BiThrTree *creatree()
{ BiThrTree *t;
  ElemType ch;
  scanf("%c",&ch);
  if(ch==' ')
    t=NULL;
  else
  {  t=(BiThrTree *)malloc(sizeof(BiThrTree));
     t->data=ch;
     t->lchild=creatree();
     t->rchild=creatree();
  }
  return t;
}

/* 先序线索化处理算法,Thrt指向头结点 */

BiThrTree *pre;                                /* 指向遍历结点的前驱结点 */
BiThrTree *PreOrderThreading(BiThrTree *T)
{ BiThrTree *Thrt;
  Thrt=(BiThrTree *)malloc(sizeof(BiThrTree)); /* 头结点 */
  Thrt->ltag=0; Thrt->rtag=1; Thrt->rchild=Thrt;
  if(!T) Thrt->lchild=Thrt;                    /* 若二叉树为空，则头结点自身构成一个循环链表 */
  else
  { Thrt->lchild=T; pre=Thrt;                  /* 头结点的左指针指向根结点,pre指向头结点 */
    PreThreading(T);                           /* 对二叉树进行先序线索化处理 */
    pre->rchild=Thrt; pre->rtag=1;
    Thrt->rchild=pre;                          /* 序列中最后一个结点与头结点相互连接 */
  }
  return Thrt;
}

PreThreading(BiThrTree *p)
{ if(p)
  { if(!p->lchild)
    { p->ltag=1;p->lchild=pre;}   /* 若当前结点左指针为空，则处理前驱线索 */
    else p->ltag=0;
    if(!pre->rchild)
    { pre->rtag=1;pre->rchild=p;} /* 若前驱结点右指针为空，则处理后继线索 */
    else pre->rtag=0;
    pre=p;	                  /* 前驱结点指针后移 */
    if(p->ltag==0)
    PreThreading(p->lchild);      /* 左子树线索化处理 */
    if(p->rtag==0)
    PreThreading(p->rchild);      /* 右子树线索化处理 */
  }
}





/*  教材习题5-4-4 编制算法对先序线索二叉树进行先序后继线索遍历*/
prethrt1(BiThrTree *Thrt)
{
  BiThrTree *p=Thrt->lchild;
  while(p!=Thrt)
  { while(p->ltag==0)
    { printf("%c  ",p->data);
      p=p->lchild;
    }
    printf("%c  ",p->data);
    p=p->rchild;
    while(p->rtag==1&&p->rchild!=Thrt)
    { printf("%c  ",p->data);p=p->rchild;}

  }
}



main()
{ BiThrTree *t,*Thrt;
  printf("input data:");
  t=creatree();                     /* 建立二叉链表 */
  getchar();                        /* 取出回车符 */
  Thrt=PreOrderThreading(t);        /* 先序线索化 */

  prethrt1(Thrt);                   /*  教材习题5-4-4 对先序线索二叉树进行先序后继线索遍历 */
  printf("\n");
}