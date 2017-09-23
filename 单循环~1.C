#include "stdio.h"
typedef int ElemType;    /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;         /* 数据域 */
  struct node *next;     /* 指针域 */
}slink;  

/* 建立单循环链表(创建一个含有n个结点的带头结点单向循环链表head) */
slink *cresclink(int n)
{ slink *head,*p,*s;/* head为头指针,p指向新链入结点,s指向新开辟结点 */
  int i;
  p=head=(slink *)malloc(sizeof(slink));/* 创建头结点 */
  for(i=1;i<=n;i++)
  { s=(slink *)malloc(sizeof(slink));    /* s指向新开辟结点 */
    scanf("%d",&s->data);                /* 新结点数据域赋值 */
    p->next=s;                           /* 将新结点连接到p所指结点的后面 */                      
    p=s;                                 /* p指向新链入结点 */
  }
  p->next=head;                          /* 尾结点的指针域指向头结点 */
  return head;                           /* 返回头指针 */
}


/* 求表长操作(返回单向循环链表head的表长) */
int getlen(slink *head)
{ int i;slink *p;
  p=head->next;i=0;
  while(p!=head)   /* 单链表中循环条件是：p!=NULL */
  { i++;
    p=p->next;
}
  return i;
}


/* 取元素操作(取出单向循环链表head的第i个结点的元素值) */
int getelem(slink *head,int i,ElemType *e)
{ int j;slink *p;
  if(i<1) return 0;                    /* 参数i不合理,返回0 */
  p=head->next;j=1;
  while(p!=head&&j<i)                  /* 单链表中循环条件是：p!=NULL&&j<i */
  { p=p->next;j++;}                    /* 从第1个结点开始查找第i个结点 */
  if(p==head) return 0;                /* i值超过链表的长度,返回0 */
  *e=p->data;
  return 1;                            /* 取元素成功,返回1 */
}



/* 定位操作(在单向循环链表head中查找第一个值为x的结点)*/

locate(slink *head,ElemType x) /* 返回位序 */
{ int i=1;
  slink *p=head->next;
  while(p!=head&&p->data!=x)   /* 单链表的循环条件是：p!=NULL&&p->data!=x */
  { p=p->next;i++;} 
  if(p!=head) return i;        /* 找到，返回位序 */
  else return 0;               /* 没找到，返回0 */
}



/* 删除操作(删除带头结点单向循环链表head中的第i个结点) */
int delete(slink *head,int i,ElemType *e)
{ slink *p,*q;int j;
  if(i<1) return 0;               /* 参数i不合理，返回0 */
  p=head;j=0;
  while(p->next!=head&&j<i-1)     /* 单链表的循环条件是：p->next!=NULL&&j<i-1 */
  { p=p->next;j++;}               /* 从第一个结点开始查找第i-1个结点,由p指向它 */
  if(p->next==head) return 0;     /* 参数i值超过链表的长度，返回0  */
  q=p->next;
  p->next=q->next;                /* 删除第i个结点 */
  *e=q->data;
  free(q);
  return 1;
}


/*  插入操作(在带头结点单向循环链表head中的第i个结点之前插入一个值为x的结点)*/
int insert(slink *head,int i,ElemType x)
{ slink *p,*q;int j;
  if(i<1) return 0;       /* 参数i不合理，返回0 */ 
  p=head;j=0;
  while(p->next!=head&&j<i-1)
  { p=p->next;j++;}       /* 从第一个结点开始查找第i-1个结点，p指向它 */
  if((p->next!=head)||(p->next==head&&j==i-1))
  { q=(slink *)malloc(sizeof(slink));    /* 创建data域为x的结点 */
    q->data=x;
    q->next=p->next;      /* q的指针域指向p结点的后继结点 */
    p->next=q;            /* p的指针域指向q结点，完成插入 */
    return 1;             /* 插入成功，返回1 */
  }
  else return 0;          /* 参数i值超过链表长度+1 ，返回0 */
}


/* 输出操作(输出带头结点单向循环链表head中的各结点值) */
void list(slink *head)
{ slink *p;
  p=head->next;
  while(p!=head)             /* 单链表的循环条件是：p!=NULL */
  { printf("%4d ",p->data);
    p=p->next;
  }
  printf("\n");
}


main()
{ slink *H;
  int n,i;
  ElemType x;
  printf("input the number of data:");
  scanf("%d",&n);
  printf("input %d data:",n);
  H=cresclink(n);                   /* 创建含有n个元素的带头结点的单循环链表 */
  list(H);                          /* 输出单循环链表 */
  printf("length=%d\n",getlen(H));  /* 输出长度 */

  printf("input the position of enement to get:");
  scanf("%d",&i);
  i=getelem(H,i,&x);                /* 取元素 */
  if(i) printf("the element is:%d\n",x);

  printf("input the data to locate:");
  scanf("%d",&x);
  i=locate(H,x);                    /* 定位 */
  printf("the position is:%d\n",i);

  printf("input the position of enement to delete:");
  scanf("%d",&i);
  delete(H,i,&x);                   /* 删除元素 */
  printf("the result are:");
  list(H);


  printf("input the position of enement to insert:");
  scanf("%d",&i);
  printf("input the data to insert:");
  scanf("%d",&x);
  insert(H,i,x);                    /* 插入元素 */
  printf("the result are:");
  list(H);
}