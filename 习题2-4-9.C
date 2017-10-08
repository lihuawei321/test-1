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


/* 教材习题2-4-9 已知三个单连表A、B和C中的结点均依元素值自小至大非递减排列(可能存在两个以上值相同的结点)，编写算法对A链表进行如下操作：使操作后的链表A中仅留下3个表中均包含的数据元素的结点，且没有值相同的结点，并释放所有无用结点。*/
void public(slink *ha,slink *hb,slink *hc)
{ slink *pa,*pb,*pc,*q,*r;
  pa=ha->next;
  while(pa->next!=NULL)      /* 在ha中删除值相同的结点 */
  { q=pa->next;
    if(pa->data==q->data)
    { pa->next=q->next;
      free(q);
    }
    pa=pa->next;
  }
  pa->next=NULL;
  pa=ha->next;
  r=ha;r->next=NULL;
  pb=hb->next;pc=hc->next;
  while(pa!=NULL)                               /* 对ha中的每个结点，分别在hb和hc查找与其值相同的结点 */
  { while(pb!=NULL&&pa->data>pb->data)
    pb=pb->next;
    while(pc!=NULL&&pa->data>pc->data)
      pc=pc->next;
    if(pa->data==pb->data&&pa->data==pc->data)  /* 若在hb和hc中同时存在，保留 */
    { r->next=pa;
      r=pa;
      pa=pa->next;
      r->next=NULL;
    }
    else                                        /* 否则，删除 */ 
    { q=pa;
      pa=pa->next;
      free(q);
    }
  }
 }


main()
{ slink *A,*B,*C;
  int n;

  printf("input length of link A:");
  scanf("%d",&n);
  printf("input %d data:",n);
  A=creslink(n);		    /* 创建含有n个元素的带头结点的单链表A */

  printf("input length of link B:");
  scanf("%d",&n);
  printf("input %d data:",n);
  B=creslink(n);		    /* 创建含有n个元素的带头结点的单链表B */

  printf("input length of link C:");
  scanf("%d",&n);
  printf("input %d data:",n);
  C=creslink(n);		    /* 创建含有n个元素的带头结点的单链表C */

  public(A,B,C);                    /* 只将三个链表均含有的数据留在A中 */

  list(A);                          /* 输出三个链表均含有的数据 */

}