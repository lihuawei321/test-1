#define MAXCSIZE 100  /* 队列空间的初始分配量 */
typedef int ElemType; /* 在实际应用中，根据需要定义所需的数据类型 */
typedef struct
{ ElemType *base;     /* 基地址 */
  int front;          /* 队头指针 */
  int rear;           /* 队尾指针 */
}cqueue;


/* 初始化操作(创建一个空循环队列cq) */
void initqueue(cqueue *cq)
{ cq->base=(ElemType *)malloc(MAXCSIZE*sizeof(ElemType)); /* 分配内存 */
  cq->front=cq->rear=0;                  /* 队头和队尾指针初始值都为0 */
}


/* 求队列长操作(循环队列中数据元素的个数) */
int getlen(cqueue *cq)
{ return((cq->rear-cq->front+MAXCSIZE)%MAXCSIZE);
}


/* 取队头元素操作(取出循环队列cq的队头元素值)*/
int getfront(cqueue *cq,ElemType *e)
{ if(cq->front==cq->rear) return 0;  /* 队空,返回0 */
  *e=cq->base[cq->front];            /* 取队头元素 */          
  return 1;
}


/* 入队列操作(在循环队列cq的队尾插入值为x的元素) */
int enqueue(cqueue *cq,ElemType x)
{ if((cq->rear+1)%MAXCSIZE==cq->front) return 0; /* 队满,返回0 */
  cq->base[cq->rear]=x;                          /* 入队列 */
  cq->rear=(cq->rear+1)%MAXCSIZE;                /* 修改队尾指针 */
  return 1;
}


/* 出队列操作(将循环队列cq的队头元素删除)*/
int outqueue(cqueue *cq,ElemType *e)
{ if(cq->front==cq->rear) return 0;        /* 队空,返回0 */  
  *e=cq->base[cq->front];                  /* 取队头元素 */          
  cq->front=(cq->front+1)%MAXCSIZE;        /* 修改队头指针 */
  return 1;
}


/* 判队空操作(判断循环队列cq是否为空) */
int emptyqueue(cqueue *cq)
{ if(cq->front==cq->rear) return 1;
  else return 0;
}

/* 输出操作(输出循环队列cq从队头到队尾的所有元素)*/
void list(cqueue *cq)
{ int i;
i=cq->front;
  while(i!=cq->rear)
  { printf("%4d ",cq->base[i]);
    i=(i+1)%MAXCSIZE;
  }
  printf("\n");
}


main()
{ cqueue CQ;
  ElemType x;
  int i;

  initqueue(&CQ);                       /* 创建一个空循环队列 */

  printf("input datas(-1:end):");       /* 输入数据,-1作为结束标志 */
  scanf("%d",&x);
  while(x!=-1)
  { enqueue(&CQ,x);  		        /* 入队 */
    scanf("%d",&x);
  }

  printf("the data from head to tail are:");
  list(&CQ);                            /* 输出循环队列 */
  printf("\n");

  printf("length=%d\n",getlen(&CQ));    /* 输出循环队列长度 */

  printf("head enement is:");
  i=getfront(&CQ,&x);                   /* 取队头元素 */
  if(i) printf("%d\n",x);

  printf("out queue a enement");
  i=outqueue(&CQ,&x);
  if(i) printf("%4d\n",x);

  if(!emptyqueue(&CQ)) printf("no empty! ");/* 判队列是否为空 */
  else printf("empty! ");

  printf("the data from head to tail are:");
  list(&CQ);                             /* 输出循环队列 */
  printf("\n");
  
}