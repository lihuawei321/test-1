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


/* 求表长操作(返回双链表head的长度) */
int getlen(dlink *head)
{ int i=0;dlink *p;
  p=head->next;
  while(p!=NULL)
  { i++;p=p->next;}
  return i;
}

/*取元素操作(取出双链表head中第i个结点的值) */
int getelem(dlink *head,int i,ElemType *e)
{ int j;dlink *p;
  if(i<1) return 0;       /* i值不合理,返回0 */
  p=head->next;j=1;
  while(p!=NULL&&j<i)     /* 从第1个结点开始查找第i个结点 */
  { p=p->next;j++;}
  if(p==NULL) return 0;   /* i值超出表长,返回0 */
  *e=p->data;             /* 保存结点值 */
  return 1;               /* 取元素成功,返回1 */
}


/* 定位操作(返回双链表head中第一个值为x的结点的位置) */
dlink *locate1(dlink *head,ElemType x) /* 返回指针 */
{ dlink *p;
  p=head->next;
  while(p!=NULL&&p->data!=x)  /* 从第一个结点开始查找值为x的结点 */
    p=p->next;
  return p;                   /* 没找到返回NULL，否则返回该结点的指针 */
}

locate(dlink *head,ElemType x)
{ int i=1;dlink *p=head->next;
  while(p!=NULL&&p->data!=x)  /* 从第一个结点开始查找值为x的结点 */
  { p=p->next;i++;}
  if(p) return i;             /* 找到,返回位序 */
  else return 0;              /* 没找到,返回0 */
} 


/* 删除操作(删除双链表head中的第i个结点) */
int delete(dlink *head,int i,ElemType *e)
{ dlink *p,*q;int j;
  if(i<1) return 0;           /* 参数i不合理,删除失败,返回0 */
  p=head;j=0;
  while(p->next!=NULL&&j<i-1)
  { p=p->next;j++;}     /* 从第1个结点开始查找第i-1个结点,由p指向它 */
  if(p->next==NULL) return 0; /* 参数i值超过表长,返回0 */
  q=p->next;                  /* q 指向第i个结点 */
  p->next=q->next;      
  if(q->next!=NULL) q->next->prior=p; /* 删除q指向的结点 */
  *e=q->data;
  free(q);                    /* 释放第i个结点占用的空间 */
  return 1;                   /* 删除成功,返回1 */
}


/* 插入操作(在双链表head中第i个结点之前插入一个值为x的结点)*/
int insert(dlink *head,int i,ElemType x)
{ dlink *p,*q;int j;
  if(i<1) return 0;     /* 参数i不合理,插入失败,返回0 */
  p=head;j=0;
  while(p!=NULL&&j<i-1)
  { p=p->next;j++;}     /* 从第1个结点开始查找第i-1个结点,p指向它 */
  if(p==NULL) return 0; /* 参数i值超过表长+1,插入失败,返回0 */
  q=(dlink *)malloc(sizeof(dlink));  /* 创建值为x的结点q */
  q->data=x;
  q->next=p->next;      /* 插入新结点 */
  q->prior=p;
  if(p->next!=NULL) p->next->prior=q; 
  p->next=q;
  return 1;             /* 插入成功,返回1 */
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



main()
{ dlink *H;
  int n,i;
  ElemType x;
  printf("input the number of node:");
  scanf("%d",&n);
  printf("input %d data:",n);
  H=credlink(n);                     /* 创建双链表 */

  list(H);                           /* 输出双链表 */

  printf("length=%d\n",getlen(H));   /* 输出双链表长度 */

  printf("input the position of element to get:");
  scanf("%d",&i);
  i=getelem(H,i,&x);                 /* 取元素 */
  if(i) printf("the data is %d:\n ",x);
  else printf("the data is not exist!\n");

  printf("input the data to locate:");
  scanf("%d",&x);
  i=locate(H,x);                     /* 定位 */
  if(i) printf("the position is %d:\n ",i);
  else printf("the position is not exist!\n");

  printf("input the position of element to delete:");
  scanf("%d",&i);                    /* 删除 */
  i=delete(H,i,&x);
  if(i)  list(H);                    /* 输出删除元素后双链表 */
  else printf("the position is not exist!\n");

  printf("input the position and element to insert:");
  scanf("%d%d",&i,&x);               
  i=insert(H,i,x);                   /* 删除 */
  if(i) list(H);                     /* 输出插入元素后双链表 */
  else printf("the position is not exist!\n");
 }

