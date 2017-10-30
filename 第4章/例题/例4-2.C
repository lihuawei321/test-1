
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


/*从一个二维矩阵创建一个三元组 */
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


/* 【例4.2】采用三元组存储结构，写出实现对稀疏矩阵进行转置的算法 */
 
/* 方法一 */
 trans1(table *M,table *T)
  { int a,b,q=0;
   T->rownum=M->colnum;
   T->colnum=M->rownum;
   T->nznum=M->nznum;
   if(T->nznum!=0)
   {
     for(a=0;a<M->colnum;a++)
	for(b=0;b<M->nznum;b++)
	 if(M->data[b].j==a)
	  {
	   T->data[q].i=M->data[b].j;
	   T->data[q].j=M->data[b].i;
	   T->data[q].e=M->data[b].e;
	   q++;
	  }
   }
 }

 /* 方法二 */
 trans2(table *M,table *T)
 { int num[N1];
   int cpot[N1];
   int i;
   int q;
   int col;
   T->rownum=M->colnum;
   T->colnum=M->rownum;
   T->nznum=M->nznum;
   for(i=0;i<M->colnum;i++) num[i]=0;
   for(i=0;i<M->nznum;i++) num[M->data[i].j]++;
   cpot[0]=0;
   for(i=1;i<M->colnum;i++) cpot[i]=cpot[i-1]+num[i-1];
   for(i=0;i<M->nznum;i++)
    {
     col=M->data[i].j;
     q=cpot[col];
     T->data[q].i=M->data[i].j;
     T->data[q].j=M->data[i].i;
     T->data[q].e=M->data[i].e;
     cpot[col]++;
    }
   }



 main()
 { table M,T,H;
   ElemType x;
   ElemType A[M1][N1]={{0,12,9,0,0,0,0},
		    {0,0,0,0,0,0,0},
		    {3,0,0,0,0,1,0},
		    {0,0,24,0,0,0,0},
		    {0,18,0,0,0,0,0},
		    {5,0,0,7,0,0,0}};   /* 以图4.8中的矩阵A为例 */

  creatable(&M,A);                      /* 用三元组表示 */
  list(&M);
  printf("\n");


  trans1(&M,&T);                        /* 用方法一转置 */
  list(&T);
  printf("\n");

  trans2(&M,&H);                        /* 用方法二转置 */
  list(&H);
  printf("\n");
}


