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


/* 教材习题2-4-7 编写算法，在一个带头结点的单链表的第i个结点之前插入另一个带头结点的单链表 */
L1insL2(slink *L1,int i,slink *L2)
{ slink *p,*q,*k,*s;
  int j;
  if(L2->next==NULL) return 0; /* L2为空链表 */
  if(i<1) return 0;            /* 参数i不正确 */
  p=L1;j=0;
  while(p!=NULL&&j<i-1)
  { p=p->next;j++;}            /* 从L1的第一个结点开始查找第i-1个结点,由p指向它 */
  if(p==NULL) return 0;        /* i值超过链表长度+1 */
  s=p->next;                   /* s指向L1的第i个结点 */
  q=L2->next;
  while(q)                     /* 复制L2到p的后面 */
  { k=(slink *)malloc(sizeof(slink));
    k->data=q->data;
    p->next=k;
    p=p->next;
    q=q->next;
  }
  p->next=s;
}



main()
{ slink *a,*b;
  int n,i;
 
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

  printf("input the position to insert ");
  scanf("%d",&i);
  L1insL2(a,i,b);                  /* 在a的第i个结点前插入b */

  printf("the result is:");
  list(a);                         /* 输出插入后的单链表 */
}