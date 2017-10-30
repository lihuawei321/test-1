#include "stdio.h"

typedef char ElemType;

/* ���������ṹ */
typedef struct tree
{ struct tree *lchild;
  struct tree *rchild;
  ElemType data;
} BitTree,*bittree;



/*  �����������������ͺ������ʱ����ջ */

/* ˳��ջ�ṹ */
typedef struct
{ bittree *top;
  bittree *base;
  int size;
} stack;

#define s_l 100              /* ջ����󳤶� */


/* ��ջ */
InitStack(stack *s)
{
  s->base=(bittree *)malloc(s_l*sizeof(bittree));
  s->top=s->base;
  s->size=s_l;
}

/* ��ջ�� */
EmptyStack(stack *S)
{ if(S->top==S->base) return 1;
  else return 0;
}

/* ѹջ */
stack *push(stack *s,BitTree *e)
{
 if(s->top-s->base>=s_l)
  printf("this stack is full\n");
 else
 {*s->top=e;s->top++;}
 return s;
}

/* ��ջ */
BitTree *pop(stack *s)
{ if(s->top==s->base)
  { printf("this stack is null\n"); return NULL;}
 else
  {s->top--;return(*s->top);}
}

/*  ȡջ��Ԫ�� */
BitTree *gettop(stack *s)
{ if(s->top==s->base)
  { printf("this stack is null\n"); return NULL;}
  else
   return *(s->top-1);
}


/* ��α���ʱ���ö��� */

#define MAXCSIZE 100                /* ������󳤶� */

typedef struct
{ bittree *base;
  int front;
  int rear;
}Squeue;

/* ��ʼ������(����һ���ն���q) */
void InitQueue(Squeue *q)
{ q->base=(bittree *)malloc(MAXCSIZE*sizeof(bittree));
  q->front=q->rear=0;
}

/* ����в���(�ڶ���q�Ķ�β����ֵΪx��Ԫ��) */
int InQueue(Squeue *q,BitTree *x)
{ int i;
  if(q->rear==MAXCSIZE)
    if(q->front==0) return 0;       /* ����,����0 */
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

/* �����в���(��˳�����q�Ķ�ͷԪ��ɾ��)*/
int OutQueue(Squeue *q,bittree *e)
{ int i;
  if(q->front==q->rear) return 0;   /* �ӿ� */
  *e=q->base[q->front];
  for(i=q->front+1;i<=q->rear-1;i++)
    q->base[i-1]=q->base[i];
  q->rear--;
  return 1;
}

/* �жӿղ���(�ж�˳�����q�Ƿ�Ϊ��) */
int EmptyQueue(Squeue *q)
{ if(q->front==q->rear) return 1;
  else return 0;
}


/* �ݹ������������� */
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

/* �ǵݹ�������������� */
void PreOrder(BitTree *T)
{ stack S; BitTree *p;
  InitStack(&S);                        /* ��ʼ��һ��ջ */
  push(&S,T);                           /* �����ָ���ջ */
  while(!EmptyStack(&S))                /* ջΪ��ʱ�㷨���� */
  { p=pop(&S);                          /* ��ջ��pָ��(����)����� */
    while(p)
    { printf("%c ",p->data);            /* ���ʸ���� */
      if(p->rchild) push(&S,p->rchild); /* �ǿյ���ָ���ջ */
      p=p->lchild;                      /* ������ָ����ʣ�ֱ����ָ��Ϊ��Ϊֹ */
    }
  }
}

/* �ǵݹ���������㷨 */
void InOrder(BitTree *T)
{ stack S;BitTree *p;
  InitStack(&S);                       /* ��ʼ��һ��ջ */
  p=T;                                 /* pָ������ */
  while(p||!EmptyStack(&S))            /* ��pΪ����ջΪ��ʱ�㷨���� */
  { while(p)
    { push(&S,p);
      p=p->lchild;                     /* ����ָ���ߣ���;������(����)�����ָ���ջ */
    }
    p=pop(&S);
    printf("%c ",p->data);             /* ����ָ��Ϊ��ʱ��ջ�����ʸý��(���������) */
    p=p->rchild;                       /* ������һ�����������ϼ������б������� */
  }
}


/* �ǵݹ��������㷨 */
void PostOrder(BitTree *T)
{ stack S;
  BitTree *p,*q;
  InitStack(&S);
  p=T;q=NULL;
  while(p||!EmptyStack(&S))
  { if(p!=q)
    { while(p)
      { push(&S,p);                   /* p�ǿ�ʱ��ѹջ */
        if(p->lchild) p=p->lchild;   /* ����ָ������*/
	else p=p->rchild;            /*����ָ��Ϊ�գ�������ָ������ */
      }
    }
    if(EmptyStack(&S)) break;         /* ��ջ�գ������ */
    q=gettop(&S);                     /* ȡջ��ָ����q��*/
    if(q->rchild==p)                 /* ��q����ָ��Ϊ��(pΪ��ʱ)��ָ��ոշ��ʹ��Ľ�� */
    { p=pop(&S);                      /* ��ջ�����ʸý�� */
      printf("%c ",p->data);
    }
    else p=q->rchild;                /* ������q����ָ������������� */
  }
}



/* �������ķǵݹ��α����㷨 */
void levellist(BitTree *T)
{ Squeue Q; BitTree *p;
  InitQueue(&Q);                        /* ��ʼ���ն��� */
  if(T) InQueue(&Q,T);                  /* �����ָ������� */
  while(!EmptyQueue(&Q))
  { OutQueue(&Q,&p);                    /* ��ͷԪ�س����� */
    printf("%2c",p->data);               /* ���� */
    if(p->lchild) InQueue(&Q,p->lchild);/* �����������ָ������� */
    if(p->rchild) InQueue(&Q,p->rchild);/* �����������ָ������� */
  }
}

 main()
{ BitTree *bt;

  printf("input data:");
  bt=CreBiTree();             /* ����ͼ5.13Ϊ�������������� */

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