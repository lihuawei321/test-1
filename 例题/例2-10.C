#include "stdio.h"
typedef int ElemType;                /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;                     /* 数据域 */
  struct node *next;                 /* 指向后继结点的指针域 */
  struct node *prior;                /* 指向前驱结点的指针域 */
}dlink;

/* 建立双链表(创建一个含有n个结点的带头结点双链表head) */
dlink *credlink(int n)
{ dlink *head,*p,*s; int i;/* p用于指向新链入结点,s用于指向新开辟结点 */
  p=head=(dlink *)malloc(sizeof(dlink)); /* 创建头结点 */
  for(i=1;i<=n;i++)
  { s=(dlink *)malloc(sizeof(dlink));    /* s指向新开辟结点 */
    scanf("%d",&s->data);                /* 新结点数据域赋值 */               
    s->prior=p;
    p->next=s;                           /* 将新结点连接到p所指结点的后面 */
    p=s;                                 /* p指向新链入结点 */
  }                                      
  p->next=head->prior=NULL;              /* 头结点的前驱域和尾结点的后继域置为空 */
  return head;                           /* 返回头指针 */
}


/* 输出操作(从两个方向输出双链表head中各结点的值)  */
void list(dlink *head)
{ dlink *p;
  p=head;
  while(p->next!=NULL)             /* 正向输出链表元素值 */
  { p=p->next;                     /* 同时将指针定位到尾结点 */
    printf("%4d ",p->data);
  }
  printf("\n");
  while(p!=head)                   /* 反向输出链表元素值 */
  { printf("%4d ",p->data);
    p=p->prior;
  }
  printf("\n");
}


/*【例2.10】有一个带头结点的双链表，其结点值为整数。设计一个算法，把所有值不小于0的结点放在所有值小于0的结点之前 */
void move(dlink *head)
{ ElemType temp; dlink *p,*q;
  p=head->next;                         /* p指向第1个结点 */
  for(q=head;q->next!=NULL;q=q->next);  /* q指向尾结点 */
  while(p!=q)
  { while(p!=q&&p->data>=0) p=p->next;  /* 从头向尾找负数 */
    while(p!=q&&q->data<0) q=q->prior;  /* 从尾向头找非负数 */
    if(p!=q)                            /* 若p与q未相遇，则交换 */
	{ temp=p->data;
      p->data=q->data;
      q->data=temp;  
	}
  }
}



main()
{ dlink *H;
  int n;
  printf("input the number of node:");
  scanf("%d",&n);
  printf("input %d data:",n);
  H=credlink(n);                     /* 创建双链表 */

  list(H);                           /* 输出双链表 */

  move(H);                           /* 调整元素位置 */
 
  list(H);                           /* 输出调整后的双链表 */
 }