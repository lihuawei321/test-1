#define INITSTRLEN 100  /* 为串分配的存储空间的初始量 */
typedef struct
{ char *ch;             /* 串存放的起始地址 */
  int length;           /* 串长 */        
  int strsize;          /* 当前为串分配的存储空间大小 */
}string;



/* 初始化操作(创建一个空串s) */
void initstring(string *s)
{ s->ch=(char *)malloc(INITSTRLEN*sizeof(char)); /* 初始化串存储空间 */
  s->length=0;                                   /* 初始化串长 */
  s->strsize=INITSTRLEN;                         /* 初始化当前存储空间容量 */
}


/* 串赋值操作(将字符串常量s2赋给字符串变量s1) */
void strassign(string *s1,char *s2)
{ int i=0;
  while(s2[i]!='\0') i++;   /* 计算s2的串长 */
  if(i>s1->strsize)         /* 存储空间不足时,增加存储空间 */
  { s1->ch=(char *)realloc(s1->ch,i*sizeof(char));
    s1->strsize=i;
  }
  s1->length=i;
  for(i=0;i<s1->length;i++) /* 从第1个字符开始逐个字符复制 */
    s1->ch[i]=s2[i];
}


/* 编写算法，统计字符串s中含有子串t的个数。要求：分别用顺序串和链串实现 */
/* (1) 用顺序串实现 */

int seek(string *s,string *t,int pos)
{ int i,j;
  if(pos<1||pos>s->length||pos>s->length-t->length+1) return 0;
  i=pos-1; j=0;
  while(i<s->length&&j<t->length)
    if(s->ch[i]==t->ch[j])
    { i++;j++;}                /* 继续匹配下一个字符 */
    else
    { i=i-j+1;j=0;}            /* 主串、子串指针回溯，重新开始下一次匹配 */
  if(j>=t->length)
    return i-t->length+1;      /* 返回主串中已匹配子串的第一个字符的位序 */
  else
    return 0;                  /* 匹配不成功 */
}

subscount(string *s,string *t)       
{ int i,n=0,k;
  for(i=1;i<=s->length;i++)
  { k=seek(s,t,i);
   if(k)
   { n++;i=k+t->length-1;}
  }
  return n;
}





main()
{ char s[81],t[81];
  string s1,s2;
  int n;

  initstring(&s1);
  initstring(&s2);

  printf("input string s:");
  gets(s);
  printf("input string t:");
  gets(t);

  strassign(&s1,s);          /* 赋值*/
  strassign(&s2,t);          /* 赋值*/

  n=subscount(&s1,&s2);      /* 统计子串数 */
  printf("sub-string count is: %d\n",n);
}
