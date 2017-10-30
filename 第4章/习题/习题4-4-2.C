

/* 习题4-4-2 设有二维数组A[m][n]，其元素类型为ElemType，每行每列都按从小到大有序，编写算法求出数组中第一个值为x的元素的行号i和列号j。设值x在A中存在，要求比较次数不多于m+n次。 */

typedef int ElemType;
#define M 3
#define N 4                        /* 以3*4矩阵为例 */

search(ElemType a[][N],ElemType x,int *i,int *j)
{ *i=0;*j=N-1;
  while(a[*i][*j]!=x)
  if(a[*i][*j]>x)
    (*j)--;
  else
    (*i)++;
}



main()
{ ElemType A[M][N],x;
  int i,j;
  printf("input %d row and %d colnum data:\n",M,N);
  for(i=0;i<M;i++)
    for(j=0;j<N;j++)
      scanf("%d",&A[i][j]);
  printf("input the search data:");
  scanf("%d",&x);
  search(A,x,&i,&j);

  printf("%d position is(%d,%d)\n",x,i,j);
}
