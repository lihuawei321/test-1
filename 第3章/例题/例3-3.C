#include "stdio.h"
#define INITSIZE 100       /* 存储空间的初始分配量 */

typedef struct
{ int no;                  /* n值 */
  double val;              /* P值 */
}ElemType;                 /* 栈中的数据元素为结构体类型 */

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



/* 判栈空操作(判断栈S是否为空) */
int emptystack(sqstack *S)
{ if(S->top==0) return 1;      /* 栈空,返回1,否则返回0 */
  else return 0;
}


/*【例3.3】利用一个栈实现下列函数的非递归计算
      1  n=0
Pn(x)=2x n=1
      2xPn-1(x)-2(n-1)Pn-2(x) n>1
*/


float p(int n,float x)
{ float fv1,fv2;
  int i;
  sqstack S;
  initstack(&S);
  for(i=n;i>=2;i--) S.base[S.top++].no=i;
  fv1=1;fv2=2*x;
  while(!emptystack(&S))    /* 若栈不空,则计算各个P值 */
  { S.base[--S.top].val=2*x*fv2-2*(S.base[S.top].no-1)*fv1;
    fv1=fv2;
    fv2=S.base[S.top].val;
  }
  return fv2;               /* 返回最终结果 */
}


main()
{ int n;
  float x,f;
  printf("input n and x:");
  scanf("%d %f",&n,&x);
  f=p(n,x);                /* 计算 */
  printf("the resule is:%f",f);
}
