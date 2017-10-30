#include "stdio.h"

#define INITSIZE 100      /* 栈存储空间的初始分配量 */
typedef int ElemType;     
typedef struct
{ int top;                /* 栈顶指针 */
  ElemType *base;         /* 存放元素的动态数组空间 */
  int stacksize;          /* 当前栈空间的大小 */
}sqstack;                 


typedef struct node
{ ElemType data;         /* 数据域 */
  struct node *next;     /* 指针域 */
}slink;                  /* 单链表结点类型 */                



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


/* 建立一个单链表(创建一个含有n个元素的带头结点的单链表head) */
slink *creslink(int n)
{ slink *head,*p,*s;  /* p用于指向新链入结点,s用于指向新开辟结点 */
  int i;
  p=head=(slink *)malloc(sizeof(slink)); /* 创建头结点*/
  for(i=1;i<=n;i++)
  { s=(slink *)malloc(sizeof(slink));    /* s指向新开辟结点 */
    scanf("%d",&s->data);                /* 新结点数据域赋值 */
    p->next=s;                           /* 将新结点连接到p所指结点的后面 */
    p=s;                                 /* p指向新链入结点 */
  }
  p->next=NULL;                          /* 尾结点的指针域置为空 */
  return head;                           /* 返回头指针 */
}


/* 输出操作(输出带头结点的单链表head中的所有结点值) */
void list(slink *head)
{ slink *p;
  p=head->next;
  while(p!=NULL)
  { printf("%3d",p->data);
    p=p->next;
  }
  printf("\n");
}


/* 【例3.5】编写算法，利用栈将带头结点的单链表逆置 */
/* 方法二：将链表中的元素利用顺序栈交换顺序 */
void turnlink2(slink *head)
{ sqstack S;
  slink *p;
  initstack(&S);                   /* 初始化空栈 */
  p=head->next;
  while(p)
  { push(&S,p->data);p=p->next;}   /* 链表中元素依次入栈 */
  p=head->next;
  while(!emptystack(&S))
  { pop(&S,&p->data);p=p->next;}   /* 栈中元素依次出栈到链表中对应结点上 */
}


main()
{ slink *H;
  int n;
  printf("input the number of data:");
  scanf("%d",&n);
  printf("input %d data:",n);
  H=creslink(n);                   /* 创建含有n个元素的带头结点的单链表 */
  printf("original link:");
  list(H);                         /* 输出单链表 */
  turnlink2(H);
  printf("turn link:");
  list(H);
}