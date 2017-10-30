/* 二叉树的顺序存储结构类型说明 */
#define VirNode '0'           /* 定义虚结点值 */
#define MAX_TREE_SIZE 100     /* 定义存储空间最大容量 */
typedef char ElemType;        /* 定义结点值类型 */
typedef ElemType SqBitTree[MAX_TREE_SIZE];
/* SqBitTree[0]单元存放结点的总数，通常存放构成满二叉树时的结点总数 */




/* 二叉树的层次遍历算法 */
void leveltree(SqBitTree bt)            /* 按满二叉树遍历(输出) */
{ int i,j;
  i=1;
  while(i<=bt[0])			/* 按层扫描 */
  { for(j=i;j<2*i;j++)                  /* 扫描第i层结点 */
      if(bt[j]==VirNode) printf("*");	/* 若是虚结点，则输出一个*号 */
      else printf("%c",bt[j]);
    printf("\n");
    i=2*i;				/* 跳到下一层的第一个结点 */
  }
}

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


/* 交换二叉树中所有结点的左右子树算法 */
void exchangetree(SqBitTree bt)
{ int k=2,i,j;ElemType t;               /* 第一层只有一个结点，所以从第二层开始进行 */
  while(k<=bt[0])
  { for(i=k,j=2*k-1;i<j;i++,j--)        /* 同一层结点值逆置即可完成交换 */
    { t=bt[i];bt[i]=bt[j];bt[j]=t;}
    k=2*k;                              /* 准备交换下一层结点 */
  }
}

/* 统计叶子结点的个数 */
int countleaf(SqBitTree bt)
{ int i,j,n;                            /* i存放每层第一个结点的编号,n存放叶子结点数 */
  i=1;n=0;
  while(i<=bt[0]/2)                     /* 按性质7可知：凡是大于bt[0]/2的结点均为叶子结点 */
  { for(j=i;j<2*i;j++)
      if(bt[j]!=VirNode&&bt[2*j]==VirNode&&bt[2*j+1]==VirNode)
        n++;
    i=2*i;                              /* 跳到下一层的第一个结点 */
  }
  for(j=i;j<2*i;j++)                    /* 最底层结点若不是虚结点，即为叶子结点 */
    if(bt[j]!=VirNode) n++;
  return n;
}

/* 求二叉树的高度 */
int high(SqBitTree bt)
{ int i,h;
  i=1;h=0;                              /* i存放每层第一个结点的编号,h存放高度 */
  while(i<=bt[0])
  { h++;
    i=2*i;                              /* 跳到下一层的第一个结点 */
  }
  return h;
}



main()
{ SqBitTree bt;
  int n;
  printf("input real node number:");
  scanf("%d%*c",&n);                  /* 同时去除回车符 */
  
  printf("input the full binary tree: ");
  crebitree(bt,n);                    /* 建立，以教材图5.6(a)为例，输入满二叉树 */
  
  printf("the leveal traversal result:\n");
  leveltree(bt);

  printf("exchange left sub-tree and right sub-tree, the result:\n");
  leveltree(bt);

  printf("the number of leaf nodes are:");
  printf("%d\n",countleaf(bt));

  printf("the height of binary tree is:");
  printf("%d\n",high(bt));
}
