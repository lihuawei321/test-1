#include "stdio.h"
#define INITSIZE 100 /* 存储空间的初始分配量 */
typedef int ElemType;/* 在实际应用中，根据需要定义所需的数据类型 */
typedef struct
{ int top;           /* 栈顶指针，也可以定义成地址指针的形式:ElemType *top */
  ElemType *base;    /* 存放元素的动态数组空间 */
  int stacksize;     /* 当前栈空间的大小 */
}sqstack;


/* 初始化操作(创建一个空栈S) */
void initstack(sqstack *S)
{ S->base=(ElemType *)malloc(INITSIZE*sizeof(ElemType));/* 申请存储空间 */
  S->top=0;                     /* 栈顶指针初始值为0  */
  S->stacksize=INITSIZE;        /* 容量为初始值 */
}


/* 求栈长操作(返回栈S的元素个数，即栈的长度) */
int getlen(sqstack *S)
{
  return (S->top);
}


/* 取栈顶元素操作(取出栈S的栈顶元素的值) */
int gettop(sqstack *S,ElemType *e)
{ if(S->top==0) return 0;     /* 栈空,返回0 */
  *e=S->base[S->top-1];       /* 栈顶元素值存入指针e所指向的内存单元 */
  return 1;                   /* 取栈顶元素成功,返回1 */ 
}


/* 入栈操作(将值为x的数据元素插入到栈S中，使之成为栈顶元素) */
int push(sqstack *S,ElemType x)
{ if(S->top>=S->stacksize)   /* 若栈满，则增加一个存储单元 */
  { S->base=(ElemType *)realloc(S->base,(S->stacksize+1)*sizeof(ElemType));
    if(!S->base) return 0;   /* 空间分配不成功,返回0 */
    S->stacksize++;
  }
  S->base[S->top++]=x;       /* 插入元素后,栈顶指针上移 */
  return 1; }


/* 出栈操作(取出栈S的栈顶元素) */
int pop(sqstack *S,ElemType *e)
{ if(S->top==0) return 0;      /* 栈空,返回0 */
  *e=S->base[--S->top];        /* 先将指针减1,再返回栈顶元素值 */
  return 1;                    /* 弹栈成功,返回1 */
}


/* 判栈空操作(判断栈S是否为空) */
int emptystack(sqstack *S)
{ if(S->top==0) return 1;      /* 栈空,返回1,否则返回0 */
  else return 0;
}


/*  输出栈操作(输出自栈顶到栈底的元素值) */
void list(sqstack *S)
{ int i;
  for(i=S->top-1;i>=0;i--)
    printf("%4d",S->base[i]);
}


main()
{ sqstack S;
  ElemType x;
  int i;

  initstack(&S);                        /* 创建一个空栈 */

  printf("input datas(-1:end):");       /* 输入数据,-1作为结束标志 */
  scanf("%d",&x);
  while(x!=-1)
  { push(&S,x);  		        /* 入栈 */
    scanf("%d",&x);
  }
  printf("the data from top to bottom are:");
  list(&S);                             /* 输出栈 */
  printf("\n");

  printf("length=%d\n",getlen(&S));     /* 输出栈长度 */

  printf("top enement is:");
  i=gettop(&S,&x);                      /* 取栈顶元素 */
  if(i) printf("%d\n",x);
 
  printf("pop a enement");
  i=pop(&S,&x);
  if(i) printf("%4d\n",x);

  if(!emptystack(&S)) printf("no empty! ");/* 判栈是否为空 */
  else printf("empty! ");

}