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


/* 【例2.6】编写算法，用带头结点单向链表实现集合操作A∪B，要求结果链表仍使用原来两个链表的存储空间，不另开辟存储空间 */
void bring(slink *la,slink *lb)
{ slink *l,*p,*q;
  l=lb->next;
  while(l!=NULL)
  { p=la;q=la->next;
    while(q!=NULL&&q->data!=l->data) /* 在la中查找lb中的数据元素 */
    { p=q;q=q->next;}
    if(q!=NULL)                      /* 若存在，则将其删除 */
    { p->next=q->next;
      free(q);
    }
    l=l->next;
  }
  for(l=la;l->next!=NULL;l=l->next); /* l指向单链表la的最后一个结点 */
  l->next=lb->next;                  /* 把单链表lb连接到单链表la的后面 */
  free(lb);
}





main()
{ slink *la,*lb;
  int n;

  printf("input length of link la:");
  scanf("%d",&n);
  printf("input %d data:",n);
  la=creslink(n);                   /* 创建含有n个元素的带头结点的单链表1a */

  printf("input length of link lb:");
  scanf("%d",&n);
  printf("input %d data:",n);
  lb=creslink(n);                   /* 创建含有n个元素的带头结点的单链表lb */

  list(la);                         /* 输出单链表la */
  list(lb);                         /* 输出单链表lb */

  bring(la,lb);                     /* 合并 */

  printf("the result are:");
  list(la);                         /* 输出连接后的单链表 */
}