/*广义表结点类型*/
#include "stdio.h"
typedef char ElemType;
typedef struct node
{ int tag;
  union
  { ElemType data;
    struct
      {struct node *hp;
       struct node *tp;
      }ptr;
  }val;
}gnode;

substring(char *sub,char *S,int i,int j)
{ char *p1=S+i-1,*p2=sub;
  int k=1;
  while(k<=j)
    { *p2++=*p1++;k++;}
  *p2='\0';
}

serve(char *str,char *hstr)
{ char ch=*str;
  int n,i,k;
  n=strlen(str);i=0;
  for(k=0;i<n&&ch!=','||k!=0;i++)
  {
    ch=*(str+i);
    if(ch=='(')  ++k;
    else if(ch==')')  --k;
  }
  if(i<n)
  { substring(hstr,str,1,i-1);
    substring(str,str,i+1,n-i+1);
  }
  else
  { strcpy(hstr,str);
    *str='\0';
  }
}
/*建立*/
gnode *creat(char *S)
{ gnode *h,*p,*q,*t;
  char emp[]="()";
  char sub[81],hsub[81];
  if(strcmp(S,emp)==0)  h=NULL;
  else
  { h=(gnode *)malloc(sizeof(gnode));
    if(strlen(S)==1)
    { h->tag=0;h->val.data=*S;}
    else
    { h->tag=1;
      p=h;
      substring(sub,S,2,strlen(S)-2);
      do { serve(sub,hsub);
	   p->val.ptr.hp=creat(hsub);q=p;
	   if(strlen(sub)!=0)
	   { p=(gnode *)malloc(sizeof(gnode));
	     p->tag=1;q->val.ptr.tp=p;
	   }
	 }while(strlen(sub)!=0);
	 q->val.ptr.tp=NULL;
     }
   }
   return h;
 }

/*输出*/
void list(gnode *h)
{ gnode *p,*q;
  if(h!=NULL)
  { if(h->tag==1)
    { p=h->val.ptr.hp;
      if(p->tag==1)
      printf("%c",'(');
      list(h->val.ptr.hp);
    }
    else
      printf("%c",h->val.data);
    if(h->tag==1&&h->val.ptr.tp!=h)
    { if(h->val.ptr.tp!=NULL)
      { printf("%c",',');
	list(h->val.ptr.tp);
      }
      else
      printf("%c",')');
    }
  }
}
/*求深度*/
depth(gnode *h)
{ int max,dep;
  gnode *p;
  if(h==NULL) return 1;
  if(h->tag==0) return 0;
  for(max=0,p=h;p;p=p->val.ptr.tp)
  { dep=depth(p->val.ptr.hp);
    if(dep>max) max=dep;
  }
  return max+1;
}

/*复制*/
gnode *copy(gnode *h)
{ gnode *t;
  if(h==NULL) t=NULL;
  else
  { t=(gnode *)malloc(sizeof(gnode));
    t->tag=h->tag;
    if(h->tag==0) t->val.data=h->val.data;
    else
    { t->val.ptr.hp=copy(h->val.ptr.hp);
      t->val.ptr.tp=copy(h->val.ptr.tp);
    }
   }
   return t;
}
/*取表头*/
gnode *head(gnode *h)
{ gnode *h1;
  if(h==NULL) h1=NULL;
  else h1=copy(h->val.ptr.hp);
  return h1;
}

/* 取表尾 */
gnode *tail(gnode *h)
{ gnode *h1;
  if(h==NULL) h1=NULL;
  else h1=copy(h->val.ptr.tp);
  return h1;
}




main()
{ char a[]="(((d)),a,(b))";
  gnode *h,*p,*t;
  clrscr();
  h=creat(a);
  p=(gnode *)malloc(sizeof(gnode));
  p->tag=1;p->val.ptr.hp=h;p->val.ptr.tp=p;
  list(p);
  printf("\n");
  printf("%d\n",depth(h));
  t=copy(h);
  p->tag=1;p->val.ptr.hp=t;p->val.ptr.tp=p;
  list(p);
  printf("\n");
  t=head(h);
  p->tag=1;p->val.ptr.hp=t;p->val.ptr.tp=p;
  list(p);
  printf("\n");
  t=tail(h);
  p->tag=1;p->val.ptr.hp=t;p->val.ptr.tp=p;
  list(p);
}