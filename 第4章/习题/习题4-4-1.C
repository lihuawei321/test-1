
#define N 4                /* 已4阶矩阵为例 */
typedef int ElemType;

/*习题4-4-1 编写算法,按矩阵格式输出按行序压缩存储的n阶下三角矩阵 */
printj(ElemType a[],int n)
{ int i,j;
  for(i=0;i<n;i++)
    { for(j=0;j<n;j++)
       if(i>=j) printf("%4d",a[i*(i+1)/2+j]);
       else printf("%4d",a[n*(n+1)/2]);
     printf("\n");
    }
 }


 main()
 { ElemType a[N*(N+1)+1]={1,2,3,4,5,6,7,8,9,10,-1};

  printj(a,4);
  printf("\n");
}


