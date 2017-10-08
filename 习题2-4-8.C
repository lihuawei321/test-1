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


/* 教材习题2-4-8 编写算法，将一个带头结点单链表中的结点按值由大到小的顺序重新连成一个单链表 */
slink *sort(slink *L1)                   
{ slink *L2,*p,*q,*s,*k;
  L2=(slink *)malloc(sizeof(slink));     /* 生成升序排序的链表的头结点 */
  L2->next=NULL;
  p=L1->next;
  while(p)                               /* 采用直接插入排序法 */
  { s=L2;q=L2->next;
    while(q&&q->data<p->data)
    { s=q;q=q->next;}
    k=(slink *)malloc(sizeof(slink));
    k->data=p->data;
    k->next=q;
    s->next=k;
    p=p->next;
  }
  return L2;
}



main()
{ slink *head,*h;
  int n;
  printf("input length of link head:");
  scanf("%d",&n);
  printf("input %d data:",n);
  head=creslink(n);                   /* 创建含有n个元素的带头结点的单链表head */
  printf("before sort:");
  list(head);                         /* 输出单链表head */

  h=sort(head);                       /* 排序 */

  printf("after sort::");
  list(h);                            /* 输出排序后的单链表 */
}