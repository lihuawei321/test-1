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


/* 教材习题2-4-6．编写算法，将带头结点的单链表A分解为两个具有相同结构的链表B、C。其中B中的结点是A中值小于0的结点，C中的结点是A中值大于0的结点(链表A的元素类型为整型，要求B、C利用A的结点)。*/

CFGL(slink *A,slink *B,slink *C)
 { slink *pb,*p,*q,*pc;
   p=A->next;
   q=A;
   while(p!=NULL)                            /* 删除值为0的结点 */
   { while(p!=NULL&&p->data!=0)
     {q=p;p=p->next;}
     if(p->data==0)
     { q->next=p->next;
       free(p);
       p=q->next;
     }
   }
   B->next=A->next;
   p=A->next;
   pb=B;
   pc=C;
   while(p!=NULL)                             /* 从A的第1个结点开始判断 */
   {
     while(p!=NULL&&p->data<0) {pb->next=p;pb=pb->next;p=p->next;}    /* 若结点值，链入B */
     if(p!=NULL)
      {pc->next=p;pc=pc->next;p=p->next;}     /* 若结点值大于0，链入C */
   }
   pb->next=NULL;                             /* B的尾结点的指针域置空 */
   pc->next=NULL;                             /* C的尾结点的指针域置空 */
 }



main()
{ slink *A,*B,*C;
  int n;

  printf("input length of link A:");
  scanf("%d",&n);
  printf("input %d data:",n);
  A=creslink(n);		    /* 创建含有n个元素的带头结点的单链表A */
  B=(slink *)malloc(sizeof(slink)); /* 创建B的头结点*/
  C=(slink *)malloc(sizeof(slink)); /* 创建C的头结点*/
  B->next=C->next=NULL;
  list(A);                          /* 输出单链表A */

  CFGL(A,B,C);                      /* 拆分 */

  printf("the link(>0) is:");
  list(C);                          /* 输出拆分后值大于0的链表 */
  printf("the link(<0) is:");
  list(B);                          /* 输出拆分后值小于0的链表 */

}