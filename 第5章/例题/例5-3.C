/* 二叉树的顺序存储结构类型说明 */
#define VirNode '0'           /* 定义虚结点值 */
#define MAX_TREE_SIZE 100     /* 定义存储空间最大容量 */
typedef char ElemType;        /* 定义结点值类型 */
typedef ElemType SqBitTree[MAX_TREE_SIZE];
/* SqBitTree[0]单元存放结点的总数，通常存放构成满二叉树时的结点总数 */




/* 二叉树的按层次建立算法 */
void crebitree(SqBitTree bt,int n)      /* n为真实结点总数 */
{ int i,j,m;
  i=1;m=0;
  while(m<n)
  { for(j=i;j<2*i;j++)                  /* 按层次进行输入，虚结点值一起输入 */
    { scanf("%c",bt+j);
      if(bt[j]!=VirNode) m++;
    }
    i=2*i;                              
  }
  bt[0]=i-1;                            /* 0号单元存放满二叉树的结点总数 */
}



/* 教材【例5.3】统计度为2的结点个数 */
int count2(SqBitTree bt)
{ int i,j,n;
  i=1;n=0;                              /* i存放每层第一个结点的编号,n存放度为2的结点数 */
  while(i<=bt[0]/2)                     /* 按性质7可知，凡是大于bt[0]/2的结点不可能是度为2的结点 */
  { for(j=i;j<2*i;j++)
      if(bt[j]!=VirNode&&bt[2*j]!=VirNode&&bt[2*j+1]!=VirNode)
        n++;
    i=2*i;                              /* 跳到下一层的第一个结点 */
  }
  return n;
}



main()
{ SqBitTree bt;
  int n;
  printf("input real node number:");
  scanf("%d%*c",&n);                  /* 同时去除回车符 */

  printf("input the full binary tree: ");
  crebitree(bt,n);                    /* 建立，以教材图5.6(a)为例，输入满二叉树 */

  printf("the result is:");
  printf("%d\n",count2(bt));
}