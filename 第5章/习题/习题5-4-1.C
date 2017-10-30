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



/* 习题5-4-1已知一棵二叉树以顺序结构存储，试编制算法计算任一结点所在的层次。 */
int levelnode(SqBitTree bt,ElemType x)
{ int num=0,i,n1;
   n1=1;
   while(bt[n1]!=x&&n1<=bt[0]) n1++;
   if(n1<=bt[0])
   { i=1;
     while(n1-i>0)
     { num++;
       n1-=i;
       i*=2;
     }
     return num+1;
   }
   else
   return -1;
}


main()
{ SqBitTree bt;
  int n;
  ElemType x;
  printf("input real node number:");
  scanf("%d%*c",&n);                  /* 同时取出回车符 */

  printf("input the full binary tree: ");
  crebitree(bt,n);                    /* 建立，以教材图5.6(a)为例，输入满二叉树 */

  printf("input x:");
  scanf("%*c%c",&x);

  n=levelnode(bt,x);
  if(n!=-1) printf("\n %c in %d level\n",x,n);
  else printf("not exist!\n");
}
