#include "stdio.h"

typedef char ElemType; 
typedef struct node
{ ElemType data;       /* 数据域 */
  struct node *next;   /* 指针域 */
}linkstack;            /* 链栈结点类型 */           


/* 初始化操作(创建一个带头结点的空栈S) */
linkstack *initstack()
{ linkstack *S;
  S=(linkstack *)malloc(sizeof(linkstack));
  S->next=NULL;
  return S;
}


/* 入栈操作(将值为x的数据元素插入栈S中,使x成为新的栈顶元素) */
int push(linkstack *S,ElemType x)
{ linkstack *p;
  p=(linkstack *)malloc(sizeof(linkstack));/* 申请存储空间 */
  if(!p) return 0;                         /* 若空间申请不成功,返回0 */
  p->data=x;
  p->next=S->next;                         /* 插入到头结点之后 */
  S->next=p;
  return 1;
}

/* 出栈操作(删除栈S的栈顶元素) */
int pop(linkstack *S,ElemType *e)
{ linkstack *p;
  if(S->next==NULL) return 0;  /* 栈空,删除失败,返回0 */
  p=S->next;
  *e=p->data;                  /* 栈顶结点值赋给e指针所指向的单元 */
  S->next=p->next;
  free(p);
  return 1;                    /* 出栈成功,返回1 */
}


/* 判栈空操作(判断栈S是否为空)*/
int emptystack(linkstack *S)
{ if(S->next==NULL) return 1;  /* 栈空,返回1,否则返回0 */
  else return 0;
}


/* 【例3.6】设计一个算法，判断一个字符串是否对称。若是，则返回1，否则返回0 */
int fsame(char *str)
{ ElemType x,same=1;
  int len,i;
  linkstack *S;
  S=initstack();                    /* 初始化空栈 */
  for(len=0;str[len]!='\0';len++);  /* 计算字符串长 */
  for(i=0;i<len/2;i++)
    push(S,str[i]);                 /* 字符串前半部分入栈 */
  for(i=(len+1)/2;i<len;i++)
  { pop(S,&x);
    if(x!=str[i])                   /* 对应字符比较 */
    { same=0;break;}
  }
  if(emptystack(S)&&same) return 1; /* 对称返回1,否则返回0 */
  else return 0;
}


main()
{ int n;
  char str[81];
  printf("input string:");
  gets(str);
  n=fsame(str);
  if(n==1) printf("YES\n");
  else printf("NO\n");
}
