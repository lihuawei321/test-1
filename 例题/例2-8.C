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


/* 【例2.8】编写算法,将带头结点单链表head(结点数据域的值为整型)拆成一个奇数链表和一个偶数链表。要求结果链表仍使用原来链表的存储空间，不另开辟存储空间 */
slink *divide(slink *head)
{ slink *odd,*p,*q,*r;
  odd=(slink *)malloc(sizeof(slink));/* 创建偶数链表的头结点 */
  r=head->next;/* r用于遍历整个链表 */
  p=head;             /* head作为奇数链表的头指针,p用于连接奇数结点 */
  q=odd;              /* odd作为偶数链表的头指针,q用于连接偶数结点 */
  while(r!=NULL)      /* 判断原链表中每个结点数据域值的奇偶性 */
  { if(r->data%2!=0)  /* 连接到奇数链表 */
    { p->next=r;p=r;}
    else              /* 连接到偶数链表 */
    { q->next=r;q=r;}
    r=r->next;
  }
  p->next=q->next=NULL;   /* 两个单链表的尾结点指针域置为NULL */
  return odd;
}






main()
{ slink *la,*lb;
  int n;

  printf("input length of link la:");
  scanf("%d",&n);
  printf("input %d data:",n);
  la=creslink(n);                   /* 创建含有n个元素的带头结点的单链表1a */
  list(la);                         /* 输出单链表la */
 
  lb=divide(la);                    /* 拆分 */

  printf("the odd link are:");
  list(la);                         /* 输出拆分后的奇数链表 */
  printf("the even link are:");
  list(lb);                         /* 输出拆分后的偶数链表 */

}