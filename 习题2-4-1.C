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



/* 教材习题2-4-1 设A和B是两个非递减的顺序表。编写算法，把A和B中都存在的元素组成新的由大到小排列的顺序表C，并分析算法的时间复杂度。*/
A_B(sqlist *A,sqlist *B,sqlist *C)
{ int i=0,j,k=0;
  while(i<A->length)                                  /* 对A中的每个元素，判断是否在B中 */
  { j=0;
    while(j<B->length&&A->data[i]!=B->data[j]) j++;
    if(A->data[i]==B->data[j])                        /* 若在B中，则存入C中 */
      C->data[k++]=A->data[i];
    i++;
  }
  C->length=k;
}



main()
{ sqlist A,B,C;
  ElemType x;
  int i;

  initlist(&A);                          /* 创建一个空的顺序表A */
  initlist(&B);                          /* 创建一个空的顺序表B */
  initlist(&C);                          /* 创建一个空的顺序表C */

  printf("input datas to A(-1:end):");   /* 在A中插入数据 */
  scanf("%d",&x);
  i=1;
  while(x!=-1)
  { insert(&A,i,x);
    i++;
    scanf("%d",&x);
  }

  printf("input datas to B(-1:end):");   /* 在B中插入数据 */
  scanf("%d",&x);
  i=1;
  while(x!=-1)
  { insert(&B,i,x);
    i++;
    scanf("%d",&x);
  }

  list(&A);                              /* 输出顺序表A */
  list(&B);                              /* 输出顺序表B */

  A_B(&A,&B,&C);                         /* 组成新表 */
  printf("the public datas are:");
  list(&C);                               /* 输出合并后的顺序表 */
}
