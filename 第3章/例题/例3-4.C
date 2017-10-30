#include "stdio.h"
#define INITSIZE 100    /* 存储空间的初始分配量 */
typedef char ElemType;  
typedef struct
{ int top;              /* 栈顶指针 */
  ElemType *base;       /* 存放元素的动态数组空间 */
  int stacksize;        /* 当前栈空间的大小 */
}sqstack;


/* 初始化操作(创建一个空栈S) */
void initstack(sqstack *S)
{ S->base=(ElemType *)malloc(INITSIZE*sizeof(ElemType));/* 申请存储空间 */
  S->top=0;                     /* 栈顶指针初始值为0  */
  S->stacksize=INITSIZE;        /* 容量为初始值 */
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



/* 【例3.4】设计一个算法，判断一个表达式中括号“（”与“）”、“[”与“]”、“{”与“}”是否匹配。若匹配，则返回1；否则返回0 */
int match(char *exps)
{ int i=0,nomatch=0;
 sqstack S;
 ElemType x;
  initstack(&S);                        /* 初始化空栈 */     
  while(!nomatch&&exps[i]!='\0')
  { switch(exps[i])
    { case '(':                         /* 当前字符为"("时,将其入栈 */
      case '[':                         /* 当前字符为"["时,将其入栈 */
      case '{':push(&S,exps[i]);break;  /* 当前字符为"{"时,将其入栈 */
      case ')':gettop(&S,&x);
               if(x=='(') pop(&S,&x);
               else nomatch=1;
               break;                   /* 判断栈顶是否是相匹配的括号"(" */
      case ']':gettop(&S,&x);
               if(x=='[') pop(&S,&x);
               else nomatch=1;
               break;                   /* 判断栈顶是否是相匹配的括号"[" */
      case '}':gettop(&S,&x);
               if(x=='{') pop(&S,&x);
               else nomatch=1;          /* 判断栈顶是否是相匹配的括号"{" */
    }
    i++;
  }
  if(emptystack(&S)&&!nomatch) return 1; /* 栈空且符号匹配，返回1 */
  else return 0;                        /* 否则返回0 */
}


main()
{ char str[81];
  int n;
  printf("input express:")
  gets(str);
  n=match(str);
  if(n==1) printf("match\n");
  else printf("nomatch\n");
}