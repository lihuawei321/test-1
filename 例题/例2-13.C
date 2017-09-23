typedef int ElemType;     /* 在实际中,根据需要定义所需的数据类型 */
#define MAXSIZE 100       /* 静态链表的最大长度,根据实际情况定义 */
typedef struct
{ ElemType data;
  int cur;                /* 游标,指向后继结点的存储位置 */
}stalink[MAXSIZE];

/* 初始化操作(建立一个空的静态链表space) */

void initlist(stalink space)   /* space[0]为备用链表头结点 */
{ int i;
  for(i=0;i<MAXSIZE-1;i++)
    space[i].cur=i+1;
  space[MAXSIZE-1].cur=0;
}

/* 获取结点函数allocnode() */

int allocnode(stalink space)
{ int i;
  i=space[0].cur;
  if(i==0) return 0;          /* 备用链表空间已空,分配空间失败 */
  space[0].cur=space[i].cur;
  return i;                   /* 分配成功,返回结点下标 */
}

/* 回收结点函数freenode() */

void freenode(stalink space,int i)
{ space[i].cur=space[0].cur;
  space[0].cur=i;
}

/* 建立静态链表(建立一个含有n个结点的静态链表head) */
int crestalink(stalink space,int n)
{ int head,k,s,i;
  k=head=allocnode(space);
  for(i=1;i<=n;i++)
  { s=allocnode(space);
    scanf("%d",&space[s].data);
    space[k].cur=s;
    k=s;
  }
  space[k].cur=0;
  return head;
}

/* 求表长操作(计算静态链表head中数据元素的个数) */
int getlen(stalink space,int head)  /* head为链表头结点的下标 */
{ int i,k;
  k=space[head].cur;i=0;
  while(k!=0)
  { i++;k=space[k].cur;}
  return i;
}

/* 取元素操作(取出静态链表head中的第i个结点的元素值) */
int getelem(stalink space,int head,int i,ElemType *e)
{ int j,k;
  if(i<1) return 0;      /* 参数i不合法 */
  j=0;k=head;
  while(k!=0&&j<i)       /* 从静态链表的第一个结点开始查找第i个结点,其下标存入k */
  { j++;k=space[k].cur;}
  if(k==0) return 0;     /* 参数i超过表长 */
  *e=space[k].data;
  return 1;              /* 读取元素成功,返回真值 */
}

/* 定位操作(确定静态链表head中第一个值为x的结点的位置) */
int locate(stalink space,int head,ElemType x)
{ int k;
  k=space[head].cur;
  while(k!=0&&space[k].data!=x)
    k=space[k].cur;
  return k;               /* 不存在,返回0,否则返回下标k */
}

/* 插入操作(在静态链表head的第i个结点之前插入一个值为x的新结点) */
int insert(stalink space,int head,int i,ElemType x)
{ int j,k,m;
  if(i<1) return 0;       /* 参数i不合法,插入失败,返回0 */
  k=head;j=0;
  while(k!=0&&j<i-1)      /* 从第一个结点开始查找第i-1个结点,其下标存入k */
  { j++;k=space[k].cur;}
  if(k==0) return 0;
  m=allocnode(space);     /* 从备用链表中获取结点,结点下标为m */
  if(m!=0)                /* 若m不为0,取结点成功,开始插入 */
  { space[m].data=x;
    space[m].cur=space[k].cur;
	space[k].cur=m;
    return 1;             /* 插入成功,返回1 */
  }
  else return 0;          /* 无可用空间 */
}

/* 删除操作(将静态链表head中的第i个结点删除) */
int delete(stalink space,int head,int i,ElemType *e)
{ int j,k,m;
  if(i<1) return 0;   /* 参数i不合法,删除失败,返回0 */
  k=head;j=0;
  while(k!=0&&j<i-1)  /* 从第一个结点开始查找第i-1个结点,其下标存入k */
  { j++;k=space[k].cur;}
  if(k==0) return 0;
  m=space[k].cur;            /* m为第i个结点的下标 */
  space[k].cur=space[m].cur; /* 将第i个结点删除 */
  *e=space[m].data;
  freenode(space,m);
  return 1;                  /* 删除成功,返回1 */
}

/* 输出操作(从头结点开始,依次输出静态链表head中的所有元素值) */
void list(stalink space,int head)
{ int i;
  i=space[head].cur;
  while(i!=0)
  { printf("%4d ",space[i].data);
    i=space[i].cur;
  }
  printf("\n");
}

/* 教材【例2.13】已知A和B是两个集合,元素类型都为整型,编写算法,建立表示集合(A-B)∪(B-A)的静态链表? */
void mergesetAB(stalink A,int HA,stalink B,int HB)
{ int i,j,k,m;
  ElemType x;
  j=B[HB].cur;
  while(j!=0)
  { x=B[j].data;                /* getelem(B,HB,j,&x);*/
    i=locate(A,HA,x);           /* 在静态链表A中查找集合B中的数据元素x */
    if(i==0) insert(A,HA,1,x);  /* 如果不存在,在A中插入值为x的结点 */
    else
    { m=0;k=HA;
      while(k!=i)
      { m++;k=A[k].cur;}
      delete(A,HA,m,&x);
    }                           /* 如果存在,在A中删除值为x的结点 */
    j=B[j].cur;
  }
  list(A,HA);                   /* 输出 */
}

main()
{int n,A,B;
 ElemType e;
 stalink spacea,spaceb;

 clrscr();                   /* 清屏 */
 initlist(spacea);           /* 初始化 */
 initlist(spaceb);
 
 printf("input the number of A:");
 scanf("%d",&n);
 printf("input %d data:",n);
 A=crestalink(spacea,n);     /* 建立一个含有n个结点的静态链表A */

 printf("input the number of B:");
 scanf("%d",&n);
 printf("input %d data:",n);
 B=crestalink(spaceb,n);

 printf("A=");
 list(spacea,A);

 printf("B=");
 list(spaceb,B);

 printf("(A-B)U(B-A)=");
 mergesetAB(spacea,A,spaceb,B);

}