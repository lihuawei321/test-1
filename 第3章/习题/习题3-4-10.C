#define MAXCSIZE 100
typedef int ElemType;
typedef struct
{ ElemType *base;
  int front;
  int rear;
}queue;

/* 初始化操作(创建一个空队列q) */
void initqueue(queue *q)
{ q->base=(ElemType *)malloc(MAXCSIZE*sizeof(ElemType));
  q->front=q->rear=0;
}

/* 求队列长操作(顺序队列中数据元素的个数) */
int getlen(queue *q)
{ return(q->rear-q->front);
}

/* 取队头元素操作(取出顺序队列q的队头元素值)*/

int getfront(queue *q,ElemType *e)
{ if(q->front==q->rear) return 0;
  *e=q->base[q->front];
  return 1;
}


/* 入队列操作(在队列q的队尾插入值为x的元素) */

int enqueue(queue *q,ElemType x)
{ int i;
  if(q->rear==MAXCSIZE)
    if(q->front==0) return 0;            /* 队满 */
    else
    { for(i=q->front;i<=q->rear-1;i++)   /* 前移 */
       q->base[i-1]=q->base[i];
      q->front--;
      q->base[q->rear-1]=x;
    }
  else
   q->base[q->rear++]=x;
  return 1;
}


/* 出队列操作(将顺序队列q的队头元素删除)*/
int outqueue(queue *q,ElemType *e)
{ int i;
  if(q->front==q->rear) return 0;      /* 队空 */
  *e=q->base[q->front];
  for(i=q->front+1;i<=q->rear-1;i++)   /* 前移 */
    q->base[i-1]=q->base[i];
  q->rear--;
  return 1;
}


/* 判队空操作(判断顺序队列q是否为空) */
int emptyqueue(queue *q)
{ if(q->front==q->rear) return 1;
  else return 0;
}

/* 输出操作(输出顺序队列q从队头到队尾的所有元素)*/
void list(queue *q)
{ int i;
  i=q->front;
  while(i!=q->rear)
  { printf("%4d ",q->base[i]);
    i=i+1;
  }
  printf("\n");
}



main()
{ queue Q;
  ElemType x;
  int i;

  initqueue(&Q);                          /* 创建一个空队列 */

  printf("input datas(-1:end):");         /* 输入数据,-1作为结束标志 */
  scanf("%d",&x);
  while(x!=-1)
  { enqueue(&Q,x);  		          /* 入队 */
    scanf("%d",&x);
  }

  printf("the data from head to tail are:");
  list(&Q);                               /* 输出队列 */
  printf("\n");

  printf("length=%d\n",getlen(&Q));       /* 输出队列长度 */

  printf("head enement is:");
  i=getfront(&Q,&x);                      /* 取队头元素 */
  if(i) printf("%d\n",x);

  printf("out queue a enement");
  i=outqueue(&Q,&x);
  if(i) printf("%4d\n",x);

  if(!emptyqueue(&Q)) printf("no empty! ");/* 判队列是否为空 */
  else printf("empty! ");

  printf("the data from head to tail are:");
  list(&Q);                                /* 输出队列 */
  printf("\n");
}