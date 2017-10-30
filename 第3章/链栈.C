
typedef int ElemType;  /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;       /* 数据域 */
  struct node *next;   /* 指针域 */
}linkstack;



#include "stdio.h"
/* 初始化操作(创建一个带头结点的空栈S) */
linkstack *initstack()
{ linkstack *S;
  S=(linkstack *)malloc(sizeof(linkstack));
  S->next=NULL;
  return S;
}

/* 取栈顶元素操作(取出栈S的栈顶元素值) */
int gettop(linkstack *S,ElemType *e)
{ if(S->next==NULL) return 0;  /* 若栈空,返回0 */
  *e=S->next->data;            /* 否则,取栈顶元素 */
  return 1;
}


/* 求栈长操作(返回栈S的元素个数,即栈的长度) */
int getlen(linkstack *S)
{ linkstack *p; int i;
  p=S->next; i=0;
  while(p!=NULL)
  { i++; p=p->next;}
  return i;
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


/* 输出栈(输出栈S自栈顶到栈底的元素值)*/
void list(linkstack *S)
{ linkstack *p;
  p=S->next;
  while(p!=NULL)
  { printf("%4d ",p->data); 
    p=p->next;
  }
  printf("\n");
}





main()
{ linkstack *S;
  ElemType x;
  int i;

  S=initstack();                        /* 创建一个空栈 */

  printf("input datas(-1:end):");       /* 输入数据,-1作为结束标志 */
  scanf("%d",&x);
  while(x!=-1)
  { push(S,x);  		        /* 插入 */
    scanf("%d",&x);
  }
  printf("the data from top to bottom are:");
  list(S);                              /* 输出栈 */
  printf("\n");

  printf("length=%d\n",getlen(S));      /* 输出栈长度 */

  printf("top enement is:");
  i=gettop(S,&x);                       /* 取栈顶元素 */
  if(i) printf("%d\n",x);
 
  printf("pop a enement");
  i=pop(S,&x);
  if(i) printf("%4d\n",x);

  if(!emptystack(S)) printf("no empty! ");/* 判栈是否为空 */
  else printf("empty! ");
}
