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
  return 1; 
}


/* 出栈操作(取出栈S的栈顶元素) */
int pop(sqstack *S,ElemType *e)
{ if(S->top==0) return 0;      /* 栈空,返回0 */
  *e=S->base[--S->top];        /* 先将指针减1,再返回栈顶元素值 */
  return 1;                    /* 弹栈成功,返回1 */
}


/* 判栈空操作(判断栈S是否为空) */
int empty(sqstack *S)
{ if(S->top==0) return 1;      /* 栈空,返回1,否则返回0 */
  else return 0;
}


/* 已知压栈函数push(s,x)，弹栈函数pop(s,e)，初始化栈函数initstack(s)，判栈空函数为empty(s)。编写算法，将任意一个十进制整数转换为任意进制数输出 */
jzzh(int m, int n)    
{  int e;
   sqstack S;
   initstack(&S);
   while(m!=0)
   { push(&S,m%n); m=m/n;}
   while(!empty(&S))
   { pop(&S,&e);
     printf("%d",e);
   }
}


main()
{ int m,n;
  printf("input m and n:");
  scanf("%d%d",&m,&n);
  printf("the result is:");
  jzzh(m,n);              /* 进制转换 */
}