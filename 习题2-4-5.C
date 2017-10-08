#include "stdio.h"
typedef int ElemType;                /* 在实际问题中,可以根据需要定义所需的数据类型 */
typedef struct node
{ ElemType data;                     /* 数据域 */
  struct node *next;                 /* 指向后继结点的指针域 */
  struct node *prior;                /* 指向前驱结点的指针域 */
}dlink;

/* 建立双链表(创建一个含有n个结点的不带头结点双链表head) */
dlink *credlink(int n)
{ dlink *head,*p,*s; /* p用于指向新链入结点,s用于指向新开辟结点 */
  int i;
  p=head=NULL;
  for(i=1;i<=n;i++)
  { s=(dlink *)malloc(sizeof(dlink));    /* s指向新开辟结点 */
    scanf("%d",&s->data);                /* 新结点数据域赋值 */
    if(i==1) {p=s;head=s;}
    else
    { s->prior=p;
      p->next=s;                         /* 将新结点连接到p所指结点的后面 */
      p=s;                               /* p指向新链入结点 */
    }
  }
  p->next=head->prior=NULL;              /* 首结点的前驱域和尾结点的后继域置为空 */
  return head;                           /* 返回头指针 */
}



/* 输出操作(输出不带头结点双链表head中各结点的值)  */
void list(dlink *head)
{ dlink *p;
  p=head;
  while(p!=NULL)                   /* 正向输出链表元素值 */
  { printf("%4d ",p->data);
    p=p->next;
  }
  printf("\n");
}

/* 教材习题2-4-5 编写算法，在不带头结点的双向链表上实现插入和删除操作。*/

/* (1)在双向链表head的第i个结点之后插入一个新结点。*/
dlink *insnode(dlink *head,int i)
{ dlink *s,*p,*q;
  int j=0;
  if(i<0) printf("position not exist\n");    /* 参数i不合理 */
  else 
  { s=(dlink *)malloc(sizeof(dlink));
    scanf("%d",&s->data);
    if(i==0)                                 /* 在第1个结点前插入 */
    { s->next=head;
      head->prior=s;
      head=s;
    }
    else                                     /* 找插入位置 */
    { q=head;
      while(j<i&&q!=NULL)
      { j++;
        p=q;
        q=q->next;
      }
      if(j<i) printf("position not exist\n");/* 参数i不合理 */
      else                                   /* 插入 */
      { s->next=q;
        s->prior=p;
        if(p->next!=NULL)
          q->prior=s;
        p->next=s;
      }
    }
  }
  return head;
}


/*(2) 删除双向链表head的第i个结点。*/
dlink *delnode(dlink *head,int i)
{ dlink *p,*s;
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
	if(s->next!=NULL)
	 s->next->prior=p;
       free(s);
      }
    }
  }
  return head;
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

  printf("input the position of element to delete:");
  scanf("%d",&i);                    /* 删除 */
  H=delnode(H,i);
  list(H);                           /* 输出删除元素后双链表 */


  printf("input the position to insert:");
  scanf("%d",&i);
  H=insnode(H,i);                    /* 插入 */
  list(H);                           /* 输出插入元素后双链表 */
}