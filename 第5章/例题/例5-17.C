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



/* 中序线索化处理算法,Thrt指向头结点 */
BiThrTree *pre;                                /* 指向遍历结点的前驱结点 */
BiThrTree *InOrderThreading(BiThrTree *T)
{ BiThrTree *Thrt;
  Thrt=(BiThrTree *)malloc(sizeof(BiThrTree));  /* 头结点 */
  Thrt->ltag=0; Thrt->rtag=1;Thrt->rchild=Thrt;
  if(!T) Thrt->lchild=Thrt;                 /* 若二叉树为空，则头结点自身构成一个循环链表 */
  else
  { Thrt->lchild=T; pre=Thrt;               /* 头结点的左指针指向根结点, pre指向头结点 */
    InThreading(T);                         /* 对二叉树进行中序线索化处理 */
    pre->rchild=Thrt; pre->rtag=1;
    Thrt->rchild=pre;                       /* 序列中最后一个结点与头结点相互连接 */

  }
  return Thrt;
}

InThreading(BiThrTree *p)
{ if(p)
  { InThreading(p->lchild);   /* 左子树线索化处理 */
    if(!p->lchild)            /* 若当前结点左指针为空，则处理前驱线索 */
    { p->ltag=1;p->lchild=pre;}
    else p->ltag=0;
    if(!pre->rchild)          /* 若前驱结点右指针为空，则处理后继线索 */
    { pre->rtag=1;pre->rchild=p;}
    else pre->rtag=0;
    pre=p;                    /* 前驱结点指针后移 */
    InThreading(p->rchild);   /* 右子树线索化处理 */
  }
}






/* 教材【例5.17】编制算法对中序线索二叉树进行中序前驱线索遍历*/
inorderthread2(BiThrTree *Thrt)
{ BiThrTree *p=Thrt->rchild;
  while(p!=Thrt)
  { while(p->rtag==0) p=p->rchild;          /* 右子树最右边结点 */
    printf("%c  ",p->data);
    while(p->ltag==1&&p->lchild!=Thrt)      /* 左链域为线索结点 */
    { p=p->lchild; printf("%c  ",p->data);}
    p=p->lchild;
  }
}


main()
{ BiThrTree *t,*Thrt;
  
  printf("input data:");
  t=creatree();                     /* 建立二叉链表 */
  getchar();                        /* 取出回车符 */
  Thrt=InOrderThreading(t);         /* 中序线索化 */


  printf("the result: ");
  inorderthread2(Thrt);             /* 对中序线索二叉树进行中序前驱线索遍历 */
  printf("\n");
}