
typedef char ElemType;
/* 二叉树的结点结构 */
struct node
{ ElemType data;
  struct node *fch;      /* 孩子 */
  struct node *nsib;     /* 兄弟 */
};

typedef struct node Tree;

#include "stdio.h"

/* 先序建立二叉树 */
Tree *creatree()
{ Tree *t;
  char ch;
  scanf("%c",&ch);
  if(ch==' ')
    t=NULL;
  else
    {
     t=(Tree *)malloc(sizeof(Tree));
     t->data=ch;
     t->fch=creatree();
     t->nsib=creatree();
     }
  return t;
}

/* 先序遍历二叉树的递归算法 */
void PreOrderTraverse(Tree *bt)
{ if(bt!=NULL)
  { printf("%c  ",bt->data);          /* 访问根结点 */
    PreOrderTraverse(bt->fch);        /* 遍历左子树 */
    PreOrderTraverse(bt->nsib);       /* 遍历右子树 */
  }
}

/* 中序遍历二叉树的递归算法*/
void InOrderTraverse(Tree *bt)
{ if(bt!=NULL)
  { InOrderTraverse(bt->fch);
    printf("%c  ",bt->data);
    InOrderTraverse(bt->nsib);
  }
}


/* 指导书【例5.30】编写算法，求以孩子兄弟表示法存储的森林的叶子结点数。 */
int Leaves(Tree *t)
{ int n=0;
  if(t)
  if(t->fch==NULL)            /* 若结点无孩子，则该结点必是叶子 */
    n+=(1+Leaves(t->nsib));/* 返回叶子结点和其兄弟子树中的叶子结点数 */
  else
    n+=(Leaves(t->fch)+Leaves(t->nsib)); /*孩子子树和兄弟子树中叶子数之和 */
  return n;
}



/* 指导书实验题目-10 以孩子兄弟链表为存储结构，请设计递归和非递归算法求树的深度 */

int height1(Tree *bt)     /* 递归求以孩子兄弟链表表示的树的深度 */
{ int hc,hs,h;
  if(bt==NULL) return 0;
  else if(!bt->fch) { h=height1(bt->nsib);return h>1?h:1;} /* 孩子空，查兄弟的深度 *、
       else  /* 结点既有孩子又有兄弟，高度取孩子高度+1和兄弟子树高度的大者 */
       { hc=height1(bt->fch); /* 第1个孩子树高 */
	 hs=height1(bt->nsib);/* 兄弟树高 */
	 return hc+1>hs?hc+1:hs;
       }
}


#define MAX 10
int height2(Tree *t)          /* 非递归遍历求以孩子兄弟链表表示的树的深度 */
{ Tree *Q[MAX],*p;
  int front=1,rear=1;         /* front,rear是队列Q的队头队尾元素的指针 */
  int last,h;                 /* last指向树中同层结点中最后一个结点，h是树的高度 */
  if(t==NULL)  return 0;
  else
  { last=1;
    h=0;
    Q[rear++]=t;
    while(front<=last)
    { p=Q[front++];       /* 队头出列 */
      while(p!=NULL)      /* 层次遍历 */
      { if(p->fch) Q[rear++]=p->fch; /* 第一个孩子入队 *、
        p=p->nsib; /* 同层兄弟指针后移 */
      }
     if(front>last)      /* 本层结束，深度加1（初始深度为0）*/
     { h++;last=rear;}   /* last再移到指向当前层最右一个结点 */
    }
    return h;
  }
}


/* 指导书自测试题四-3 统计树中叶子结点数 */
int fun(Tree *T)
{ int c;
  Tree *p;
  if(!T->fch) return 1;
  else
  {  c=0;
     for(p=T->fch;p;p=p->nsib)
     c+=fun(p);
     return c;
  }
}



main()
{
 Tree *t;
 t=creatree();
 PreOrderTraverse(t);
 printf("%d\n",fun(t));
}


