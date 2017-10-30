#include "stdio.h"
typedef int ElemType;  
typedef struct node
{ ElemType data;       /* 数据域 */
  struct node *next;   /* 指针域 */
}linkstack,slink;      /* 链栈结点类型与单链表结点类型相同 */



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


/* 编写算法，用链栈实现带头结点单链表逆置的操作 */
void turnlink3(slink *head)
{ linkstack *S;
  slink *p;
  S=initstack();
  p=head->next;
  while(p!=NULL)
  { push(S,p->data);
    p=p->next;
  }
  head->next=S->next;
  free(S);
}



main()
{ slink *H;
  int n;
  printf("input the number of data:");
  scanf("%d",&n);
  printf("input %d data:",n);
  H=creslink(n);                   /* 创建含有n个元素的带头结点的单链表 */
  
  printf("original link:");
  list(H);                         /* 输出逆置前的单链表 */
  
  turnlink3(H);                     
  printf("turned link:"); 
  list(H);                          /* 输出逆置后的单链表 */
}
