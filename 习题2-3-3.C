#include "stdio.h"
typedef int ElemType;                /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;                     /* 数据域 */
  struct node *next;                 /* 指向后继结点的指针域 */
  struct node *prior;                /* 指向前驱结点的指针域 */
  int freq;                          /* 访问频度 */
}dlink;

/* 建立双链表(创建一个含有n个结点的带头结点双链表head) */
dlink *credlink(int n)
{ dlink *head,*p,*s; int i;/* p用于指向新链入结点,s用于指向新开辟结点 */
  p=head=(dlink *)malloc(sizeof(dlink)); /* 创建头结点 */
  for(i=1;i<=n;i++)
  { s=(dlink *)malloc(sizeof(dlink));    /* s指向新开辟结点 */
    scanf("%d",&s->data);                /* 新结点数据域赋值 */
    s->freq=0;                           /* 访问频率初始值为0 */
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
    printf("%3d %3d     ",p->data,p->freq);
  }
  printf("\n");
  while(p!=head)                   /* 反向输出链表元素值 */
  { printf("%3d %3d     ",p->data,p->freq);
    p=p->prior;
  }
  printf("\n");
}


/* 教材习题2-3-3 已知h是一个带头结点的双链表，每个结点有四个成员：指向前驱结点的指针prior、指向后继结点的指针next、存放数据的成员data和访问频度freq。所有结点的freq初始值为0。每当在双链表上进行一次locate(h,x)操作时，令元素值为x的结点的freq的值增1，并使此链表中结点保持按访问频度递减的顺序排列，以便使访问频度高的结点总是靠近表头 */
locate(dlink *h,ElemType x)
{ dlink *p=h->next,*q;
  while(p!=NULL&&p->data!=x) p=p->next;       /* while(p!=NULL&&     (7)     ) */
  if(p==NULL) return 0;
  else 
  { p->freq++;
    q=p->prior;
    while(q!=h&&q->freq<p->freq)              /* while(q!=h&&     (8)     ) */
    { p->prior=q->prior;
      p->prior->next=p;
      q->next=p->next;
      if(q->next!=NULL)                       /* if(     (9)      ) */
        q->next->prior=q;
      p->next=q;
      q->prior=p;
      q=p->prior;                             /*     (10)      ; */
    }
   }
   return 1;
}


main()
{ dlink *H;
  int n,i;
  ElemType x;
  printf("input the number of node:");
  scanf("%d",&n);
  printf("input %d data:",n);
  H=credlink(n);                     /* 创建双链表 */

  list(H);                           /* 输出双链表信息 */
  printf("input search data(-1:end):");
  scanf("%d",&x);
  while(x!=-1)
  { locate(H,x);                     /* 查找 */
    scanf("%d",&x);
  }
  list(H);                           /* 输出查找后的双链表信息 */
 }