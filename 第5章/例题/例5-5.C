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




/*教材【例5.5】找出值为x的结点的双亲结点和左右孩子结点的值 */
int search(SqBitTree bt,ElemType x,ElemType *pa,ElemType *lc,ElemType *rc)
{ int i=1;                       
  while(i<=bt[0]&&bt[i]!=x) i++;   /* 查找 */
  if(i>bt[0])                      /* 不存在 */
  { printf("Not found!\n"); *pa=*lc=*rc=VirNode; return 0;}
  if(i==1)                         /* 根结点无双亲 */                        
  { printf("This node has not parents!\n"); *pa=VirNode;}
  else *pa=bt[i/2];
  if(i>bt[0]/2||bt[2*i]==VirNode)  /* 无左孩子 */
  { printf("This Node has not left child!\n"); *lc=VirNode;}
  else *lc=bt[2*i];
  if(i>bt[0]/2||bt[2*i+1]==VirNode)/* 无右孩子 */
  { printf("This Node has not right child!\n"); *rc=VirNode;}
  else *rc=bt[2*i+1];              
  return 1;
}



main()
{ SqBitTree bt;
  ElemType x,pa,lc,rc;
  int n;

  printf("input real node number:");
  scanf("%d%*c",&n);                  /* 同时去除回车符 */

  printf("input the full binary tree: ");
  crebitree(bt,n);                    /* 建立，以教材图5.6(a)为例，输入满二叉树 */
  printf("input x:");
  scanf("%*c%c",&x);

  search(bt,x,&pa,&lc,&rc);
  printf("\nparnet=%c\nleft child=%c\nright child=%c\n",pa,lc,rc);
}
