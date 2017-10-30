#include "stdio.h"
typedef struct node
{ char ch;              /* 数据域 */
  struct node *next;    /* 指针域 */
}linkstr;


/* 初始化操作(创建一个只含头结点空链串s) */
linkstr *initstring(void)
{ linkstr *s;
  s=(linkstr *)malloc(sizeof(linkstr));     /* 创建头结点 */
  s->next=NULL;
  return s;
}


/* 串赋值操作(将一个字符串常量t赋给字符串变量s) */
void strassign(linkstr *s,char *t)
{ int i;linkstr *p,*q,*r;
  r=s;q=s->next;
  for(i=0;t[i]!='\0';i++)
    if(q!=NULL)                 /* 利用原链表结点空间存放串值 */
    { q->ch=t[i];r=q;q=q->next;}
    else                        /* 开辟新结点存放串值 */
    { p=(linkstr *)malloc(sizeof(linkstr));
      p->ch=t[i];
      r->next=p;
      r=p;
    }
  r->next=NULL;
  while(q!=NULL)                /* 若原串s中有多余结点空间,则释放 */
  { p=q->next;free(q);q=p;}
} 


/* 输出操作(输出串s的值) */
void list(linkstr *s)
{ linkstr *p;
  p=s->next;
  while(p!=NULL)
  { printf("%c",p->ch);
    p=p->next;
  }
  printf("\n");
}


/* 教材习题3-4-8 编写算法，将链串中最先出现的子串"ab"改为"xyz" */

void abtoxyz(linkstr *s)
{ linkstr *p=s->next,*q;
  int find=0;
  while(p->next!=NULL&&find==0)
  { if(p->ch=='a'&&p->next->ch=='b')
     { p->ch='x';p->next->ch='z';
       q=(linkstr *)malloc(sizeof(linkstr));
       q->ch='y';
       q->next=p->next;
       p->next=q;
       find=1;
     }
    else p=p->next;
  }
}



main()
{ char str[81];
  linkstr *s;
 
  s=initstring();

  printf("input string:");
  gets(str);
  
  strassign(s,str);           /* 赋值*/
 
  abtoxyz(s);                 /* 替换 */
  printf("tne replace string:");
  list(s);                    /* 输出 */
}