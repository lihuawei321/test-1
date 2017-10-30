#include "stdio.h"
#define MAXCSIZE 100  /* 队列空间的初始分配量 */
typedef int ElemType; 
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


/*【例3.7】编写程序，从键盘输入一个整数序列a1，a2，…，an。若ai>0，则ai进队列；若ai<0，则队头元素出队列；当ai==0时算法结束。要求利用循环队列完成，并在异常情况下(如队空)打印错误信息 */

void fun(void)
{ cqueue cq;ElemType x;int i;
  initqueue(&cq);
  scanf("%d",&x);
  while(x!=0)           /* 当输入0时退出循环，同时算法结束 */
  { if(x>0)
    { if(!enqueue(&cq,x))
      { printf("The cycle queue is full!\n");break;}
    }
    else if(!outqueue(&cq,&x))
    { printf("The cycle queue is empty!\n");break;}
    scanf("%d",&x);
  }
  list(&cq);
}


main()
{
 fun();
}