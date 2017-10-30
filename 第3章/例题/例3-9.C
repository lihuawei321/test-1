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


/*【例3.9】设计一个函数，将链串中存放的一个英文句子的各单词的首字母变为大写*/
void firstupr(linkstr *s)
{ int word=0;linkstr *p;              /* word用于标记是否为空格 */
  p=s->next;
  while(p!=NULL)
  { if(p->ch==' ') word=0;            /* 当前字符是空格,word置0 */
    else if(word==0)                  /* 当前字符不为空格,但前一个字符是空格 */
         { if(p->ch>='a'&&p->ch<='z') /* 将当前字母变为大写 */
           p->ch-=32;
	   word=1;                    /* 同时将word置1 */
	 }
    p=p->next;
  }
}




main()
{ char str[81];
  linkstr *s;

  s=initstring();

  printf("input string:");
  gets(str);

  strassign(s,str);        /* 赋值*/
  printf("original string is:");
  list(s);                 /* 输出 */

  printf("turn string is:");
  firstupr(s);             /* 词首字母大写 */
  list(s);                 /* 输出 */

}