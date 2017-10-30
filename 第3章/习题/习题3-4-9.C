#include "stdio.h"

#define MAXSIZE  100        /* 两栈共享的顺序存储空间 */
typedef int ElemType;       /* 数据元素类型 */
typedef struct
{ ElemType stack[MAXSIZE];  /* 栈空间 */
  int top[2];               /* top[0]和top[1]为两个栈顶指针 */
}stk;

stk s;                      /* 定义栈 */

/* 初始化操作 */
void initstack()
{ s.top[0]=-1;              /* 第1个栈的顶指针初始值为-1  */
  s.top[1]=MAXSIZE;         /* 第2个栈的顶指针初始值为MAXSIZE  */
}


/* 求栈长操作 */
int getlen(int i)
{ if(i==0) return s.top[0]+1;
  else return MAXSIZE-s.top[2];
}


/* 取栈顶元素操作 */
int gettop(int i,ElemType *e)
{ if(i==0)
    if(s.top[0]==-1) return 0;                   /* 栈空,返回0 */
    else { *e=s.stack[s.top[0]]; return 1;}      /* 栈顶元素值存入指针e所指向的内存单元 */
  else if(s.top[1]==MAXSIZE)  return 0;          /* 栈空,返回0 */ 
       else { *e=s.stack[s.top[1]]; return 1;}   /* 栈顶元素值存入指针e所指向的内存单元 */
}


/* 入栈操作(将值为x的数据元素插入到栈S中，使之成为栈顶元素) */
push(int i, ElemType x)  /* i为栈号,i=0表示左边的栈s1,i=1表示右边的栈s2,x是入栈元素 */
{ if(i<0||i>1) { printf("error\n");exit(0);}
  if(s.top[1]-s.top[0]==1) { printf("stack FULL\n"); return 0;}
   switch(i)
  { case 0: s.stack[++s.top[0]]=x; return 1;
    case 1: s.stack[--s.top[1]]=x; return 1;
  }
}


/* 出栈操作(取出栈S的栈顶元素) */
ElemType pop(int i)    /* i为栈号,i=0表示左边的栈s1,i=1表示右边的栈s2  */ 
{ if(i<0||i>1){ printf("error\n");exit(0);}
  switch(i)
  { case 0: if(s.top[0]==-1) { printf("stack null\n");return -1;}
            else return (s.stack[s.top[0]--]);
    case 1: if(s.top[1]==MAXSIZE) { printf("stack null\n"); return -1;}
            else return(s.stack[s.top[1]++]);
  }
}



/* 判栈空操作(判断栈S是否为空) */
int emptystack()
{ if(s.top[0]==-1&&s.top[1]==MAXSIZE) return 1;      /* 栈空,返回1,否则返回0 */
  else return 0;
}


/*  输出栈操作(输出自栈顶到栈底的元素值) */
void list()
{ int i;
  for(i=s.top[0];i>=0;i--)
    printf("%4d",s.stack[i]);
  printf("\n");
  
  for(i=s.top[1];i<MAXSIZE;i++)
    printf("%4d",s.stack[i]);
  printf("\n");

}


main()
{ ElemType x;
  int i;

  initstack();                         /* 创建一个空栈 */

  printf("input datas(0:end):");       /* 输入数据,-1作为结束标志 */
  scanf("%d",&x);
  while(x!=0)
  { if(x>0) push(0,x);  	       /* 大于0，入左栈 */
    else   push(1,x);                  /* 小于0，入右栈 */
    scanf("%d",&x);
  }

  list();                              /* 输出栈 */

  printf("pop a enement");
  x=pop(0);
  x=pop(1);

  list();                              /* 输出栈 */

}