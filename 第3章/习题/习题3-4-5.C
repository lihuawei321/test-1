#include "stdio.h"

typedef int ElemType; /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;      /* 数据域 */
  struct node *next;  /* 指针域 */
}qlink;               /* 结点类型定义 */
typedef struct
{ qlink *front;       /* 队头指针 */
  qlink *rear;        /* 队尾指针 */
}linkqueue;           /* 链队列类型定义 */



/* 初始化操作(建立空的链队列LQ) */
void initqueue(linkqueue *LQ)
{ LQ->front=LQ->rear=(qlink *)malloc(sizeof(qlink));/* 创建头结点 */
  LQ->front->next=NULL;
}


/* 入队列操作(在队列LQ中插入一个值为x的元素,使之成为新的队尾元素) */
void enqueue(linkqueue *LQ,ElemType x)
{ qlink *p;
  p=(qlink *)malloc(sizeof(qlink));  /* 创建新结点 */
  p->data=x;
  p->next=NULL;
  LQ->rear->next=p;                  /* 插入到链队列的尾部 */
  LQ->rear=p;
}
 

/* 出队操作(删除链队列中的队头结点) */
int outqueue(linkqueue *LQ,ElemType *e)
{ qlink *p;
  if(LQ->front==LQ->rear) return 0;  /* 队空,返回0 */
  p=LQ->front->next;
  *e=p->data;
  LQ->front->next=p->next;
  if(LQ->rear==p)  /* 当队中只有一个元素时,出队后应重新修改队尾指针rear */
    LQ->rear=LQ->front;
  free(p);
  return 1;
}


/* 判队空操作(判断链队列是否为空) */
int emptyqueue(linkqueue *LQ)
{ if(LQ->front==LQ->rear) return 1;   /* 队空的条件为:front==rear */
  else return 0;
}


/* 输出队列操作(输出链队列从队头至队尾的所有元素) */
void list(linkqueue *LQ)
{ qlink *p;
  p=LQ->front->next;
  while(p!=NULL)
  { printf("%4d",p->data);
    p=p->next;
  }
}



/* 教材习题3-4-5 已知一个整数队列，编写算法，将所有的值为x的整数出队列，其他数据保持原来的先后顺序关系 */
linkqueue delx(linkqueue *Q,int x)
{ linkqueue Q1;
  int e;
  initqueue(&Q1);
  while(!emptyqueue(Q))
  { outqueue(Q,&e);
    if(e!=x)
      enqueue(&Q1,e);
  }
  return Q1;
}



main()
{ linkqueue LQ;
  int x;
  initqueue(&LQ);                       /* 创建一个空链队列 */

  printf("input datas(-1:end):");       /* 输入数据,-1作为结束标志 */
  scanf("%d",&x);
  while(x!=-1)
  { enqueue(&LQ,x);  		        /* 入队 */
    scanf("%d",&x);
  }

  printf("the data from head to tail are:");
  list(&LQ);                            /* 输出链队列 */
  printf("\n");

  printf("input the deleted element:");
  scanf("%d",&x);
  LQ=delx(&LQ,x);

  printf("the data from head to tail are:");
  list(&LQ);                             /* 输出链队列 */
  printf("\n");

}