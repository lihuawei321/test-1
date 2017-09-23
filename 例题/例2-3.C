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



/*【例2.3】编写算法，将两个非递减顺序表L1和L2合并到顺序表L中，使合并后的顺序表仍然保持非递减的特性 */
void merge(sqlist *L1,sqlist *L2,sqlist *L)
{ int i=0,j=0;
  initlist(L);                          /* 初始化顺序表L */
  while(i<L1->length&&j<L2->length)
    if(L1->data[i]<L2->data[j])         /* 将L1->data[i]插入到L尾部 */
    { insert(L,L->length+1,L1->data[i]);i++;}
    else                                /* 将L2->data[j]插入到L的尾部 */
    { insert(L,L->length+1,L2->data[j]);j++;}
  while(i<L1->length)      /* L2中的元素已插完,将L1的剩余部分插入到L尾部 */
  { insert(L,L->length+1,L1->data[i]);i++;}
  while(j<L2->length)      /* L1中的元素已插完,将L2的剩余部分插入到L尾部 */
  { insert(L,L->length+1,L2->data[j]);j++;}
}




main()
{ sqlist Q,Q1,Q2;
  ElemType x;
  int i;

  initlist(&Q);                          /* 创建一个空的顺序表Q */
  initlist(&Q1);                         /* 创建一个空的顺序表Q1 */
  initlist(&Q2);                         /* 创建一个空的顺序表Q2 */

  printf("input datas to Q1(-1:end):");  /* 在Q1中插入数据 */
  scanf("%d",&x);
  i=1;
  while(x!=-1)
  { insert(&Q1,i,x);  		         
    i++;
    scanf("%d",&x);
  }

  printf("input datas to Q2(-1:end):");  /* 在Q2中插入数据 */
  scanf("%d",&x);
  i=1;
  while(x!=-1)
  { insert(&Q2,i,x);  		         
    i++;
    scanf("%d",&x);
  }

  list(&Q1);                              /* 输出顺序表Q1 */
  list(&Q2);                              /* 输出顺序表Q2 */

  merge(&Q1,&Q2,&Q);                      /* 移动 */

  list(&Q);                               /* 输出合并后的顺序表 */
}
