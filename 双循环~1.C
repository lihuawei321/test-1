#include "stdio.h"
typedef int ElemType; /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;      /* 数据域 */
  struct node *next;  /* 指向后继结点的指针域 */
  struct node *prior; /* 指向前驱结点的指针域 */
}dlink;


/* 建立双向循环链表(创建一个含有n个结点的带头结点双向循环链表head) */
dlink *credclink(int n)
{ dlink *head,*p,*s;int i;
  p=head=(dlink *)malloc(sizeof(dlink)); /* 创建头结点 */
  for(i=1;i<=n;i++)
  { s=(dlink *)malloc(sizeof(dlink));    /* s指向新开辟结点 */
    scanf("%d",&s->data);                
    s->prior=p;
    p->next=s;                           /* 将新结点连接到p所指结点的后面 */
    p=s;                                 /* p指向新链入结点 */
  }
  p->next=head;head->prior=p;            /* 首尾相连,构成循环 */
  return head;                           /* 返回头指针 */                
}



/* 求表长操作(计算双向循环链表head的表长)*/
int getlen(dlink *head)
{ int i=0;dlink *p;
  p=head->next;
  while(p!=head)          /* 双链表的循环条件是:p!=NULL */
  { i++;p=p->next;}
  return i;
}



/* 取元素操作(取出双向循环链表head的第i个结点的数据元素的值) */
int getelem(dlink *head,int i,ElemType *e)
{ int j;dlink *p;
  if(i<1) return 0;        /* i值不合理,返回0 */
  p=head->next;j=1;
  while(p!=head&&j<i)      /* 双链表的循环条件是:p!=NULL&&j<i */
  { p=p->next;j++;}        /* 从第1个结点开始查找第i个结点 */
  if(p==head) return 0;    /* 参数i值超出表长,返回0 */
  *e=p->data;              /* 保存结点值 */
  return 1;                /* 取元素成功，返回1 */
}
 


/* 定位操作(在带头结点双向循环链表中查找第一个值为x的结点)*/
locate(dlink *head,ElemType x)
{ int i=1;
  dlink *p=head->next;
  while(p!=head&&p->data!=x) /* 双链表的循环条件是:p!=NULL&&p->data!=x */
  { p=p->next;i++;}          /* 从第一个结点开始查找值为x的结点 */
  if(p!=head) return i;      /* 找到,返回位序 */
  else return 0;             /* 没找到,返回0 */
} 



/* 删除操作(删除带头结点的双向循环链表head中的第i个结点) */
int delete(dlink *head,int i,ElemType *e)
{ dlink *p,*q;int j;
  if(i<1) return 0;           /* 参数i不合理,删除失败,返回0 */
  p=head;j=0;
  while(p->next!=head&&j<i-1) /* 双链表的循环条件是:p->next!=NULL&&j<i-1 */ 
  { p=p->next;j++;}           /* 从第一个结点开始查找第i-1个结点，由p指向它 */
  if(p->next==head) return 0; /* 参数i值超过表长,返回0 */ 
  q=p->next;                  /* q 指向第i个结点 */
  p->next=q->next;
  q->next->prior=p;           /* 删除q指向的结点 */
  *e=q->data;
  free(q);
  return 1;                   /* 删除成功,返回1 */
}


/* 插入操作(在带头结点双向循环链表head的第i个结点之前插入一个值为x的结点)*/
int insert(dlink *head,int i,ElemType x)
{ dlink *p,*q;int j;
  if(i<1) return 0;           /* 参数i不合理,插入失败,返回0 */
  p=head;j=0;
  while(p->next!=head&&j<i-1)
  { p=p->next;j++;}           /* 从第一个结点开始查找第i-1个结点,p指向它 */
  if((p->next!=head)||(p->next==head&&j==i-1)) /* 插入位置合理 */
  { q=(dlink *)malloc(sizeof(dlink));          /* 创建值为x的结点q */
    q->data=x;
    q->next=p->next;
    q->prior=p;
    p->next->prior=q;
    p->next=q;                    /* 插入新结点 */
    return 1;                     /* 插入成功,返回1 */
  }                      
  else return 0;                  /* 参数i值超过表长+1,插入失败,返回0 */ 
}


/* 输出操作(从两个方向输出带头结点双向循环链表head的各结点的值)*/
 void list(dlink *head)
{ dlink *p;
  p=head->next;              /* 正向输出链表 */
  while(p!=head)             
  { printf("%4d ",p->data);
     p=p->next;
  }
  printf("\n");
  p=head->prior;             /* 反向输出链表 */
  while(p!=head)
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
  H=credclink(n);                    /* 创建双循环链表 */

  list(H);                           /* 输出双循环链表 */

  printf("length=%d\n",getlen(H));   /* 输出双循环链表长度 */

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
  if(i)  list(H);                    /* 输出删除元素后双循环链表 */
  else printf("the position is not exist!\n");

  printf("input the position and element to insert:");
  scanf("%d%d",&i,&x);               
  i=insert(H,i,x);                   /* 删除 */
  if(i) list(H);                     /* 输出插入元素后双循环链表 */
  else printf("the position is not exist!\n");
 }