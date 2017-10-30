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


/* 【例3.2】编写算法，用非递归方法计算n! */
long fac(int n)
{ long f=1; ElemType x; sqstack S;
  initstack(&S);            /* 初始化空栈 */
  while(n>0)
  { push(&S,n);n--;}        /* n至1依次入栈 */
  while(!emptystack(&S))
  {pop(&S,&x);f*=x;}        /* 1至n依次出栈并乘到初值为1的变量f上 */
  return f;
}



main()
{ long f;
  int n;
  printf("input n:");
  scanf("%d",&n);
  f=fac(n);                /* 求阶乘 */
  printf("%d!=%ld\n",n,f);
}
