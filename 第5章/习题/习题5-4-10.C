
/* 二叉树的结点结构 */
typedef char ElemType;
#include "stdio.h"
struct tree
{ int data,hd,xd;
  struct tree *lchild,*rchild;
};




/* 先序建立二叉树*/

struct tree *CreBiTree(void)
{ struct tree *bt;ElemType x;
scanf("%c",&x);                /* 读入数据 */
  if(x==' ') bt=NULL;            /* 输入空格符,安排空指针 */
  else
  { bt=(struct tree *)malloc(sizeof(struct tree));
    bt->data=x;                  /* 生成新结点 */
    bt->hd=0;
    bt->xd=0;
    bt->lchild=CreBiTree();      /* 建立左子树 */
    bt->rchild=CreBiTree();      /* 建立右子树 */
  }
  return bt;                     /* 返回根结点的指针 */
}


/*先序遍历二叉树的递归算法*/
void PreOrder(struct tree *bt)
{ if(bt!=NULL)
  { printf("%c %d %d\n",bt->data,bt->hd,bt->xd);    /* 访问根结点 */
    PreOrder(bt->lchild);                           /* 先序遍历根结点的左子树 */
    PreOrder(bt->rchild);                           /* 先序遍历根结点的右子树 */
  }
}



/*教材习题5-4-10 */

count(struct tree *t)
{ int n=0;
  if(t!=NULL)
  { n++;
    n+=count(t->lchild);
    t->hd=n-1;
    n+=count(t->rchild);
    if(t->rchild==NULL)
     t->xd=t->hd;
    else t->xd=t->hd+1;
  }
  return n;
}



main()
{ struct tree *bt;
  int n;

  printf("input data:");
  bt=CreBiTree(); /* 可以图5.20(a)中的第1棵树为例，输入其对应的二叉树 */
  printf("before count:\n");
  PreOrder(bt);

  count(bt);
  printf("after count:\n");
  PreOrder(bt);

}


