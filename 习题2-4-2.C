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


/* 定位操作(查找元素x在单链表head中第一次出现的位置) */

slink *locate(slink *head,ElemType x) /* 返回指针 */
{ slink *p;
  p=head->next;
  while(p!=NULL&&p->data!=x)  /* 从第一个结点开始查找数据域值为x的结点 */
    p=p->next;
  return p;
}



/* 教材习题2-4-2 编写算法，删除单链表L中p所指向结点的前驱结点。*/

delp_prior(slink *L,slink *p)
{ slink *q1,*q2;
  if(p==L||p==L->next||p==NULL)     /* 参数p不合理 */
   printf("\nNo exist!");
  else
   { q1=L;q2=L->next;
     while(q2->next!=p)             /* q2指向p的前驱,q1指向q2的前驱 */
     { q1=q2;q2=q2->next;}
     q1->next=p;                    /* 删除q2 */
     free(q2);
   }
}



main()
{ slink *head,*p;
  int n;
  ElemType x;
  printf("input length of link head:");
  scanf("%d",&n);
  printf("input %d data:",n);
  head=creslink(n);                   /* 创建含有n个元素的带头结点的单链表head */

  list(head);                         /* 输出单链表head */

  printf("input the data to locate:");
  scanf("%d",&x);
  p=locate(head,x);                   /* 查找元素x在单链表head中第一次出现的位置(指针) */


  if(p) delp_prior(head,p);           /* 输出p的前驱 */
  printf("the result are:");
  list(head);                         /* 输出删除前驱后的单链表 */
}