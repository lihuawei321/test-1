#include "stdio.h"
#define MAXSIZE 100  /* 栈初始空间大小 */
typedef int ElemType;
typedef struct
{ ElemType *base;    /* 栈底指针 */
  ElemType *top;     /* 栈顶指针 */
}qstack;             /* 栈的类型 */



/* 初始化操作(创建一个空栈S) */
void initstack(qstack *S)
{ S->base=(ElemType *)malloc(MAXSIZE*sizeof(ElemType));/* 申请存储空间 */
  S->top=S->base;                     /* 栈顶指针初始值为基地址  */
}


/* 求栈长操作(返回栈S的元素个数，即栈的长度) */
int getlen(qstack *S)
{
  return (S->top-S->base);
}


/* 取栈顶元素操作(取出栈S的栈顶元素的值) */
int gettop(qstack *S,ElemType *e)
{ if(S->top==S->base) return 0;     /* 栈空,返回0 */
  *e=*(S->top-1);                   /* 栈顶元素值存入指针e所指向的内存单元 */
  return 1;                         /* 取栈顶元素成功,返回1 */
}


/* 入栈操作(将值为x的数据元素插入到栈S中，使之成为栈顶元素) */
push(qstack *S, ElemType x)
{ if(S->top==S->base+MAXSIZE)          /* 栈满 */
     return 0;
   *(S->top)=x;
   S->top++;
   return 1;
}



/* 出栈操作(取出栈S的栈顶元素) */
pop(qstack *S, ElemType *e)
{  if(S->top==S->base)  /* 栈空 */
   return 0;
   S->top--;
   *e=*(S->top);
   return 1;
}



/*  输出栈操作(输出自栈顶到栈底的元素值) */
void list(qstack *S)
{ ElemType *p;
  for(p=S->top-1;p>=S->base;p--)
    printf("%4d",*p);
}


main()
{ qstack S;
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
  i=pop(&S,&x);                         /* 出栈 */
  if(i) printf("%4d\n",x);
  list(&S);
}