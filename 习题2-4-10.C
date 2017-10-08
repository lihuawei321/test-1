#include "stdio.h"
typedef int ElemType;                /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;                     /* 数据域 */
  struct node *next;                 /* 指向后继结点的指针域 */
  struct node *prior;                /* 指向前驱结点的指针域 */
}dlink;


/* 建立单链表(创建一个含有n个结点的带头结点单链表head) */
dlink *credlink(int n)
{ dlink *head,*p,*s; int i;              /* p用于指向新链入结点,s用于指向新开辟结点 */
  p=head=(dlink *)malloc(sizeof(dlink)); /* 创建头结点 */
  for(i=1;i<=n;i++)
  { s=(dlink *)malloc(sizeof(dlink));    /* s指向新开辟结点 */
    scanf("%d",&s->data);                /* 新结点数据域赋值 */
    p->next=s;                           /* 将新结点连接到p所指结点的后面 */
    p=s;                                 /* p指向新链入结点 */
  }
  p->next=NULL;                          /* 尾结点的后继域置为空 */
  return head;                           /* 返回头指针 */
}


/* 输出操作(从两个方向输出带头结点双向循环链表head的各结点的值) */
 void list(dlink *head)
{ dlink *p;
  p=head->next;              /* 正向输出链表 */
  while(p!=head)
  { printf("%4d ",p->data);
     p=p->next;
  }
  printf("\n");
  p=head->prior;             /* 反向输出链表 */
  while(p!=head)
  { printf("%4d ",p->data);
     p=p->prior;
  }
  printf("\n");
}


/* 已知L是一个带头结点的单链表，其结点中含有prior、data和next三个域，其中data为数据域，next为指针域，其值为后继结点的地址，prior也为指针域，但值均为空(NULL)。试编写算法将此链表改成为双向循环链表 */
link(dlink *L)
{ dlink *p,*pre;
  pre=L;p=L->next;
  while(p!=NULL)
  { p->prior=pre;           /* 从第1个结点开始,为每个结点的前驱域赋值 */
    pre=p;
    p=p->next;
  }
  pre->next=L;              /* 尾结点后继域指向头结点 */
  L->prior=pre;             /* 头结点前驱域指向尾结点 */
}


main()
{ dlink *H;
  int n;
  printf("input the number of node:");
  scanf("%d",&n);
  printf("input %d data:",n);
  H=credlink(n);                     /* 创建双链表 */
  link(H);                           /* 将单链表改为双循环链表 */
  list(H);                           /* 输出双循环链表 */
}