
 /* 稀疏矩阵的压缩存储 三元顺序表 (只存放非0元素的行标,列标和值) */
 /* 定义三元顺序表的最大长度 */
 #define MAXSIZE  10
 /* 三元组的数据类型 */
 typedef int ElemType;
 typedef struct
 { int i;      /* 行标 */
   int j;      /* 列标 */
   ElemType e; /* 非0元素值 */
 }tupletype;
typedef struct
 { int rownum;
   int colnum;
   int nznum;
   tupletype data[MAXSIZE];
 }table;

 #define M1 6
 #define N1 7


/*从一个二维矩阵创建一个三元组*/
 void creatable(table *M,ElemType A[M1][N1])
 { int i,j;
   M->rownum=M1;
   M->colnum=N1;
   M->nznum=0;
   for(i=0;i<M1;i++)
     for(j=0;j<N1;j++)
       if(A[i][j]!=0)
       { M->data[M->nznum].i=i;
	 M->data[M->nznum].j=j;
	 M->data[M->nznum].e=A[i][j];
	 M->nznum++;
       }
 }


/* 将指定位置的元素值赋给变量，先在三元组中找到指定的位置，将该处的元素赋给x */
getvalue(table *M,ElemType *x,int row,int col)
{ int k=0;
  if(row>=M->rownum||col>=M->colnum)
    return 0;
  while(k<M->nznum&&row>M->data[k].i) k++;
  while(k<M->nznum&&col>M->data[k].j) k++;
  if(M->data[k].i==row&&M->data[k].j==col)
  { *x=M->data[k].e;return 1;}
  else return 0;
}



/*三元组元素赋值*/
putvalue(table *M,ElemType x,int row,int col)
{ int i,k=0;
  if(row>M->rownum||col>M->colnum)
    return 0;
  while(k<M->nznum&&row>M->data[k].i) k++;
  while(k<M->nznum&&col>M->data[k].j) k++;
  if(M->data[k].i==row&&M->data[k].j==col)
    M->data[k].e=x;
   else
   { for(i=M->nznum-1;i>=k;i--)
       M->data[i+1]=M->data[i];
     M->data[k].i=row;
     M->data[k].j=col;
     M->data[k].e=x;
     M->nznum++;
   }
   return 1;
}




 /* 写出输出以压缩方式存储的稀疏矩阵 */
 list(table *M)
 {int i,j,k,e;
  for(i=0;i<M->rownum;i++)
   {
    for(j=0;j<M->colnum;j++)
     { e=0;
      for(k=0;k<M->nznum;k++)
	 if(i==M->data[k].i&&j==M->data[k].j)
	    {e=M->data[k].e;break;}
	 printf("%4d",e);
     }

    printf("\n");
   }
}


 main()
 { table M;
   ElemType x;
   int row,col,n;
   ElemType A[M1][N1]={{0,12,9,0,0,0,0},
		    {0,0,0,0,0,0,0},
		    {3,0,0,0,0,1,0},
		    {0,0,24,0,0,0,0},
		    {0,18,0,0,0,0,0},
		    {5,0,0,7,0,0,0}};           /* 以图4.8矩阵A为例 */
                                            
  creatable(&M,A);                              /* 用三元组表示稀疏矩阵A */
  printf("sparse matrix A:\n");
  list(&M);                                     /* 输出 */
  printf("\n");

  printf("input row and col to get value:");
  scanf("%d%d",&row,&col);
  n=getvalue(&M,&x,row,col);
  if(n) printf("%d\n",x);
  else printf("no exist!\n");
  printf("\n");


  printf("input row,col and value to update:");
  scanf("%d%d%d",&row,&col,&x);
  n=putvalue(&M,x,row,col);
  if(n) list(&M);
  else printf("error\n");
 }