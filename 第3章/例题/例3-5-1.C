
typedef int ElemType;  
typedef struct node
{ ElemType data;       /* 数据域 */
  struct node *next;   /* 指针域 */
}linkstack;            /* 链栈结点类型与单链表结点类型相同 */



#include "stdio.h"
/* 初始化操作(创建一个带头结点的空栈S) */
linkstack *initstack()
{ linkstack *S;
  S=(linkstack *)malloc(sizeof(linkstack));
  S->next=NULL;
  return S;
}


/* 入栈操作(将值为x的数据元素插入栈S中,使x成为新的栈顶元素) */
int push(linkstack *S,ElemType x)
{ linkstack *p;
  p=(linkstack *)malloc(sizeof(linkstack));/* 申请存储空间 */
  if(!p) return 0;                         /* 若空间申请不成功,返回0 */
  p->data=x;
  p->next=S->next;                         /* 插入到头结点之后 */
  S->next=p;
  return 1;
}

/* 出栈操作(删除栈S的栈顶元素) */
int pop(linkstack *S,ElemType *e)
{ linkstack *p;
  if(S->next==NULL) return 0;  /* 栈空,删除失败,返回0 */
  p=S->next;
  *e=p->data;                  /* 栈顶结点值赋给e指针所指向的单元 */
  S->next=p->next;
  free(p);
  return 1;                    /* 出栈成功,返回1 */
}



/* 输出栈(输出栈S自栈顶到栈底的元素值)*/
void list(linkstack *S)
{ linkstack *p;
  p=S->next;
  while(p!=NULL)
  { printf("%4d ",p->data); 
    p=p->next;
  }
  printf("\n");
}


/* 【例3.5】编写算法，利用栈将带头结点的单链表逆置 */

/* 方法一：把单链表S1看成一个链栈， 把在S1中出栈的元素依次入栈S2，直到S1为空为止，此时的S2就是S1的逆置 */
void turnlink1(linkstack *S1,linkstack *S2)
{ ElemType x;
  while(S1->next!=NULL)
  { pop(S1,&x);
    push(S2,x);
  }
}



main()
{ linkstack *S1,*S2;
  ElemType x;

  S1=initstack();                        /* 创建空栈S1 */
  S2=initstack();                        /* 创建空栈S2 */

  printf("input datas(-1:end):");        /* 输入数据,-1作为结束标志 */
  scanf("%d",&x);
  while(x!=-1)
  { push(S1,x);  		         /* 元素入栈 */
    scanf("%d",&x);
  }
  printf("S1 is:");
  list(S1);
  turnlink1(S1,S2);
  printf("S2 is:");
  list(S2);
}
