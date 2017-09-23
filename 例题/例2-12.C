#include "stdio.h"
typedef int ElemType; /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;      /* 数据域 */
  struct node *next;  /* 指向后继结点的指针域 */
  struct node *prior; /* 指向前驱结点的指针域 */
}dlink;


/* 输出操作(输出带头结点双向循环链表head的各结点的值)*/
 void list(dlink *head)
{ dlink *p;
  p=head->next;              /* 正向输出链表 */
  while(p!=head)             
  { printf("%4d ",p->data);
     p=p->next;
  }
  printf("\n");
}


/*【例2.12】将自然数1~m按由小到大的顺序沿顺时针方向围成一个圈，然后以1为起点，先沿顺时针方向数到第n个数将其划去，再沿逆时针方向数到第k个数将其划去，重复上述操作，直到剩下一个数为止。问最后剩下的是哪个数？(用带头结点双向循环链表实现)*/
void onlyone(int m,int n,int k)
{ dlink *head,*p,*q;
  int i;
  if(m<1||n<1||k<1){ printf("Error!\n");exit(0);} /* 参数不合理 */
  p=head=(dlink *)malloc(sizeof(dlink));          
  for(i=1;i<=m;i++)
  { q=(dlink *)malloc(sizeof(dlink));
    q->data=i;
    q->prior=p;
    p->next=q;
    p=q;
  }
  p->next=head; head->prior=p; /* 建立一个值为编号的带头结点双向循环链表head */
  p=head;
  while(m>1)
  { for(i=1;i<=n;i++)          /* 顺时针搜索第n个结点，用p指向它 */
    { q=p;p=p->next;
      if(p==head) { q=head;p=head->next;}
    }
    q->next=p->next;
    p->next->prior=q;
    free(p);
    p=q->next;
    m--;
    if(m>1)      /* 若链表中的结点数不为1，将p指向的结点删除，链表长度减1 */
    { for(i=1;i<=k;i++)        /* 逆时针搜索第k个结点，用p指向它 */
      { q=p;p=p->prior;
	if(p==head) {q=p;p=p->prior;}
      }
      q->prior=p->prior;
      p->prior->next=q;
      free(p);
      p=q->prior;
      m--;
    }
  }
  list(head);       /* 若链表中只有一个结点，该结点值即为所求，否则出错 */
}

main()
{ int m,n,k;
  printf("input m,n and k:");
  scanf("%d%d%d",&m,&n,&k);
  printf("the result is:");
  onlyone(m,n,k);
 }