#include "stdio.h"
typedef int ElemType;    /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;         /* 数据域 */
  struct node *next;     /* 指针域 */
}slink;  


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


/*【例2.11】由n个已按1,2,3,…,n编号的人围成一圈，从编号为1的人开始按1,2,3顺序循环报数，凡报到3者出圈，最后只留一人，问其编码是多少?(用带头结点单向循环链表实现) */
void onlyone(int n)
{ slink *head,*p,*q;
  int i,m,k;
  p=head=(slink *)malloc(sizeof(slink));
  for(i=1;i<=n;i++)
  { q=(slink *)malloc(sizeof(slink));
    q->data=i;
    p->next=q;
    p=q;
  }
  p->next=head;         /* 建立了一个值为编号的带头结点单向循环链表head */
  p=head;m=0;
  while(m<n-1)
  { k=0;
    while(k<3)
    { k++;q=p;p=p->next;
      if(p==head)
      { q=p;p=p->next;} /* 跳过头结点 */
    }
    q->next=p->next;    /* 删除p结点 */
    free(p);
    p=q;                /* 重新定位p指针 */
    m++;                /* 对删除的结点计数，当m=n-1时退出循环 */
  }
  list(head);           /* 检验链表中是否仅剩一个结点，若是，即为所求 */
}


main()
{ int n,i;
  printf("input n:");
  scanf("%d",&n);
  printf("the result is:");
  onlyone(n);
}
