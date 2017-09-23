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


/* 【例2.5】编写算法，将两个带头结点的非递减有序单向链表la和lb归并成一个非递减的有序单链表。要求结果链表仍使用原来两个链表的存储空间，不另开辟存储空间。表中允许有重复的数据 */
void merge(slink *la,slink *lb)
{ slink *pa,*pb,*pc;
  pa=la->next;pb=lb->next;
  pc=la;       /* 将la作为新链表的头指针，pc总是指向新链表的最后一个结点*/
  while(pa!=NULL&&pb!=NULL)
  { if(pa->data<=pb->data)
    { pc->next=pa;pa=pa->next;}    /* pa指向的结点连接到pc指向结点后 */
    else
    { pc->next=pb;pb=pb->next;}    /* pb指向的结点连接到pc指向结点后 */
    pc=pc->next;
  }
  if(pa!=NULL) pc->next=pa;        /* 若la表中还有剩余结点,则接入新表中 */
  else pc->next=pb;                /* 若lb表中还有剩余结点,则接入新表中 */
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

  merge(la,lb);                     /* 归并 */

  printf("the result are:");
  list(la);                         /* 输出连接后的单链表 */
}