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


/*  输出栈操作(输出自栈顶到栈底的元素值) */
void list(sqstack *S)
{ int i;
  for(i=S->top-1;i>=0;i--)
    printf("%d",S->base[i]);
}


/*【例3.1】编写算法，将十进制正整数m转换成n(2≤n≤9)进制数 */
void conversion(int m,int n)
{ sqstack S;
  initstack(&S);
  while(m!=0)
  { push(&S,m%n); m=m/n;}       /* 余数入栈，商作为下一个被除数 */
  list(&S);                     /* 输出 */
}


main()
{ int m,n;
  printf("input m and n:");
  scanf("%d%d",&m,&n);
  printf("the result is:");
  conversion(m,n);              /* 进制转换 */
}