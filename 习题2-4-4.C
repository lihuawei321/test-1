#include "stdio.h"
typedef int ElemType;    /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;         /* 数据域 */
  struct node *next;     /* 指针域 */
}slink;                 


/* 建立一个单链表(创建一个含有n个元素的不带头结点的单链表head) */
slink *initlist(int n)
{ slink *head,*p,*s;
  int i;
  p=head=NULL;
  for(i=1;i<=n;i++)
  { s=(slink *)malloc(sizeof(slink));
    scanf("%d",&s->data);
    if(i==1) {p=s;head=s;}
    else
    { p->next=s;
      p=s;
    }
  }
  p->next=NULL;                         /* 尾结点的指针域置为空 */
  return head;
}


/* 输出操作(输出不带头结点的单链表head中的所有结点值) */
void list(slink *head)
{ slink *p;
  p=head;
  while(p!=NULL)
  { printf("%3d",p->data);
    p=p->next;
  }
  printf("\n");
}




/* 教材习题2-4-4 编写算法，在不带头结点的单链表上实现插入和删除操作 */

/* (1)在单链表head的第i个结点之后插入一个新结点 */

slink *insnode(slink *head,int i)
{ slink *s,*p,*q;
  int j=0;
  if(i<0) printf("position not exist\n");   /* 参数i不合理 */
  else
  { s=(slink *)malloc(sizeof(slink));
    printf("input the data to insert:");
    scanf("%d",&s->data);
    if(i==0)                                /* 在第1个结点前插入 */
    { s->next=head;
      head=s;
    }
    else                                    /* 找插入位置 */
    { q=head;
      while(j<i&&q!=NULL)
      { j++;
	p=q;
	q=q->next;
      }
      if(j<i) printf("position not exist\n");/* 参数i不合理 */
      else                                   /* 插入 */
      { p->next=s;
	s->next=q;
      }
    }
  }
  return head;
}

/* (2)删除单链表head的第i个结点 */
slink *delnode(slink *head,int i)
{ slink *p,*s;
  int j;
  if(i<1) printf("position not exist\n");      /* 参数i不合理 */
  else
  { if(i==1)                                   /* 删除的结点时第1个结点 */
    { if(head!=NULL)
      { s=head;
	head=s->next;
	free(s);
      }
    }
    else                                       /* 找删除位置 */
    { s=head->next;
      p=head;
      j=2;
      while(j<i&&s!=NULL)
      { j++;p=s;s=s->next;}
      if(j<i) printf("position not exist\n");  /* 参数i不合理 */
      else                                     /* 删除 */
      { p->next=s->next;
	free(s);
      }
    }
  }
  return head;
}



main()
{ slink *head,*p;
  int n,i;
  ElemType x;
  printf("input length of link head:");
  scanf("%d",&n);
  printf("input %d data:",n);
  head=initlist(n);                   /* 创建含有n个元素的不带头结点的单链表head */

  list(head);                         /* 输出单链表 */

  printf("input the position to insert:");
  scanf("%d",&i);
  head=insnode(head,i);               /* 插入 */
  list(head);                         /* 输出插入新结点后单链表 */

  printf("input the position to delete:");
  scanf("%d",&i);
  head=delnode(head,i);               /* 插入 */
  list(head);                         /* 输出删除结点后的单链表 */
}