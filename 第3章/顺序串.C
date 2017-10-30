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


/* 串复制操作(将字符串变量s2的值赋给字符串变量s1中) */
void assign(string *s1,string *s2)
{ int i;
  if(s1->strsize<s2->length) /* 存储空间不足,增加存储空间 */
  { s1->ch=(char *)realloc(s1->ch,s2->length*sizeof(char));
    s1->strsize=s2->length;
  }
  s1->length=s2->length;     /* 修改串长 */
  for(i=0;i<s1->length;i++)  /* 从第1个字符开始,逐个字符复制 */
    s1->ch[i]=s2->ch[i];
}


/* 求串长操作(求串s的长度)*/
int length(string *s)
{ return s->length;
}

/* 串连接操作(将字符串s1和s2连接后存到串s中) */
void concat(string *s,string *s1,string *s2)
{  int i;
   if(s->strsize<(s1->length+s2->length))/* 增加存储空间 */
   { s->ch=(char *)realloc(s->ch,(s1->length+s2->length)*sizeof(char));
     s->strsize=s1->length+s2->length;
   }
   s->length=s1->length+s2->length;     /* 连接后串s的长度 */
   for(i=0;i<s1->length;i++)            /* 把s1复制到s中 */
     s->ch[i]=s1->ch[i];
   for(;i<s->length;i++)                /* 把s2追加到s后 */
     s->ch[i]=s2->ch[i-s1->length];
}


/* 判串等操作(判断两个字符串s和t是否相等,若相等返回1,否则返回0) */
int equal(string *s,string *t)
{ int i;
  for(i=0;i<s->length&&i<t->length;i++)
    if(s->ch[i]!=t->ch[i]) return 0;      /* 串中对应字符不等 */
  if(i<s->length||i<t->length) return 0;  /* 串长不等 */
  else return 1;                          /* 串相等 */
}


/* 取子串操作(在字符串s中,把从第i个字符开始的连续j个字符存入字符串t中) */
int substr(string *s,int i,int j,string *t)
{ int k;
  if(i<=0||i>s->length||j<0||j>s->length-i+1) return 0;/* 参数i、j不合理 */
  if(t->strsize<j)
  { t->ch=(char *)realloc(t->ch,j*sizeof(char));
    t->strsize=j;
  }
  for(k=0;k<j;k++)
    t->ch[k]=s->ch[i-1+k];    /* 字符复制 */
  t->length=j;                /* 修改串t的长度 */
  return 1;
}


/* 串替换操作(把字符串s的从第i个字符开始的j个连续字符用字符串t替换) */
int replace(string *s,int i,int j,string *t)
{ int k,m;
  char *p1,*p2;
  if(i<=0||i>s->length||j<=0||j>s->length-i+1) return 0; /* 参数i、j不合理 */
  if(j<t->length)
  { if(s->length+t->length-j>s->strsize)   /* 存储空间不足,增加存储空间 */
{ s->ch=(char *)realloc(s->ch,(s->length+t->length-j)*sizeof(char));
s->strsize=s->length+t->length-j;    /* 修改串空间长度 */
}
    for(k=s->length-1;k>=i+j-1;k--)        /* j小于串t的长度,后移 */
      s->ch[k-j+t->length]=s->ch[k];
  }
  else                                     /* j大于串t的长度,前移 */
    for(k=i-1+j;k<s->length;k++)
      s->ch[k-j+t->length]=s->ch[k];
  s->length=s->length+t->length-j;
  for(k=0;k<t->length;k++)                 /* 复制 */
    s->ch[k+i-1]=t->ch[k];
  return 1;
}


/* 插入操作(在字符串s的第i个字符之前插入字符串t) */
int insert(string *s,int i,string *t)
{ int j;
  if(i<=0||i>s->length+1) return 0;    /* 参数i不合理 */
  if(s->strsize<s->length+t->length)   /* 增加存储空间 */
  { s->ch=(char *)realloc(s->ch,(s->length+t->length)*sizeof(char));
    s->strsize=s->length+t->length;
  }
  for(j=s->length-1;j>=i-1;j--)        /* 后移 */
    s->ch[j+t->length]=s->ch[j];
  for(j=0;j<t->length;j++)             /* 复制 */
    s->ch[i+j-1]=t->ch[j];
  s->length+=t->length;                /* 修改串长 */
  return 1;
}


/* 删除操作(在字符串中,删除从第i个字符开始的连续j个字符) */
int delete(string *s,int i,int j)
{ int k;
  if(i<=0||i>s->length||j<=0||j>s->length-i+1) return 0; /* 参数i、j不合理 */
  for(k=i+j-1;k<s->length;k++)               /* 前移 */
    s->ch[k-j]=s->ch[k];
  s->length-=j;                              /* 修改串长 */
  return 1;
}

/* 输出操作(输出串s的值) */
void list(string *s)
{ int i;
  for(i=0;i<s->length;i++)
    printf("%c",s->ch[i]);
  printf("\n");
}

main()
{ char str1[81],str2[81];
  string s,s1,s2,s3;
  int n,i,j;
  
  initstring(&s);
  initstring(&s1);
  initstring(&s2);

  printf("input string str1:");
  gets(str1);
  printf("input string str2:");
  gets(str2);

  strassign(&s1,str1);        /* 赋值*/
  printf("string s1:");
  list(&s1);                  /* 输出 */

  strassign(&s2,str2);        
  printf("string s2:");
  list(&s2);                 

  assign(&s,&s1);             /* 复制 */
  printf("copy s1 to s and s is:");
  list(&s);                   

  printf("s1 length:");
  printf("%d\n",length(&s1)); /* 输出长度 */

  concat(&s,&s1,&s2);
  printf("s1 plus s2 to s and s is:");
  list(&s);                  

  n=equal(&s1,&s2);           /* 判等 */
  if(n) printf("s1 is equal to s2\n");
  else printf("s1 is not equal to s2\n");


  printf("get sub-string from s1 to s and input position(i) and length(j):");
  scanf("%d%d",&i,&j);
  n=substr(&s1,i,j,&s);       /* 取子串 */
  if(n) { printf("sub-string is:"); list(&s);}
  else printf("error!\n");


  printf("replace in s1 use s and input position(i) and length(j):");
  scanf("%d%d",&i,&j);
  n=replace(&s1,i,j,&s);      /* 替换 */
  if(n) { printf("the result is:"); list(&s1);}
  else printf("error!\n");

  printf("insert s2 in s1 and input position(i):");
  scanf("%d",&i);
  n=insert(&s1,i,&s2);        /* 插入 */
  if(n) { printf("the result is:"); list(&s1);}
  else printf("error!\n");

  printf("delete in s1 and input position(i) and length(j):");
  scanf("%d%d",&i,&j);
  n=delete(&s1,i,j);          /* 删除 */ 
  if(n) { printf("the result is:"); list(&s1);}
  else printf("error!\n");
}
