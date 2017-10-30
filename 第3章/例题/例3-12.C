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


/* 【例3.12】编写算法，求串s和串t的最长公共子串 */
void maxpubstr(string *s,string *t)
{ int pos=0,len=0,i,j,k,len1;
  i=0;                      /* i作为扫描s的指针 */
  while(i<s->length)
  { j=0;                    /* j作为扫描t的指针 */
    while(j<t->length)
    { if(s->ch[i]==t->ch[j])
	  { len1=1;             /* 找一个子串,其在s中的位序为i,长度为len1 */
	    for(k=1;k+i<s->length&&k+j<t->length&&s->ch[k+i]==t->ch[k+j];k++)
	      len1++;
	    if(len1>len)
            { pos=i;len=len1;}  /* 保存最长公共子串的起始位置和长度 */
	  }
	  j++;
    }
    i++;                    /* 继续扫描s中第i个字符之后的字符 */
  }
  for(i=0;i<len;i++)        /* 输出最长公共子串 */
    printf("%c",s->ch[i+pos]);
}




main()
{ char s[81],t[81];
  string s1,s2;
  
  initstring(&s1);
  initstring(&s2);

  printf("input string s:");
  gets(s);
  printf("input string t:");
  gets(t);

  strassign(&s1,s);          /* 赋值*/
  strassign(&s2,t);          /* 赋值*/
  printf("max public sub-string:");
  maxpubstr(&s1,&s2);        /* 输出最长公共子串 */
}
