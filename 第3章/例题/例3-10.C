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


/*【例3.10】编写函数，在带头结点的链串上实现Brute-Force算法 */
int seek(linkstr *s,linkstr *t,int pos)
{ int i; linkstr *p,*q,*r;
  if(pos<1) return 0;
  for(i=0,r=s;r&&i<pos;i++,r=r->next);
  if(!r) return 0;           /* pos值超过链串长度 */
  while(r)
  { p=r; q=t->next;
    while(p&&q&&q->ch==p->ch)
    { p=p->next; q=q->next;} /* 若当前字符相同，则继续比较下一个字符 */
    if(!q) return i;         /* 匹配成功，返回第一个字符在主串中的位序 */
    i++; r=r->next;          /* 匹配不成功，继续进行下一趟匹配 */
  }
  return 0;                  /* 匹配不成功，返回0 */
}




main()
{ char s[81],t[81];
  linkstr *s1,*s2;
  int n,pos;

  s1=initstring();
  s2=initstring();

  printf("input string s:");
  gets(s);
  printf("input string t:");
  gets(t);

  strassign(s1,s);           /* 赋值*/
  strassign(s2,t);           /* 赋值*/

  printf("input begin position:");
  scanf("%d",&pos);
  n=seek(s1,s2,pos);         /* 采用Brute-Force算法 */
  printf("%d\n",n);          /* 失败输出0,成功输出起始位置 */
}