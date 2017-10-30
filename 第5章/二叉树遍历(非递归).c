#include "stdio.h"

typedef char ElemType;

/* 二叉树结点结构 */
typedef struct tree
{ struct tree *lchild;
  struct tree *rchild;
  ElemType data;
} BitTree,*bittree;



/*  先序遍历、中序遍历和后序遍历时利用栈 */

/* 顺序栈结构 */
typedef struct
{ bittree *top;
  bittree *base;
  int size;
} stack;

#define s_l 100              /* 栈的最大长度 */


/* 建栈 */
InitStack(stack *s)
{
  s->base=(bittree *)malloc(s_l*sizeof(bittree));
  s->top=s->base;
  s->size=s_l;
}

/* 判栈空 */
EmptyStack(stack *S)
{ if(S->top==S->base) return 1;
  else return 0;
}

/* 压栈 */
stack *push(stack *s,BitTree *e)
{
 if(s->top-s->base>=s_l)
  printf("this stack is full\n");
 else
 {*s->top=e;s->top++;}
 return s;
}

/* 出栈 */
BitTree *pop(stack *s)
{ if(s->top==s->base)
  { printf("this stack is null\n"); return NULL;}
 else
  {s->top--;return(*s->top);}
}

/*  取栈顶元素 */
BitTree *gettop(stack *s)
{ if(s->top==s->base)
  { printf("this stack is null\n"); return NULL;}
  else
   return *(s->top-1);
}


/* 层次遍历时利用队列 */

#define MAXCSIZE 100                /* 队列最大长度 */

typedef struct
{ bittree *base;
  int front;
  int rear;
}Squeue;

/* 初始化操作(创建一个空队列q) */
void InitQueue(Squeue *q)
{ q->base=(bittree *)malloc(MAXCSIZE*sizeof(bittree));
  q->front=q->rear=0;
}

/* 入队列操作(在队列q的队尾插入值为x的元素) */
int InQueue(Squeue *q,BitTree *x)
{ int i;
  if(q->rear==MAXCSIZE)
    if(q->front==0) return 0;       /* 队满,返回0 */
    else
    { for(i=q->front;i<=q->rear-1;i++)
       q->base[i-1]=q->base[i];
      q->front--;
      q->base[q->rear-1]=x;
    }
  else
   q->base[q->rear++]=x;
  return 1;
}

/* 出队列操作(将顺序队列q的队头元素删除)*/
int OutQueue(Squeue *q,bittree *e)
{ int i;
  if(q->front==q->rear) return 0;   /* 队空 */
  *e=q->base[q->front];
  for(i=q->front+1;i<=q->rear-1;i++)
    q->base[i-1]=q->base[i];
  q->rear--;
  return 1;
}

/* 判队空操作(判断顺序队列q是否为空) */
int EmptyQueue(Squeue *q)
{ if(q->front==q->rear) return 1;
  else return 0;
}


/* 递归先序建立二叉树 */
BitTree *CreBiTree(void)
{ BitTree *bt; ElemType x;
  scanf("%c",&x);
  if(x==' ') bt=NULL;
  else
    { bt=(BitTree *)malloc(sizeof(BitTree));
      bt->data=x;
      bt->lchild=CreBiTree();
      bt->rchild=CreBiTree();
     }
  return bt;
}

/* 非递归先序遍历二叉树 */
void PreOrder(BitTree *T)
{ stack S; BitTree *p;
  InitStack(&S);                        /* 初始化一个栈 */
  push(&S,T);                           /* 根结点指针进栈 */
  while(!EmptyStack(&S))                /* 栈为空时算法结束 */
  { p=pop(&S);                          /* 弹栈，p指向(子树)根结点 */
    while(p)
    { printf("%c ",p->data);            /* 访问根结点 */
      if(p->rchild) push(&S,p->rchild); /* 非空的右指针进栈 */
      p=p->lchild;                      /* 沿着左指针访问，直到左指针为空为止 */
    }
  }
}

/* 非递归中序遍历算法 */
void InOrder(BitTree *T)
{ stack S;BitTree *p;
  InitStack(&S);                       /* 初始化一个栈 */
  p=T;                                 /* p指向根结点 */
  while(p||!EmptyStack(&S))            /* 当p为空且栈为空时算法结束 */
  { while(p)
    { push(&S,p);
      p=p->lchild;                     /* 沿左指针走，沿途经过的(子树)根结点指针进栈 */
    }
    p=pop(&S);
    printf("%c ",p->data);             /* 当左指针为空时弹栈并访问该结点(子树根结点) */
    p=p->rchild;                       /* 向右跳一步到右子树上继续进行遍历过程 */
  }
}


/* 非递归后序遍历算法 */
void PostOrder(BitTree *T)
{ stack S;
  BitTree *p,*q;
  InitStack(&S);
  p=T;q=NULL;
  while(p||!EmptyStack(&S))
  { if(p!=q)
    { while(p)
      { push(&S,p);                   /* p非空时，压栈 */
        if(p->lchild) p=p->lchild;   /* 沿左指针下移*/
	else p=p->rchild;            /*若左指针为空，则沿右指针下移 */
      }
    }
    if(EmptyStack(&S)) break;         /* 若栈空，则结束 */
    q=gettop(&S);                     /* 取栈顶指针送q，*/
    if(q->rchild==p)                 /* 若q的右指针为空(p为空时)或指向刚刚访问过的结点 */
    { p=pop(&S);                      /* 则弹栈并访问该结点 */
      printf("%c ",p->data);
    }
    else p=q->rchild;                /* 否则，沿q的右指针继续遍历访问 */
  }
}



/* 二叉树的非递归层次遍历算法 */
void levellist(BitTree *T)
{ Squeue Q; BitTree *p;
  InitQueue(&Q);                        /* 初始化空队列 */
  if(T) InQueue(&Q,T);                  /* 根结点指针入队列 */
  while(!EmptyQueue(&Q))
  { OutQueue(&Q,&p);                    /* 队头元素出队列 */
    printf("%2c",p->data);               /* 访问 */
    if(p->lchild) InQueue(&Q,p->lchild);/* 左子树根结点指针入队列 */
    if(p->rchild) InQueue(&Q,p->rchild);/* 右子树根结点指针入队列 */
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

  printf("LevelOrder result:");
  levellist(bt);
  printf("\n");
}