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


/* 输出操作(输出串s的值) */
void list(string *s)
{ int i;
  for(i=0;i<s->length;i++)
    printf("%c",s->ch[i]);
  printf("\n");
}



/*Brute-Force算法*/
int index(string *s,string *t,int pos)
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


/* KMP算法  */
/* 修正前获取next[]值的算法 */
void getnext(string *t,int next[])  /* 由模式串t求出next值 */
{ int j,k;
  j=0;k=-1;next[0]=-1;
  while(j<t->length)
    if(k==-1||t->ch[j]==t->ch[k])
    { j++;k++;next[j]=k;}
    else k=next[k];
}


/* 修正后获取next[]值的算法 */
void getnextval(string *t,int nextval[])
{ int j,k;
  j=0;k=-1;nextval[0]=-1;
  while(j<t->length)
    if(k==-1||t->ch[j]==t->ch[k])
    { j++;k++;
      if(t->ch[j]!=t->ch[k])
        nextval[j]=k;
      else
        nextval[j]=nextval[k];
    }
    else k=nextval[k];
}



int KMPindexa(string *s,string *t,int pos)
{ int next[INITSTRLEN],i,j;
  getnext(t,next);
  i=pos-1;j=0;
  while(i<s->length&&j<t->length)
    if(j==-1||s->ch[i]==t->ch[j])
    { i++;j++;}           /* 对应字符相同，指针后移一个位置 */
    else j=next[j];       /* i不变，j后退，相当于模式串向右滑动 */
  if(j>=t->length)
    return i-t->length+1; /* 匹配成功，返回第一个匹配字符在主串中的位序 */
  else return 0;          /* 匹配不成功，返回标志0 */
}



int KMPindexb(string *s,string *t,int pos)
{ int next[INITSTRLEN],i,j;
  getnextval(t,next);
  i=pos-1;j=0;
  while(i<s->length&&j<t->length)
    if(j==-1||s->ch[i]==t->ch[j])
    { i++;j++;}           /* 对应字符相同，指针后移一个位置 */
    else j=next[j];       /* i不变，j后退，相当于模式串向右滑动 */
  if(j>=t->length)
    return i-t->length+1; /* 匹配成功，返回第一个匹配字符在主串中的位序 */
  else return 0;          /* 匹配不成功，返回标志0 */
}



main()
{ char s[81],t[81];
  string s1,s2;
  int n,pos;

  initstring(&s1);
  initstring(&s2);

  printf("input string s:");
  gets(s);
  printf("input string t:");
  gets(t);

  strassign(&s1,s);          /* 赋值*/
  strassign(&s2,t);          /* 赋值*/

  printf("input begin position:");
  scanf("%d",&pos);
  n=index(&s1,&s2,pos);      /* 采用Brute-Force算法 */
  printf("%d\n",n);          /* 失败输出0,成功输出起始位置 */

  printf("input begin position:");
  scanf("%d",&pos);
  n=KMPindexa(&s1,&s2,pos);  /* 采用修正前的KMP算法 */
  printf("%d\n",n);          /* 失败输出0,成功输出起始位置 */

  printf("input begin position:");
  scanf("%d",&pos);
  n=KMPindexb(&s1,&s2,pos);  /* 采用修正前的KMP算法 */
  printf("%d\n",n);          /* 失败输出0,成功输出起始位置 */

}
