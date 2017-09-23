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


/* 【例2.7】编写算法，实现带头结点单链表head逆置。要求结果链表仍使用原链表的存储空间，不另开辟存储空间 */
void turn(slink *head)
{ slink *p,*q;
  p=head->next;head->next=NULL; /* 置一个空链表head,p指向待插入结点 */
  while(p!=NULL) 
  { q=p->next;                  /* 保存待插入点的后继结点指针 */
    p->next=head->next;
    head->next=p;               /* 将p指向结点插入到头结点之后 */
    p=q;                        /* p指向待插入结点 */
  }
}






main()
{ slink *head;
  int n;
  printf("input length of link head:");
  scanf("%d",&n);
  printf("input %d data:",n);
  head=creslink(n);                   /* 创建含有n个元素的带头结点的单链表head */

  list(head);                         /* 输出单链表head */
  
  turn(head);                         /* 逆置 */

  printf("the result are:");
  list(head);                         /* 输出逆置后的单链表 */
}