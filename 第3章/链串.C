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


/* 串复制操作(将串变量t的值赋给串变量s) */
void assign(linkstr *s,linkstr *t)
{ linkstr *p,*q,*r,*u;
  p=t->next;q=s->next;r=s;
  while(p!=NULL)
  { if(q!=NULL)                 /* 利用原链表结点空间存放串值 */
    { q->ch=p->ch;r=q;q=q->next;}
    else                        /* 开辟新结点存放串值 */
    { u=(linkstr *)malloc(sizeof(linkstr));
      u->ch=p->ch;
      r->next=u;
      r=u;
    }
    p=p->next;
  }
  r->next=NULL;
  while(q!=NULL)                /* 若原串中有多余结点空间,则释放 */
  { p=q->next;free(q);q=p;}
}


/* 求长度操作(计算串s的长度) */
int length(linkstr *s)
{ linkstr *p;int n=0;
  p=s->next;
  while(p!=NULL)
  { n++;p=p->next;}
  return n;
}


/* 判等操作(判断两个串s和t是否相等，若相等返回1，否则返回0) */
int equal(linkstr *s,linkstr *t)
{ linkstr *p,*q;
  p=s->next;q=t->next;
  while(p!=NULL&&q!=NULL)
  { if(p->ch!=q->ch) return 0;   /* 对应字符不同 */
    p=p->next;q=q->next;
  }
  if(p!=NULL||q!=NULL) return 0; /* 长度不同 */
  else  return 1;                /* 串相等 */
}

/* 连接操作(将串s2连接到串s1的后面,结果存入串s中)*/
void concat(linkstr *s,linkstr *s1,linkstr *s2)
{ linkstr *p,*q,*r,*u;
  r=s;q=s->next;
  p=s1->next;
  while(p!=NULL)                  /* 将串s1复制到s中 */
  { if(q!=NULL)                   /* 利用原链表结点空间存放串值 */
    { q->ch=p->ch;r=q;q=q->next;}
    else                          /* 开辟新结点存放串值 */
    { u=(linkstr *)malloc(sizeof(linkstr));
      u->ch=p->ch;
      r->next=u;
      r=u;
    }
    p=p->next;
  }
  p=s2->next;
  while(p!=NULL)                 /* 将串s2追加到s后 */
  { if(q!=NULL)                  /* 利用原链表结点空间存放串值 */
    { q->ch=p->ch;r=q;q=q->next;}
    else                         /* 开辟新结点存放串值 */
    { u=(linkstr *)malloc(sizeof(linkstr));
      u->ch=p->ch;
      r->next=u;
      r=u;
    }
    p=p->next;
  }
  r->next=NULL;
  while(q!=NULL)                /* 若原串中有多余结点空间,则释放 */
  { p=q->next;free(q);q=p;}
}


/* 取子串操作(将串s的从第i个字符开始的连续j个字符存入t中) */
int substr(linkstr *s,int i,int j,linkstr *t)
{ int k;linkstr *p,*q,*r,*u;
  if(i<=0||i>length(s)||j<=0||i+j-1>length(s)) return 0; /* 参数i、j不合理 */
  for(k=0,p=s;k<i;k++) p=p->next;         /* 让p指向第i个结点 */
  for(k=0,r=t,q=t->next;k<j;k++)          /* 复制到t中 */
  { if(q!=NULL)                           /* 利用原链表结点空间存放串值 */
    { q->ch=p->ch;r=q;q=q->next;}
    else                                  /* 开辟新结点存放串值 */
    { u=(linkstr *)malloc(sizeof(linkstr));
      u->ch=p->ch;
      r->next=u;
      r=u;
    }
    p=p->next;
  }
  r->next=NULL;
  while(q!=NULL)
  { p=q->next; free(q); q=p;}
  return 1;
}

/* 插入操作(在串s的第i个位置之前插入子串t) */
int insert(linkstr *s,int i,linkstr *t)
{ int j;linkstr *p,*q,*r;
  if(i<=0||i>length(s)+1) return 0;
  for(j=0,r=s;j<i-1;j++) r=r->next;   /* 让r指向第i-1个结点 */
  p=t->next;
  while(p!=NULL)                  /* 将t复制到r所指向的结点后面 */
  { q=(linkstr *)malloc(sizeof(linkstr));
    q->ch=p->ch;
    q->next=r->next;
    r->next=q;
    r=q;
    p=p->next;
  }
  return 1;
}


/* 删除操作(删除链串s的从第i个字符开始的连续j个字符) */
int delete(linkstr *s,int i,int j)
{ int k;linkstr *p,*q,*r;
  if(i<=0||i>length(s)||j<0||i+j-1>length(s)) return 0; /* 参数i、j不合理 */
  for(k=0,p=s;k<i-1;k++) p=p->next;     /* 让p指向第i-1个结点 */
  for(k=1;k<=j;k++)
  { q=p->next;p->next=q->next;free(q);}
  return 1;
}


/* 替换操作(将链串s的从第i个字符开始的连续j个字符用串t替换) */
int replace(linkstr *s,int i,int j,linkstr *t)
{ int k;
  linkstr *p1,*p2,*q,*r,*f;
  if(i<=0||i>length(s)||j<=0||i+j-1>length(s)) return 0; /* 参数i、j不合理 */
  for(k=0,r=s;k<i-1;k++) r=r->next;    /* 让r指向s的第i-1个结点 */
  for(k=0,p1=r;k<=j;k++) p1=p1->next;  /* 让p1指向s的第i+j个结点 */
  f=r->next;p2=t->next;
  while(p2!=NULL)                      /* 将串t复制到r所指向的结点后面 */
  { if(f!=p1)                          /* 利用原链表结点空间存放串值 */
    { f->ch=p2->ch;r=f;f=f->next;}
    else                               /* 开辟新结点存放串值 */
    { q=(linkstr *)malloc(sizeof(linkstr));
      q->ch=p2->ch;
      r->next=q;
      r=q;
    }
    p2=p2->next;
  }
  r->next=p1;                          /* 替换完成 */
  return 1;
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



main()
{ char str1[81],str2[81];
  linkstr *s,*s1,*s2;
  int n,i,j;

  s=initstring();
  s1=initstring();
  s2=initstring();

  printf("input string str1:");
  gets(str1);
  printf("input string str2:");
  gets(str2);

  strassign(s1,str1);         /* 赋值*/
  printf("string s1:");
  list(s1);                   /* 输出 */

  strassign(s2,str2);
  printf("string s2:");
  list(s2);

  assign(s,s1);              /* 复制 */
  printf("copy s1 to s and s is:");
  list(s);                   

  printf("s1 length:");
  printf("%d\n",length(s1)); /* 输出长度 */

  concat(s,s1,s2);
  printf("s1 plus s2 to s and s is:");
  list(s);                  

  n=equal(s1,s2);             /* 判等 */
  if(n) printf("s1 is equal to s2\n");
  else printf("s1 is not equal to s2\n");


  printf("get sub-string from s1 to s and input position(i) and length(j):");
  scanf("%d%d",&i,&j);
  n=substr(s1,i,j,s);         /* 取子串 */
  if(n) { printf("sub-string is:"); list(s);}
  else printf("error!\n");


  printf("replace in s1 use s and input position(i) and length(j):");
  scanf("%d%d",&i,&j);
  n=replace(s1,i,j,s);        /* 替换 */
  if(n) { printf("the result is:"); list(s1);}
  else printf("error!\n");

  printf("insert s2 in s1 and input position(i):");
  scanf("%d",&i);
  n=insert(s1,i,s2);          /* 插入 */
  if(n) { printf("the result is:"); list(s1);}
  else printf("error!\n");

  printf("delete in s1 and input position(i) and length(j):");
  scanf("%d%d",&i,&j);
  n=delete(s1,i,j);           /* 删除 */ 
  if(n) { printf("the result is:"); list(s1);}
  else printf("error!\n");
}