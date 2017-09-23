#include "stdio.h"
typedef int ElemType;    /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;         /* 数据域 */
  struct node *next;     /* 指针域 */
}slink;                 


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


/* 【例2.4】编写算法，实现两个带头结点单向链表a和b的连接。要求结果链表仍使用原来两个链表的存储空间，不另开辟存储空间 */
void link(slink *a,slink *b)
{ slink *p;
  for(p=a;p->next!=NULL;p=p->next); /* p指向单链表a的最后一个结点 */
  p->next=b->next;                  /* 把单链表b连接到单链表a的后面 */
  free(b);
}



main()
{ slink *a,*b;
  int n;
 
  printf("input length of link a:");
  scanf("%d",&n);
  printf("input %d data:",n);
  a=creslink(n);                   /* 创建含有n个元素的带头结点的单链表a */

  printf("input length of link b:");
  scanf("%d",&n);
  printf("input %d data:",n);
  b=creslink(n);                   /* 创建含有n个元素的带头结点的单链表b */

  list(a);                         /* 输出单链表a */
  list(b);                         /* 输出单链表b */

  link(a,b);                       /* 连接 */

  printf("the result are:");
  list(a);                         /* 输出连接后的单链表 */
}