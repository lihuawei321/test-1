/*【例2.9】假设多项式形式为：p(x)=c1xe1+c2xe2+…+cmxem，其中，ci和ei(1≤i≤m)为整型数，并且e1＞e2＞…＞em≥0。编写求两个多项式相加的程序。*/

#include "stdio.h"
typedef struct node
{ int c;                            /* 多项式项系数 */
  int e;                            /* 多项式项指数 */
  struct node *next;
}dxs;


dxs *creat(int m)                   /* 把多项式表示成带头结点的单链表 */
{ dxs *head,*p,*q;int i;
  p=head=(dxs *)malloc(sizeof(dxs));/* 头结点 */
  for(i=1;i<=m;i++)
  { q=(dxs *)malloc(sizeof(dxs));
    scanf("%d%d",&q->c,&q->e);
    p->next=q;
    p=q;
  }
  p->next=NULL;
  return head;
}


plus(dxs *h1,dxs *h2) /* 多项式求和 */
{ dxs *h,*p1,*p2,*q;
  h=h1;
  p1=h1->next; p2=h2->next;
  while(p1!=NULL&&p2!=NULL)
    if(p1->e>p2->e)               /* p1结点连到h结点的后面 */
    { h->next=p1;h=p1;p1=p1->next;} 
    else if(p2->e>p1->e)          /* p2结点连到h结点的后面 */
    { h->next=p2;h=p2;p2=p2->next;}
    else if(p1->c+p2->c!=0)       /* 结点值合并到p1结点中 */
    { p1->c=p1->c+p2->c;          /* 把p2->c累加到p1->c中 */
      h->next=p1;h=p1;p1=p1->next;/* p1结点连到h结点的后面 */
      q=p2;
      p2=p2->next;
      free(q);
    }
    else                          /* 系数和为0，删除两个对应的结点 */
    { q=p1;p1=p1->next;free(q);
      q=p2;p2=p2->next;free(q);
    }
  if(p1!=NULL) h->next=p1;        /* 剩余部分连到h结点的后面 */
  else h->next=p2;
  free(h2);
}


void list(dxs *head)              /* 输出多项式 */
{ dxs *p=head->next;;
  while(p!=NULL)
  { printf("(%4d,%4d)  ",p->c,p->e);
    p=p->next;
  }
  printf("\n");
}


main()
{ dxs *h1,*h2;
  h1=creat(5);
  h2=creat(7);
  plus(h1,h2);
  list(h1);
}
