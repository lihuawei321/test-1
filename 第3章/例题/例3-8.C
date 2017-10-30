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


/* 【例3.8】写一个递归的算法来实现字符串逆序存储，要求不另设串存储空间 */
void turn(string *s)
{ char temp;static int i=0;   /* 定义静态存储变量，以保持i值递增 */
  if(i<s->length/2)  
  { temp=s->ch[i];            /* 对称字符交换位置 */
    s->ch[i]=s->ch[s->length-1-i];
    s->ch[s->length-i-1]=temp;
    i++;
    turn(s);                  /* 递归 */
  }
}



main()
{ char str[81];
  string s;

  initstring(&s);

  printf("input string:");
  gets(str);

  strassign(&s,str);        /* 赋值*/
  printf("original string is:");
  list(&s);                 /* 输出 */

  printf("turn string is:");
  turn(&s);                 /* 逆置 */
  list(&s);                 /* 输出 */

}
