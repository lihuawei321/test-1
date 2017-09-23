typedef int ElemType;    /* 在实际问题中,根据需要定义所需的数据类型 */
#define INITSIZE 100     /* 顺序表存储空间的初始分配量 */
typedef struct
{ ElemType *data;        /* 存储空间基地址 */
  int length;            /* 顺序表长度(即已存入的元素个数) */
      int listsize;      /* 当前存储空间容量(即能存入的元素个数) */
}sqlist;


/* 初始化操作(创建一个空的顺序表L) */
void initlist(sqlist *L)
{ L->data=(ElemType *)malloc(sizeof(ElemType)*INITSIZE);/* 申请存储空间*/
  L->length=0;              /* 初始长度为0 */
  L->listsize=INITSIZE;     /* 容量为初始量 */
}


/* 插入操作(在顺序表L中的第i个位序上插入一个值为x的数据元素) */
int insert(sqlist *L,int i,ElemType x)
{ int j;
  if(i<1||i>L->length+1) return 0;  /* 参数i不合理,返回0 */
  if(L->length==L->listsize)        /* 存储空间不够，增加一个存储空间 */
  {  L->data=(ElemType *)realloc(L->data,(L->listsize+1)*sizeof(ElemType));
     L->listsize++;                 /* 重置存储空间长度 */
  }
  for(j=L->length-1;j>=i-1;j--)
    L->data[j+1]=L->data[j];        /* 将序号为i及之后的数据元素后移一位 */
  L->data[i-1]=x;                   /* 在序号i处放入x */
  L->length++;                      /* 顺序表长度增1 */
  return 1;                         /* 插入成功,返回1 */
}



/* 输出操作(输出顺序表L的各数据元素值) */
void list(sqlist *L)
{ int i;
  for(i=0;i<L->length;i++)
    printf("%5d ",L->data[i]);
  printf("\n");
}



/*【例2.2】已知顺序表L中存放的是互不相同的整数，编写算法，将顺序表L中的所有奇数移到所有的偶数(含0)前面。要求时间最少，辅助空间最少 */
void move(sqlist *L)
{ int i=0,j=L->length-1;
  ElemType temp;
  while(i<j)
  { while(i<j&&L->data[i]%2!=0) i++;      /* 从头向尾找到偶数 */
    while(i<j&&L->data[j]%2==0) j--;      /* 从尾向头找到奇数 */
    if(i<j)                               /* 没相遇，交换 */
    { temp=L->data[i];
      L->data[i]=L->data[j];
      L->data[j]=temp;
    }
  }
}



main()
{ sqlist Q;
  ElemType x;
  int i;

  initlist(&Q);                         /* 创建一个空的顺序表Q */

  printf("input datas(-1:end):");       /* 输入数据,-1作为结束标志 */
  scanf("%d",&x);
  i=1;
  while(x!=-1)
  { insert(&Q,i,x);  		        /* 插入 */
    i++;
    scanf("%d",&x);
  }

  list(&Q);                             /* 输出顺序表 */

  move(&Q);                             /* 移动 */

  list(&Q);                             /* 输出执行删除操作后的顺序表 */
}
