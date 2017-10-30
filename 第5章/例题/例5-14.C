
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


/* 中序遍历二叉树的递归算法*/
void InOrder(BitTree *bt)
{ if(bt!=NULL)
  { InOrder(bt->lchild);     /* 中序遍历根结点的左子树 */
    printf("%c",bt->data);   /* 访问根结点 */
    InOrder(bt->rchild);     /* 中序遍历根结点的右子树 */
  }
}



/*教材【例5.14】删除值为x的结点，使得其左右子树的安排仍然满足原来的中序遍历序列 */
int find=0;
void search(BitTree *bt,ElemType x,BitTree **p,BitTree **f)
{ if(bt!=NULL&&!find)
    if(bt->data==x)
    { find=1;*p=bt;}
    else
    { *f=bt;
      search(bt->lchild,x,p,f);
      *f=bt;
      search(bt->rchild,x,p,f);
    }
}
/* 删除值为x结点的算法 */
void deltree(BitTree **bt,ElemType x)
{ BitTree *p,*f,*q,*s;
  p=f=NULL;
  search(*bt,x,&p,&f);             /* 查找 */
  if(p!=NULL)                      /* 存在 */
    if(p->lchild!=NULL)            /* 待删除结点p的左子树不空 */
    { q=p->lchild;
      s=q;
      while(s->rchild!=NULL)
      { q=s;s=s->rchild;}          /* 找到结点p的左子树中最右下的结点 */
      if(s!=q) q->rchild=s->lchild;
      else p->lchild=q->lchild;
      p->data=s->data;
      free(s);
    }
    else                           /* 待删除结点p的左子树为空  */
    { if(f!=NULL)
        if(p==f->lchild) f->lchild=p->rchild;
        else f->rchild=p->rchild;
      else *bt=(*bt)->rchild;
      free(p);
    }
  else printf("结点x在二叉树中不存在!\n");
}




main()
{ BitTree *bt,*p;
  ElemType x;
  printf("input data:");
  bt=CreBiTree();             /* 以图5.13为例建立二叉链表 */

  printf("InOrder result before delete:\n");
  InOrder(bt);
  printf("\n");

  printf("input x:");
  scanf("%*c%c",&x);
  deltree(&bt,x);
  if(find)
  { printf("InOrder result after delete:\n");
    InOrder(bt);
    printf("\n");
  }
}


